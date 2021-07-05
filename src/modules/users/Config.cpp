/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "Config.h"

#include "CreateUserJob.h"
#include "MiscJobs.h"
#include "SetHostNameJob.h"
#include "SetPasswordJob.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/Logger.h"
#include "utils/String.h"
#include "utils/Variant.h"

#include <QCoreApplication>
#include <QFile>
#include <QMetaProperty>
#include <QRegExp>
#include <QTimer>

#ifdef HAVE_ICU
#include <unicode/translit.h>
#include <unicode/unistr.h>

//Needed for ICU to apply some transliteration ruleset.
//Still needs to be adjusted to fit the needs of the most of users
static const char TRANSLITERATOR_ID[] = "Russian-Latin/BGN;"
                                        "Greek-Latin/UNGEGN;"
                                        "Any-Latin;"
                                        "Latin-ASCII";
#endif

#include <memory>

static const QRegExp USERNAME_RX( "^[a-z_][a-z0-9_-]*[$]?$" );
static constexpr const int USERNAME_MAX_LENGTH = 31;

static const QRegExp HOSTNAME_RX( "^[a-zA-Z0-9][-a-zA-Z0-9_]*$" );
static constexpr const int HOSTNAME_MIN_LENGTH = 2;
static constexpr const int HOSTNAME_MAX_LENGTH = 63;

static void
updateGSAutoLogin( bool doAutoLogin, const QString& login )
{
    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
    if ( !gs )
    {
        cWarning() << "No Global Storage available";
        return;
    }

    if ( doAutoLogin && !login.isEmpty() )
    {
        gs->insert( "autoLoginUser", login );
    }
    else
    {
        gs->remove( "autoLoginUser" );
    }

    if ( login.isEmpty() )
    {
        gs->remove( "username" );
    }
    else
    {
        gs->insert( "username", login );
    }
}

const NamedEnumTable< HostNameAction >&
hostNameActionNames()
{
    // *INDENT-OFF*
    // clang-format off
    static const NamedEnumTable< HostNameAction > names {
        { QStringLiteral( "none" ), HostNameAction::None },
        { QStringLiteral( "etcfile" ), HostNameAction::EtcHostname },
        { QStringLiteral( "hostnamed" ), HostNameAction::SystemdHostname }
    };
    // clang-format on
    // *INDENT-ON*

    return names;
}

Config::Config( QObject* parent )
    : Calamares::ModuleSystem::Config( parent )
{
    emit readyChanged( m_isReady );  // false

    // Gang together all the changes of status to one readyChanged() signal
    connect( this, &Config::hostNameStatusChanged, this, &Config::checkReady );
    connect( this, &Config::loginNameStatusChanged, this, &Config::checkReady );
    connect( this, &Config::fullNameChanged, this, &Config::checkReady );
    connect( this, &Config::userPasswordStatusChanged, this, &Config::checkReady );
    connect( this, &Config::rootPasswordStatusChanged, this, &Config::checkReady );
    connect( this, &Config::reuseUserPasswordForRootChanged, this, &Config::checkReady );
    connect( this, &Config::requireStrongPasswordsChanged, this, &Config::checkReady );
}

Config::~Config() {}

void
Config::setUserShell( const QString& shell )
{
    if ( !shell.isEmpty() && !shell.startsWith( '/' ) )
    {
        cWarning() << "User shell" << shell << "is not an absolute path.";
        return;
    }
    if ( shell != m_userShell )
    {
        m_userShell = shell;
        emit userShellChanged( shell );
        // The shell is put into GS as well.
        auto* gs = Calamares::JobQueue::instance()->globalStorage();
        if ( gs )
        {
            gs->insert( "userShell", shell );
        }
    }
}

static inline void
insertInGlobalStorage( const QString& key, const QString& group )
{
    auto* gs = Calamares::JobQueue::instance()->globalStorage();
    if ( !gs || group.isEmpty() )
    {
        return;
    }
    gs->insert( key, group );
}

void
Config::setAutoLoginGroup( const QString& group )
{
    if ( group != m_autoLoginGroup )
    {
        m_autoLoginGroup = group;
        insertInGlobalStorage( QStringLiteral( "autoLoginGroup" ), group );
        emit autoLoginGroupChanged( group );
    }
}

QStringList
Config::groupsForThisUser() const
{
    QStringList l;
    l.reserve( defaultGroups().size() + 1 );

    for ( const auto& g : defaultGroups() )
    {
        l << g.name();
    }
    if ( doAutoLogin() && !autoLoginGroup().isEmpty() )
    {
        l << autoLoginGroup();
    }

    return l;
}

void
Config::setSudoersGroup( const QString& group )
{
    if ( group != m_sudoersGroup )
    {
        m_sudoersGroup = group;
        insertInGlobalStorage( QStringLiteral( "sudoersGroup" ), group );
        emit sudoersGroupChanged( group );
    }
}


void
Config::setLoginName( const QString& login )
{
    CONFIG_PREVENT_EDITING( QString, "loginName" );
    if ( login != m_loginName )
    {
        m_customLoginName = !login.isEmpty();
        m_loginName = login;
        updateGSAutoLogin( doAutoLogin(), login );
        emit loginNameChanged( login );
        emit loginNameStatusChanged( loginNameStatus() );
    }
}

const QStringList&
Config::forbiddenLoginNames()
{
    static QStringList forbidden { "root" };
    return forbidden;
}

QString
Config::loginNameStatus() const
{
    // An empty login is "ok", even if it isn't really
    if ( m_loginName.isEmpty() )
    {
        return QString();
    }

    if ( m_loginName.length() > USERNAME_MAX_LENGTH )
    {
        return tr( "Your username is too long." );
    }
    for ( const QString& badName : forbiddenLoginNames() )
    {
        if ( 0 == QString::compare( badName, m_loginName, Qt::CaseSensitive ) )
        {
            return tr( "'%1' is not allowed as username." ).arg( badName );
        }
    }

    QRegExp validateFirstLetter( "^[a-z_]" );
    if ( validateFirstLetter.indexIn( m_loginName ) != 0 )
    {
        return tr( "Your username must start with a lowercase letter or underscore." );
    }
    if ( !USERNAME_RX.exactMatch( m_loginName ) )
    {
        return tr( "Only lowercase letters, numbers, underscore and hyphen are allowed." );
    }

    return QString();
}

void
Config::setHostName( const QString& host )
{
    if ( host != m_hostName )
    {
        m_customHostName = !host.isEmpty();
        m_hostName = host;
        Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
        if ( host.isEmpty() )
        {
            gs->remove( "hostname" );
        }
        else
        {
            gs->insert( "hostname", host );
        }
        emit hostNameChanged( host );
        emit hostNameStatusChanged( hostNameStatus() );
    }
}

const QStringList&
Config::forbiddenHostNames()
{
    static QStringList forbidden { "localhost" };
    return forbidden;
}

QString
Config::hostNameStatus() const
{
    // An empty hostname is "ok", even if it isn't really
    if ( m_hostName.isEmpty() )
    {
        return QString();
    }

    if ( m_hostName.length() < HOSTNAME_MIN_LENGTH )
    {
        return tr( "Your hostname is too short." );
    }
    if ( m_hostName.length() > HOSTNAME_MAX_LENGTH )
    {
        return tr( "Your hostname is too long." );
    }
    for ( const QString& badName : forbiddenHostNames() )
    {
        if ( 0 == QString::compare( badName, m_hostName, Qt::CaseSensitive ) )
        {
            return tr( "'%1' is not allowed as hostname." ).arg( badName );
        }
    }

    if ( !HOSTNAME_RX.exactMatch( m_hostName ) )
    {
        return tr( "Only letters, numbers, underscore and hyphen are allowed." );
    }

    return QString();
}


/** @brief Guess the machine's name
 *
 * If there is DMI data, use that; otherwise, just call the machine "-pc".
 * Reads the DMI data just once.
 */
static QString
guessProductName()
{
    static bool tried = false;
    static QString dmiProduct;

    if ( !tried )
    {
        // yes validateHostnameText() but these files can be a mess
        QRegExp dmirx( "[^a-zA-Z0-9]", Qt::CaseInsensitive );
        QFile dmiFile( QStringLiteral( "/sys/devices/virtual/dmi/id/product_name" ) );

        if ( dmiFile.exists() && dmiFile.open( QIODevice::ReadOnly ) )
        {
            dmiProduct = QString::fromLocal8Bit( dmiFile.readAll().simplified().data() )
                             .toLower()
                             .replace( dmirx, " " )
                             .remove( ' ' );
        }
        if ( dmiProduct.isEmpty() )
        {
            dmiProduct = QStringLiteral( "pc" );
        }
        tried = true;
    }
    return dmiProduct;
}
#ifdef HAVE_ICU
static QString
transliterate( const QString& input )
{
    static auto ue = UErrorCode::U_ZERO_ERROR;
    static auto transliterator = std::unique_ptr< icu::Transliterator >(
        icu::Transliterator::createInstance( TRANSLITERATOR_ID, UTRANS_FORWARD, ue ) );

    if ( ue != UErrorCode::U_ZERO_ERROR )
    {
        cWarning() << "Can't create transliterator";

        //it'll be checked later for non-ASCII characters
        return input;
    }

    icu::UnicodeString transliterable( input.utf16() );
    transliterator->transliterate( transliterable );
    return QString::fromUtf16( transliterable.getTerminatedBuffer() );
}
#else
static QString
transliterate( const QString& input )
{
    return input;
}
#endif

static QString
makeLoginNameSuggestion( const QStringList& parts )
{
    if ( parts.isEmpty() || parts.first().isEmpty() )
    {
        return QString();
    }

    QString usernameSuggestion = parts.first();
    for ( int i = 1; i < parts.length(); ++i )
    {
        if ( !parts.value( i ).isEmpty() )
        {
            usernameSuggestion.append( parts.value( i ).at( 0 ) );
        }
    }

    return USERNAME_RX.indexIn( usernameSuggestion ) != -1 ? usernameSuggestion : QString();
}

static QString
makeHostnameSuggestion( const QStringList& parts )
{
    static const QRegExp HOSTNAME_RX( "^[a-zA-Z0-9][-a-zA-Z0-9_]*$" );
    if ( parts.isEmpty() || parts.first().isEmpty() )
    {
        return QString();
    }

    QString productName = guessProductName();
    QString hostnameSuggestion = QStringLiteral( "%1-%2" ).arg( parts.first() ).arg( productName );
    return HOSTNAME_RX.indexIn( hostnameSuggestion ) != -1 ? hostnameSuggestion : QString();
}

void
Config::setFullName( const QString& name )
{
    CONFIG_PREVENT_EDITING( QString, "fullName" );

    if ( name.isEmpty() && !m_fullName.isEmpty() )
    {
        if ( !m_customHostName )
        {
            setHostName( name );
        }
        if ( !m_customLoginName )
        {
            setLoginName( name );
        }
        m_fullName = name;
        emit fullNameChanged( name );
    }

    if ( name != m_fullName )
    {
        m_fullName = name;
        emit fullNameChanged( name );

        // Build login and hostname, if needed
        static QRegExp rx( "[^a-zA-Z0-9 ]", Qt::CaseInsensitive );

        QString cleanName = CalamaresUtils::removeDiacritics( transliterate( name ) )
                                .replace( QRegExp( "[-']" ), "" )
                                .replace( rx, " " )
                                .toLower()
                                .simplified();


        QStringList cleanParts = cleanName.split( ' ' );

        if ( !m_customLoginName )
        {
            QString login = makeLoginNameSuggestion( cleanParts );
            if ( !login.isEmpty() && login != m_loginName )
            {
                setLoginName( login );
                // It's **still** not custom, though setLoginName() sets that
                m_customLoginName = false;
            }
        }
        if ( !m_customHostName )
        {
            QString hostname = makeHostnameSuggestion( cleanParts );
            if ( !hostname.isEmpty() && hostname != m_hostName )
            {
                setHostName( hostname );
                // Still not custom
                m_customHostName = false;
            }
        }
    }
}

void
Config::setAutoLogin( bool b )
{
    if ( b != m_doAutoLogin )
    {
        m_doAutoLogin = b;
        updateGSAutoLogin( b, loginName() );
        emit autoLoginChanged( b );
    }
}

void
Config::setReuseUserPasswordForRoot( bool reuse )
{
    if ( reuse != m_reuseUserPasswordForRoot )
    {
        m_reuseUserPasswordForRoot = reuse;
        emit reuseUserPasswordForRootChanged( reuse );
        {
            auto rp = rootPasswordStatus();
            emit rootPasswordStatusChanged( rp.first, rp.second );
        }
    }
}

void
Config::setRequireStrongPasswords( bool strong )
{
    if ( strong != m_requireStrongPasswords )
    {
        m_requireStrongPasswords = strong;
        emit requireStrongPasswordsChanged( strong );
        {
            auto rp = rootPasswordStatus();
            emit rootPasswordStatusChanged( rp.first, rp.second );
        }
        {
            auto up = userPasswordStatus();
            emit userPasswordStatusChanged( up.first, up.second );
        }
    }
}

void
Config::setUserPassword( const QString& s )
{
    if ( s != m_userPassword )
    {
        m_userPassword = s;
        const auto p = passwordStatus( m_userPassword, m_userPasswordSecondary );
        emit userPasswordStatusChanged( p.first, p.second );
        emit userPasswordChanged( s );
    }
}

void
Config::setUserPasswordSecondary( const QString& s )
{
    if ( s != m_userPasswordSecondary )
    {
        m_userPasswordSecondary = s;
        const auto p = passwordStatus( m_userPassword, m_userPasswordSecondary );
        emit userPasswordStatusChanged( p.first, p.second );
        emit userPasswordSecondaryChanged( s );
    }
}

/** @brief Checks two copies of the password for validity
 *
 * Given two copies of the password -- generally the password and
 * the secondary fields -- checks them for validity and returns
 * a pair of <validity, message>.
 *
 */
Config::PasswordStatus
Config::passwordStatus( const QString& pw1, const QString& pw2 ) const
{
    if ( pw1 != pw2 )
    {
        return qMakePair( PasswordValidity::Invalid, tr( "Your passwords do not match!" ) );
    }

    bool failureIsFatal = requireStrongPasswords();
    for ( const auto& pc : m_passwordChecks )
    {
        QString message = pc.filter( pw1 );

        if ( !message.isEmpty() )
        {
            return qMakePair( failureIsFatal ? PasswordValidity::Invalid : PasswordValidity::Weak, message );
        }
    }

    return qMakePair( PasswordValidity::Valid, tr( "OK!" ) );
}


Config::PasswordStatus
Config::userPasswordStatus() const
{
    return passwordStatus( m_userPassword, m_userPasswordSecondary );
}

int
Config::userPasswordValidity() const
{
    auto p = userPasswordStatus();
    return p.first;
}

QString
Config::userPasswordMessage() const
{
    auto p = userPasswordStatus();
    return p.second;
}


void
Config::setRootPassword( const QString& s )
{
    if ( writeRootPassword() && s != m_rootPassword )
    {
        m_rootPassword = s;
        const auto p = passwordStatus( m_rootPassword, m_rootPasswordSecondary );
        emit rootPasswordStatusChanged( p.first, p.second );
        emit rootPasswordChanged( s );
    }
}

void
Config::setRootPasswordSecondary( const QString& s )
{
    if ( writeRootPassword() && s != m_rootPasswordSecondary )
    {
        m_rootPasswordSecondary = s;
        const auto p = passwordStatus( m_rootPassword, m_rootPasswordSecondary );
        emit rootPasswordStatusChanged( p.first, p.second );
        emit rootPasswordSecondaryChanged( s );
    }
}

QString
Config::rootPassword() const
{
    if ( writeRootPassword() )
    {
        if ( reuseUserPasswordForRoot() )
        {
            return userPassword();
        }
        return m_rootPassword;
    }
    return QString();
}

QString
Config::rootPasswordSecondary() const
{
    if ( writeRootPassword() )
    {
        if ( reuseUserPasswordForRoot() )
        {
            return userPasswordSecondary();
        }
        return m_rootPasswordSecondary;
    }
    return QString();
}

Config::PasswordStatus
Config::rootPasswordStatus() const
{
    if ( writeRootPassword() && !reuseUserPasswordForRoot() )
    {
        return passwordStatus( m_rootPassword, m_rootPasswordSecondary );
    }
    else
    {
        return userPasswordStatus();
    }
}

int
Config::rootPasswordValidity() const
{
    auto p = rootPasswordStatus();
    return p.first;
}

QString
Config::rootPasswordMessage() const
{
    auto p = rootPasswordStatus();
    return p.second;
}

bool
Config::isReady() const
{
    bool readyFullName = !fullName().isEmpty();  // Needs some text
    bool readyHostname = hostNameStatus().isEmpty();  // .. no warning message
    bool readyUsername = !loginName().isEmpty() && loginNameStatus().isEmpty();  // .. no warning message
    bool readyUserPassword = userPasswordValidity() != Config::PasswordValidity::Invalid;
    bool readyRootPassword = rootPasswordValidity() != Config::PasswordValidity::Invalid;
    return readyFullName && readyHostname && readyUsername && readyUserPassword && readyRootPassword;
}

/** @brief Update ready status and emit signal
 *
 * This is a "concentrator" private slot for all the status-changed
 * signals, so that readyChanged() is emitted only when needed.
 */
void
Config::checkReady()
{
    bool b = isReady();
    if ( b != m_isReady )
    {
        m_isReady = b;
        emit readyChanged( b );
    }
}


STATICTEST void
setConfigurationDefaultGroups( const QVariantMap& map, QList< GroupDescription >& defaultGroups )
{
    defaultGroups.clear();

    const QString key( "defaultGroups" );
    auto groupsFromConfig = map.value( key ).toList();
    if ( groupsFromConfig.isEmpty() )
    {
        if ( map.contains( key ) && map.value( key ).isValid() && map.value( key ).canConvert( QVariant::List ) )
        {
            // Explicitly set, but empty: this is valid, but unusual.
            cDebug() << key << "has explicit empty value.";
        }
        else
        {
            // By default give the user a handful of "traditional" groups, if
            // none are specified at all. These are system (GID < 1000) groups.
            cWarning() << "Using fallback groups. Please check *defaultGroups* value in users.conf";
            for ( const auto& s : { "lp", "video", "network", "storage", "wheel", "audio" } )
            {
                defaultGroups.append(
                    GroupDescription( s, GroupDescription::CreateIfNeeded {}, GroupDescription::SystemGroup {} ) );
            }
        }
    }
    else
    {
        for ( const auto& v : groupsFromConfig )
        {
            if ( v.type() == QVariant::String )
            {
                defaultGroups.append( GroupDescription( v.toString() ) );
            }
            else if ( v.type() == QVariant::Map )
            {
                const auto innermap = v.toMap();
                QString name = CalamaresUtils::getString( innermap, "name" );
                if ( !name.isEmpty() )
                {
                    defaultGroups.append( GroupDescription( name,
                                                            CalamaresUtils::getBool( innermap, "must_exist", false ),
                                                            CalamaresUtils::getBool( innermap, "system", false ) ) );
                }
                else
                {
                    cWarning() << "Ignoring *defaultGroups* entry without a name" << v;
                }
            }
            else
            {
                cWarning() << "Unknown *defaultGroups* entry" << v;
            }
        }
    }
}

STATICTEST HostNameActions
getHostNameActions( const QVariantMap& configurationMap )
{
    HostNameAction setHostName = HostNameAction::EtcHostname;
    QString hostnameActionString = CalamaresUtils::getString( configurationMap, "setHostname" );
    if ( !hostnameActionString.isEmpty() )
    {
        bool ok = false;
        setHostName = hostNameActionNames().find( hostnameActionString, ok );
        if ( !ok )
        {
            setHostName = HostNameAction::EtcHostname;  // Rather than none
        }
    }

    HostNameAction writeHosts = CalamaresUtils::getBool( configurationMap, "writeHostsFile", true )
        ? HostNameAction::WriteEtcHosts
        : HostNameAction::None;
    return setHostName | writeHosts;
}

/** @brief Process entries in the passwordRequirements config entry
 *
 * Called once for each item in the config entry, which should
 * be a key-value pair. What makes sense as a value depends on
 * the key. Supported keys are documented in users.conf.
 *
 * @return if the check was added, returns @c true
 */
STATICTEST bool
addPasswordCheck( const QString& key, const QVariant& value, PasswordCheckList& passwordChecks )
{
    if ( key == "minLength" )
    {
        add_check_minLength( passwordChecks, value );
    }
    else if ( key == "maxLength" )
    {
        add_check_maxLength( passwordChecks, value );
    }
    else if ( key == "nonempty" )
    {
        if ( value.toBool() )
        {
            passwordChecks.push_back(
                PasswordCheck( []() { return QCoreApplication::translate( "PWQ", "Password is empty" ); },
                               []( const QString& s ) { return !s.isEmpty(); },
                               PasswordCheck::Weight( 1 ) ) );
        }
        else
        {
            cDebug() << "nonempty check is mentioned but set to false";
            return false;
        }
    }
#ifdef CHECK_PWQUALITY
    else if ( key == "libpwquality" )
    {
        add_check_libpwquality( passwordChecks, value );
    }
#endif  // CHECK_PWQUALITY
    else
    {
        cWarning() << "Unknown password-check key" << key;
        return false;
    }
    return true;
}

/** @brief Returns a value of either key from the map
 *
 * Takes a function (e.g. getBool, or getString) and two keys,
 * returning the value in the map of the one that is there (or @p defaultArg)
 */
template < typename T, typename U >
T
either( T ( *f )( const QVariantMap&, const QString&, U ),
        const QVariantMap& configurationMap,
        const QString& oldKey,
        const QString& newKey,
        U defaultArg )
{
    if ( configurationMap.contains( oldKey ) )
    {
        return f( configurationMap, oldKey, defaultArg );
    }
    else
    {
        return f( configurationMap, newKey, defaultArg );
    }
}

void
Config::setConfigurationMap( const QVariantMap& configurationMap )
{
    QString shell( QLatin1String( "/bin/bash" ) );  // as if it's not set at all
    if ( configurationMap.contains( "userShell" ) )
    {
        shell = CalamaresUtils::getString( configurationMap, "userShell" );
    }
    // Now it might be explicitly set to empty, which is ok
    setUserShell( shell );

    setAutoLoginGroup( either< QString, const QString& >(
        CalamaresUtils::getString, configurationMap, "autologinGroup", "autoLoginGroup", QString() ) );
    setSudoersGroup( CalamaresUtils::getString( configurationMap, "sudoersGroup" ) );

    m_hostNameActions = getHostNameActions( configurationMap );

    setConfigurationDefaultGroups( configurationMap, m_defaultGroups );

    // Renaming of Autologin -> AutoLogin in 4ffa79d4cf also affected
    // configuration keys, which was not intended. Accept both.
    m_doAutoLogin = either( CalamaresUtils::getBool,
                            configurationMap,
                            QStringLiteral( "doAutologin" ),
                            QStringLiteral( "doAutoLogin" ),
                            false );

    m_writeRootPassword = CalamaresUtils::getBool( configurationMap, "setRootPassword", true );
    Calamares::JobQueue::instance()->globalStorage()->insert( "setRootPassword", m_writeRootPassword );

    m_reuseUserPasswordForRoot = CalamaresUtils::getBool( configurationMap, "doReusePassword", false );

    m_permitWeakPasswords = CalamaresUtils::getBool( configurationMap, "allowWeakPasswords", false );
    m_requireStrongPasswords
        = !m_permitWeakPasswords || !CalamaresUtils::getBool( configurationMap, "allowWeakPasswordsDefault", false );

    // If the value doesn't exist, or isn't a map, this gives an empty map -- no problem
    auto pr_checks( configurationMap.value( "passwordRequirements" ).toMap() );
    for ( decltype( pr_checks )::const_iterator i = pr_checks.constBegin(); i != pr_checks.constEnd(); ++i )
    {
        addPasswordCheck( i.key(), i.value(), m_passwordChecks );
    }
    std::sort( m_passwordChecks.begin(), m_passwordChecks.end() );

    updateGSAutoLogin( doAutoLogin(), loginName() );
    checkReady();

    ApplyPresets( *this, configurationMap ) << "fullName"
                                            << "loginName";
}

void
Config::finalizeGlobalStorage() const
{
    updateGSAutoLogin( doAutoLogin(), loginName() );

    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
    if ( writeRootPassword() )
    {
        gs->insert( "reuseRootPassword", reuseUserPasswordForRoot() );
    }
    gs->insert( "password", CalamaresUtils::obscure( userPassword() ) );
}

Calamares::JobList
Config::createJobs() const
{
    Calamares::JobList jobs;

    if ( !isReady() )
    {
        return jobs;
    }

    Calamares::Job* j;

    if ( !m_sudoersGroup.isEmpty() )
    {
        j = new SetupSudoJob( m_sudoersGroup );
        jobs.append( Calamares::job_ptr( j ) );
    }

    j = new SetupGroupsJob( this );
    jobs.append( Calamares::job_ptr( j ) );

    j = new CreateUserJob( this );
    jobs.append( Calamares::job_ptr( j ) );

    j = new SetPasswordJob( loginName(), userPassword() );
    jobs.append( Calamares::job_ptr( j ) );

    j = new SetPasswordJob( "root", rootPassword() );
    jobs.append( Calamares::job_ptr( j ) );

    j = new SetHostNameJob( hostName(), hostNameActions() );
    jobs.append( Calamares::job_ptr( j ) );

    return jobs;
}
