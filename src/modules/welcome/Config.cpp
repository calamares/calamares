/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019-2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "Config.h"

#include "Branding.h"
#include "CalamaresAbout.h"
#include "GlobalStorage.h"
#include "JobQueue.h"
#include "Settings.h"
#include "geoip/Handler.h"
#include "locale/Global.h"
#include "locale/Lookup.h"
#include "modulesystem/ModuleManager.h"
#include "utils/Logger.h"
#include "utils/Retranslator.h"
#include "utils/Variant.h"

#include <QFutureWatcher>

Config::Config( QObject* parent )
    : QObject( parent )
    , m_languages( CalamaresUtils::Locale::availableTranslations() )
    , m_filtermodel( std::make_unique< QSortFilterProxyModel >() )
    , m_requirementsChecker( std::make_unique< GeneralRequirements >( this ) )
{
    initLanguages();

    CALAMARES_RETRANSLATE_SLOT( &Config::retranslate );
    // But also when the requirements model changes, update the messages
    connect( requirementsModel(), &Calamares::RequirementsModel::progressMessageChanged, this, &Config::retranslate );
}

void
Config::retranslate()
{
    const auto* branding = Calamares::Branding::instance();
    const auto* settings = Calamares::Settings::instance();
    m_genericWelcomeMessage = genericWelcomeMessage().arg( branding ? branding->versionedName() : QString() );
    emit genericWelcomeMessageChanged( m_genericWelcomeMessage );

    const auto* r = requirementsModel();
    if ( r && !r->satisfiedRequirements() )
    {
        QString message;
        const bool setup = settings ? settings->isSetupMode() : false;

        if ( !r->satisfiedMandatory() )
        {
            message = setup ? tr( "This computer does not satisfy the minimum "
                                  "requirements for setting up %1.<br/>"
                                  "Setup cannot continue." )
                            : tr( "This computer does not satisfy the minimum "
                                  "requirements for installing %1.<br/>"
                                  "Installation cannot continue." );
        }
        else
        {
            message = setup ? tr( "This computer does not satisfy some of the "
                                  "recommended requirements for setting up %1.<br/>"
                                  "Setup can continue, but some features "
                                  "might be disabled." )
                            : tr( "This computer does not satisfy some of the "
                                  "recommended requirements for installing %1.<br/>"
                                  "Installation can continue, but some features "
                                  "might be disabled." );
        }

        m_warningMessage = message.arg( branding ? branding->shortVersionedName() : QString() );
    }
    else
    {
        m_warningMessage = tr( "This program will ask you some questions and "
                               "set up %2 on your computer." )
                               .arg( branding ? branding->productName() : QString() );
    }

    emit warningMessageChanged( m_warningMessage );
}

CalamaresUtils::Locale::TranslationsModel*
Config::languagesModel() const
{
    return m_languages;
}

Calamares::RequirementsModel*
Config::requirementsModel() const
{
    auto* manager = Calamares::ModuleManager::instance();
    return manager ? manager->requirementsModel() : nullptr;
}

QAbstractItemModel*
Config::unsatisfiedRequirements() const
{
    if ( !m_filtermodel->sourceModel() )
    {
        m_filtermodel->setFilterRole( Calamares::RequirementsModel::Roles::Satisfied );
        m_filtermodel->setFilterFixedString( QStringLiteral( "false" ) );
        m_filtermodel->setSourceModel( requirementsModel() );
    }
    return m_filtermodel.get();
}


QString
Config::languageIcon() const
{
    return m_languageIcon;
}

void
Config::initLanguages()
{
    // Find the best initial translation
    CalamaresUtils::Locale::Translation defaultTranslation;

    cDebug() << "Trying to match locale" << defaultTranslation.id();
    int matchedLocaleIndex = m_languages->find( defaultTranslation.id() );

    // Need to match by some other means than the exact translation Id
    if ( matchedLocaleIndex < 0 )
    {
        QLocale defaultLocale = defaultTranslation.locale();

        cDebug() << "Trying to match locale" << defaultLocale;
        matchedLocaleIndex = m_languages->find(
            [ & ]( const QLocale& x )
            { return x.language() == defaultLocale.language() && x.country() == defaultLocale.country(); } );

        if ( matchedLocaleIndex < 0 )
        {
            cDebug() << Logger::SubEntry << "Trying to match approximate locale" << defaultLocale.language();

            matchedLocaleIndex
                = m_languages->find( [ & ]( const QLocale& x ) { return x.language() == defaultLocale.language(); } );
        }

        if ( matchedLocaleIndex < 0 )
        {
            QLocale en_us( QLocale::English, QLocale::UnitedStates );

            cDebug() << Logger::SubEntry << "Trying to match English (US)";
            matchedLocaleIndex = m_languages->find( en_us );

            // Now, if it matched, because we didn't match the system locale, switch to the one found
            if ( matchedLocaleIndex >= 0 )
            {
                QLocale::setDefault( m_languages->locale( matchedLocaleIndex ).locale() );
            }
        }
    }

    if ( matchedLocaleIndex >= 0 )
    {
        setLocaleIndex( matchedLocaleIndex );
    }
    else
    {
        cWarning() << "No available translation matched" << defaultTranslation.id() << defaultTranslation.locale();
    }
}

void
Config::setCountryCode( const QString& countryCode )
{
    m_countryCode = countryCode;
    setLocaleIndex( CalamaresUtils::Locale::availableTranslations()->find( m_countryCode ) );

    emit countryCodeChanged( m_countryCode );
}

void
Config::setLanguageIcon( const QString& languageIcon )
{
    m_languageIcon = languageIcon;
}

void
Config::setLocaleIndex( int index )
{
    if ( index == m_localeIndex || index > CalamaresUtils::Locale::availableTranslations()->rowCount( QModelIndex() )
         || index < 0 )
    {
        return;
    }

    m_localeIndex = index;

    const auto& selectedTranslation = m_languages->locale( m_localeIndex );
    cDebug() << "Index" << index << "Selected locale" << selectedTranslation.id().name;

    QLocale::setDefault( selectedTranslation.locale() );
    const auto* branding = Calamares::Branding::instance();
    CalamaresUtils::installTranslator( selectedTranslation.id(),
                                       branding ? branding->translationsDirectory() : QString() );
    if ( Calamares::JobQueue::instance() && Calamares::JobQueue::instance()->globalStorage() )
    {
        CalamaresUtils::Locale::insertGS( *Calamares::JobQueue::instance()->globalStorage(),
                                          QStringLiteral( "LANG" ),
                                          CalamaresUtils::translatorLocaleName().name );
    }
    emit localeIndexChanged( m_localeIndex );
}

void
Config::setIsNextEnabled( bool isNextEnabled )
{
    m_isNextEnabled = isNextEnabled;
    emit isNextEnabledChanged( m_isNextEnabled );
}

void
Config::setDonateUrl( const QString& url )
{
    m_donateUrl = url;
    emit donateUrlChanged();
}

void
Config::setKnownIssuesUrl( const QString& url )
{
    m_knownIssuesUrl = url;
    emit knownIssuesUrlChanged();
}

void
Config::setReleaseNotesUrl( const QString& url )
{
    m_releaseNotesUrl = url;
    emit releaseNotesUrlChanged();
}

void
Config::setSupportUrl( const QString& url )
{
    m_supportUrl = url;
    emit supportUrlChanged();
}

QString
Config::aboutMessage() const
{
    return Calamares::aboutString();
}


QString
Config::genericWelcomeMessage() const
{
    QString message;

    const auto* settings = Calamares::Settings::instance();
    const auto* branding = Calamares::Branding::instance();
    const bool welcomeStyle = branding ? branding->welcomeStyleCalamares() : true;

    if ( settings ? settings->isSetupMode() : false )
    {
        message = welcomeStyle ? tr( "<h1>Welcome to the Calamares setup program for %1</h1>" )
                               : tr( "<h1>Welcome to %1 setup</h1>" );
    }
    else
    {
        message = welcomeStyle ? tr( "<h1>Welcome to the Calamares installer for %1</h1>" )
                               : tr( "<h1>Welcome to the %1 installer</h1>" );
    }

    return message;
}

QString
Config::warningMessage() const
{
    return m_warningMessage;
}

/** @brief Look up a URL for a button
 *
 * Looks up @p key in @p map; if it is a *boolean* value, then
 * assume an old-style configuration, and fetch the string from
 * the branding settings @p e. If it is a string, not a boolean,
 * use it as-is. If not found, or a weird type, returns empty.
 *
 * This allows switching the showKnownIssuesUrl and similar settings
 * in welcome.conf from a boolean (deferring to branding) to an
 * actual string for immediate use. Empty strings, as well as
 * "false" as a setting, will hide the buttons as before.
 */
static QString
jobOrBrandingSetting( Calamares::Branding::StringEntry e, const QVariantMap& map, const QString& key )
{
    if ( !map.contains( key ) )
    {
        return QString();
    }
    auto v = map.value( key );
    if ( v.type() == QVariant::Bool )
    {
        return v.toBool() ? ( Calamares::Branding::instance()->string( e ) ) : QString();
    }
    if ( v.type() == QVariant::String )
    {
        return v.toString();
    }

    return QString();
}

static inline void
setLanguageIcon( Config* c, const QVariantMap& configurationMap )
{
    QString language = CalamaresUtils::getString( configurationMap, "languageIcon" );
    if ( !language.isEmpty() )
    {
        auto icon = Calamares::Branding::instance()->image( language, QSize( 48, 48 ) );
        if ( !icon.isNull() )
        {
            c->setLanguageIcon( language );
        }
    }
}

static inline void
logGeoIPHandler( CalamaresUtils::GeoIP::Handler* handler )
{
    if ( handler )
    {
        cDebug() << Logger::SubEntry << "Obtained from" << handler->url() << " ("
                 << static_cast< int >( handler->type() ) << handler->selector() << ')';
    }
}

static void
setCountry( Config* config, const QString& countryCode, CalamaresUtils::GeoIP::Handler* handler )
{
    if ( countryCode.length() != 2 )
    {
        cDebug() << "Unusable country code" << countryCode;
        logGeoIPHandler( handler );
        return;
    }

    auto c_l = CalamaresUtils::Locale::countryData( countryCode );
    if ( c_l.first == QLocale::Country::AnyCountry )
    {
        cDebug() << "Unusable country code" << countryCode;
        logGeoIPHandler( handler );
        return;
    }
    else
    {
        int r = CalamaresUtils::Locale::availableTranslations()->find( countryCode );
        if ( r < 0 )
        {
            cDebug() << "Unusable country code" << countryCode << "(no suitable translation)";
        }
        if ( ( r >= 0 ) && config )
        {
            config->setCountryCode( countryCode );
        }
    }
}

static inline void
setGeoIP( Config* config, const QVariantMap& configurationMap )
{
    bool ok = false;
    QVariantMap geoip = CalamaresUtils::getSubMap( configurationMap, "geoip", ok );
    if ( ok )
    {
        using FWString = QFutureWatcher< QString >;

        auto* handler = new CalamaresUtils::GeoIP::Handler( CalamaresUtils::getString( geoip, "style" ),
                                                            CalamaresUtils::getString( geoip, "url" ),
                                                            CalamaresUtils::getString( geoip, "selector" ) );
        if ( handler->type() != CalamaresUtils::GeoIP::Handler::Type::None )
        {
            auto* future = new FWString();
            QObject::connect( future,
                              &FWString::finished,
                              [ config, future, handler ]()
                              {
                                  QString countryResult = future->future().result();
                                  cDebug() << "GeoIP result for welcome=" << countryResult;
                                  ::setCountry( config, countryResult, handler );
                                  future->deleteLater();
                                  delete handler;
                              } );
            future->setFuture( handler->queryRaw() );
        }
        else
        {
            // Would not produce useful country code anyway.
            delete handler;
        }
    }
}

void
Config::setConfigurationMap( const QVariantMap& configurationMap )
{
    using Calamares::Branding;

    setSupportUrl( jobOrBrandingSetting( Branding::SupportUrl, configurationMap, "showSupportUrl" ) );
    setKnownIssuesUrl( jobOrBrandingSetting( Branding::KnownIssuesUrl, configurationMap, "showKnownIssuesUrl" ) );
    setReleaseNotesUrl( jobOrBrandingSetting( Branding::ReleaseNotesUrl, configurationMap, "showReleaseNotesUrl" ) );
    setDonateUrl( jobOrBrandingSetting( Branding::DonateUrl, configurationMap, "showDonateUrl" ) );

    ::setLanguageIcon( this, configurationMap );
    ::setGeoIP( this, configurationMap );

    if ( configurationMap.contains( "requirements" )
         && configurationMap.value( "requirements" ).type() == QVariant::Map )
    {
        m_requirementsChecker->setConfigurationMap( configurationMap.value( "requirements" ).toMap() );
    }
    else
    {
        cWarning() << "no valid requirements map found in welcome "
                      "module configuration.";
    }
}
