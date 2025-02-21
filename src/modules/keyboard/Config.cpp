/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019-2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2020 Camilo Higuita <milo.h@aol.com> *
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "Config.h"

#include "SetKeyboardLayoutJob.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "locale/Global.h"
#include "utils/Logger.h"
#include "utils/RAII.h"
#include "utils/Retranslator.h"
#include "utils/String.h"
#include "utils/Variant.h"

#include <QApplication>
#include <QFile>
#include <QGuiApplication>
#include <QProcess>
#include <QRegularExpression>
#include <QStandardPaths>
#include <QTimer>

#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusReply>

/* Returns stringlist with suitable setxkbmap command-line arguments
 * to set the given @p model.
 */
static QStringList
xkbmap_model_args( const QString& model )
{
    QStringList r { "-model", model };
    return r;
}

/* Returns stringlist with suitable setxkbmap command-line arguments
 * to set the given @p layout and @p variant.
 */
static QStringList
xkbmap_layout_args( const QString& layout, const QString& variant )
{
    QStringList r { "-layout", layout };
    if ( !variant.isEmpty() )
    {
        r << "-variant" << variant;
    }
    return r;
}

static QStringList
xkbmap_layout_args_with_group_switch( const QStringList& layouts,
                                      const QStringList& variants,
                                      const QString& switchOption )
{
    if ( layouts.size() != variants.size() )
    {
        cError() << "Number of layouts and variants must be equal (empty string should be used if there is no "
                    "corresponding variant)";
        return QStringList();
    }

    QStringList r { "-layout", layouts.join( "," ) };

    if ( !variants.isEmpty() )
    {
        r << "-variant" << variants.join( "," );
    }

    if ( !switchOption.isEmpty() )
    {
        r << "-option" << switchOption;
    }

    return r;
}

/* Returns group-switch setxkbd option if set
 * or an empty string otherwise
 */
static inline QString
xkbmap_query_grp_option()
{
    QProcess setxkbmapQuery;
    setxkbmapQuery.start( "setxkbmap", { "-query" } );
    setxkbmapQuery.waitForFinished();

    QString outputLine;

    do
    {
        outputLine = setxkbmapQuery.readLine();
    } while ( setxkbmapQuery.canReadLine() && !outputLine.startsWith( "options:" ) );

    if ( !outputLine.startsWith( "options:" ) )
    {
        return QString();
    }

    int index = outputLine.indexOf( "grp:" );

    if ( index == -1 )
    {
        return QString();
    }

    //it's either in the end of line or before the other option so \s or ,
    int lastIndex = outputLine.indexOf( QRegularExpression( "[\\s,]" ), index );

    return outputLine.mid( index, lastIndex - index );
}

AdditionalLayoutInfo
Config::getAdditionalLayoutInfo( const QString& layout )
{
    QFile layoutTable( ":/non-ascii-layouts" );

    if ( !layoutTable.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        cError() << "Non-ASCII layout table could not be opened";
        return AdditionalLayoutInfo();
    }

    QString tableLine;

    do
    {
        tableLine = layoutTable.readLine();
    } while ( layoutTable.canReadLine() && !tableLine.startsWith( layout ) );

    if ( !tableLine.startsWith( layout ) )
    {
        return AdditionalLayoutInfo();
    }

    QStringList tableEntries = tableLine.split( " ", SplitSkipEmptyParts );

    AdditionalLayoutInfo r;

    r.additionalLayout = tableEntries[ 1 ];
    r.additionalVariant = tableEntries[ 2 ] == "-" ? "" : tableEntries[ 2 ];

    r.vconsoleKeymap = tableEntries[ 3 ];

    return r;
}

Config::Config( QObject* parent )
    : QObject( parent )
    , m_keyboardModelsModel( new KeyboardModelsModel( this ) )
    , m_keyboardLayoutsModel( new KeyboardLayoutModel( this ) )
    , m_keyboardVariantsModel( new KeyboardVariantsModel( this ) )
    , m_KeyboardGroupSwitcherModel( new KeyboardGroupsSwitchersModel( this ) )
{
    m_applyTimer.setSingleShot( true );
    connect( &m_applyTimer, &QTimer::timeout, this, &Config::apply );

    // Connect signals and slots
    connect( m_keyboardModelsModel,
             &KeyboardModelsModel::currentIndexChanged,
             [ & ]( int index )
             {
                 m_current.selectedModel = m_keyboardModelsModel->key( index );
                 somethingChanged();
             } );

    connect( m_keyboardLayoutsModel,
             &KeyboardLayoutModel::currentIndexChanged,
             [ & ]( int index )
             {
                 m_current.selectedLayout = m_keyboardLayoutsModel->item( index ).first;
                 updateVariants( QPersistentModelIndex( m_keyboardLayoutsModel->index( index ) ) );
                 emit prettyStatusChanged();
             } );

    connect( m_keyboardVariantsModel,
             &KeyboardVariantsModel::currentIndexChanged,
             [ & ]( int index )
             {
                 m_current.selectedVariant = m_keyboardVariantsModel->key( index );
                 somethingChanged();
             } );
    connect( m_KeyboardGroupSwitcherModel,
             &KeyboardGroupsSwitchersModel::currentIndexChanged,
             [ & ]( int index )
             {
                 m_current.selectedGroup = m_KeyboardGroupSwitcherModel->key( index );
                 somethingChanged();
             } );

    // If the user picks something explicitly -- not a consequence of
    // a guess -- then move to UserSelected state and stay there.
    connect( m_keyboardModelsModel, &KeyboardModelsModel::currentIndexChanged, this, &Config::selectionChange );
    connect( m_keyboardLayoutsModel, &KeyboardLayoutModel::currentIndexChanged, this, &Config::selectionChange );
    connect( m_keyboardVariantsModel, &KeyboardVariantsModel::currentIndexChanged, this, &Config::selectionChange );
    connect( m_KeyboardGroupSwitcherModel,
             &KeyboardGroupsSwitchersModel::currentIndexChanged,
             this,
             &Config::selectionChange );

    m_current.selectedModel = m_keyboardModelsModel->key( m_keyboardModelsModel->currentIndex() );
    m_current.selectedLayout = m_keyboardLayoutsModel->item( m_keyboardLayoutsModel->currentIndex() ).first;
    m_current.selectedVariant = m_keyboardVariantsModel->key( m_keyboardVariantsModel->currentIndex() );
    m_current.selectedGroup = m_KeyboardGroupSwitcherModel->key( m_KeyboardGroupSwitcherModel->currentIndex() );
}

void
Config::somethingChanged()
{
    if ( m_applyTimer.isActive() )
    {
        m_applyTimer.stop();
    }
    m_applyTimer.start( QApplication::keyboardInputInterval() );
    emit prettyStatusChanged();
}

static void
applyXkb( const BasicLayoutInfo& settings, AdditionalLayoutInfo& extra )
{
    QStringList basicArguments = xkbmap_model_args( settings.selectedModel );
    if ( !extra.additionalLayout.isEmpty() )
    {
        if ( !settings.selectedGroup.isEmpty() )
        {
            extra.groupSwitcher = "grp:" + settings.selectedGroup;
        }

        if ( extra.groupSwitcher.isEmpty() )
        {
            extra.groupSwitcher = xkbmap_query_grp_option();
        }
        if ( extra.groupSwitcher.isEmpty() )
        {
            extra.groupSwitcher = "grp:alt_shift_toggle";
        }

        basicArguments.append(
            xkbmap_layout_args_with_group_switch( { extra.additionalLayout, settings.selectedLayout },
                                                  { extra.additionalVariant, settings.selectedVariant },
                                                  extra.groupSwitcher ) );
        QProcess::execute( "setxkbmap", basicArguments );

        cDebug() << "xkbmap selection changed to: " << settings.selectedLayout << '-' << settings.selectedVariant
                 << "(added " << extra.additionalLayout << "-" << extra.additionalVariant
                 << " since current layout is not ASCII-capable)";
    }
    else
    {
        basicArguments.append( xkbmap_layout_args( settings.selectedLayout, settings.selectedVariant ) );
        QProcess::execute( "setxkbmap", basicArguments );
        cDebug() << "xkbmap selection changed to: " << settings.selectedLayout << '-' << settings.selectedVariant;
    }
}

static void
applyLocale1( const BasicLayoutInfo& settings, AdditionalLayoutInfo& extra )
{
    QString layout = settings.selectedLayout;
    QString variant = settings.selectedVariant;
    QString option;

    if ( !extra.additionalLayout.isEmpty() )
    {
        layout = extra.additionalLayout + "," + layout;
        variant = extra.additionalVariant + "," + variant;
        option = extra.groupSwitcher;
    }

    QDBusInterface locale1( "org.freedesktop.locale1",
                            "/org/freedesktop/locale1",
                            "org.freedesktop.locale1",
                            QDBusConnection::systemBus() );
    if ( !locale1.isValid() )
    {
        cWarning() << "Interface" << locale1.interface() << "is not valid.";
        return;
    }

    // Using convert=true, this also updates the VConsole config
    {
        QDBusReply< void > r
            = locale1.call( "SetX11Keyboard", layout, settings.selectedModel, variant, option, true, false );
        if ( !r.isValid() )
        {
            cWarning() << "Could not set keyboard config through org.freedesktop.locale1.X11Keyboard." << r.error();
        }
    }
}

// In a config-file's list of lines, replace lines <key>=<something> by <key>=<value>
static void
replaceKey( QStringList& content, const QString& key, const QString& value )
{
    for ( int i = 0; i < content.length(); ++i )
    {
        if ( content.at( i ).startsWith( key ) )
        {
            content[ i ] = key + value;
        }
    }
}

static bool
rewriteKWin( const QString& path, const QString& model, const QString& layouts, const QString& variants )
{
    if ( !QFile::exists( path ) )
    {
        return false;
    }

    QFile config( path );
    if ( !config.open( QIODevice::ReadOnly ) )
    {
        return false;
    }
    QStringList content = []( QFile& f )
    {
        QTextStream s( &f );
        return s.readAll().split( '\n' );
    }( config );
    config.close();

    if ( !config.open( QIODevice::WriteOnly ) )
    {
        return false;
    }

    replaceKey( content, QStringLiteral( "Model=" ), model );
    replaceKey( content, QStringLiteral( "LayoutList=" ), layouts );
    replaceKey( content, QStringLiteral( "VariantList=" ), variants );

    config.write( content.join( '\n' ).toUtf8() );
    config.close();

    return true;
}

void
applyKWin( const BasicLayoutInfo& settings, AdditionalLayoutInfo& extra )
{
    const auto paths = QStandardPaths::standardLocations( QStandardPaths::ConfigLocation );

    auto join = [ &additional = extra.additionalLayout ]( const QString& s1, const QString& s2 )
    { return additional.isEmpty() ? s1 : QStringLiteral( "%1,%2" ).arg( s1, s2 ); };

    const QString layouts = join( settings.selectedLayout, extra.additionalLayout );
    const QString variants = join( settings.selectedVariant, extra.additionalVariant );

    bool updated = false;
    for ( const auto& path : paths )
    {
        const QString candidate = path + QStringLiteral( "/kxkbrc" );
        if ( rewriteKWin( candidate, settings.selectedModel, layouts, variants ) )
        {
            updated = true;
            break;
        }
    }

    if ( updated )
    {
        auto kwin = QDBusMessage::createSignal(
            QStringLiteral( "/Layouts" ), QStringLiteral( "org.kde.keyboard" ), QStringLiteral( "reloadConfig" ) );
        QDBusConnection::sessionBus().send( kwin );
    }
}

void
Config::apply()
{
    m_additionalLayoutInfo = getAdditionalLayoutInfo( m_current.selectedLayout );
    if ( m_configureXkb )
    {
        applyXkb( m_current, m_additionalLayoutInfo );
    }
    if ( m_configureLocale1 )
    {
        applyLocale1( m_current, m_additionalLayoutInfo );
    }
    if ( m_configureKWin )
    {
        applyKWin( m_current, m_additionalLayoutInfo );
    }
    m_applyTimer.stop();
    // Writing /etc/ files is not needed "live"
}

KeyboardModelsModel*
Config::keyboardModels() const
{
    return m_keyboardModelsModel;
}

KeyboardLayoutModel*
Config::keyboardLayouts() const
{
    return m_keyboardLayoutsModel;
}

KeyboardVariantsModel*
Config::keyboardVariants() const
{
    return m_keyboardVariantsModel;
}

KeyboardGroupsSwitchersModel*
Config::keyboardGroupsSwitchers() const
{
    return m_KeyboardGroupSwitcherModel;
}

static QPersistentModelIndex
findLayout( const KeyboardLayoutModel* klm, const QString& currentLayout )
{
    QPersistentModelIndex currentLayoutItem;

    for ( int i = 0; i < klm->rowCount(); ++i )
    {
        QModelIndex idx = klm->index( i );
        if ( idx.isValid() && idx.data( KeyboardLayoutModel::KeyboardLayoutKeyRole ).toString() == currentLayout )
        {
            currentLayoutItem = idx;
        }
    }

    return currentLayoutItem;
}

void
Config::getCurrentKeyboardLayoutXkb( QString& currentLayout, QString& currentVariant, QString& currentModel )
{
    QProcess process;
    process.start( "setxkbmap", QStringList() << "-print" );
    if ( process.waitForFinished() )
    {
        const QStringList list = QString( process.readAll() ).split( "\n", SplitSkipEmptyParts );

        // A typical line looks like
        //      xkb_symbols   { include "pc+latin+ru:2+inet(evdev)+group(alt_shift_toggle)+ctrl(swapcaps)"       };
        for ( const auto& line : list )
        {
            bool symbols = false;
            if ( line.trimmed().startsWith( "xkb_symbols" ) )
            {
                symbols = true;
            }
            else if ( !line.trimmed().startsWith( "xkb_geometry" ) )
            {
                continue;
            }

            int firstQuote = line.indexOf( '"' );
            int lastQuote = line.lastIndexOf( '"' );

            if ( firstQuote < 0 || lastQuote < 0 || lastQuote <= firstQuote )
            {
                continue;
            }

            QStringList split = line.mid( firstQuote + 1, lastQuote - firstQuote ).split( "+", SplitSkipEmptyParts );
            cDebug() << split;
            if ( symbols && split.size() >= 2 )
            {
                currentLayout = split.at( 1 );

                if ( currentLayout.contains( "(" ) )
                {
                    int parenthesisIndex = currentLayout.indexOf( "(" );
                    currentVariant = currentLayout.mid( parenthesisIndex + 1 ).trimmed();
                    currentVariant.chop( 1 );
                    currentLayout = currentLayout.mid( 0, parenthesisIndex ).trimmed();
                }

                break;
            }
            else if ( !symbols && split.size() >= 1 )
            {
                currentModel = split.at( 0 );
                if ( currentModel.contains( "(" ) )
                {
                    int parenthesisIndex = currentLayout.indexOf( "(" );
                    currentModel = currentModel.mid( parenthesisIndex + 1 ).trimmed();
                    currentModel.chop( 1 );
                }
            }
        }
    }
}

void
Config::getCurrentKeyboardLayoutLocale1( QString& currentLayout, QString& currentVariant, QString& currentModel )
{
    QDBusInterface locale1( "org.freedesktop.locale1",
                            "/org/freedesktop/locale1",
                            "org.freedesktop.locale1",
                            QDBusConnection::systemBus() );
    if ( !locale1.isValid() )
    {
        cWarning() << "Interface" << locale1.interface() << "is not valid.";
        return;
    }

    currentLayout = locale1.property( "X11Layout" ).toString().split( "," ).last();
    currentVariant = locale1.property( "X11Variant" ).toString().split( "," ).last();
    currentModel = locale1.property( "X11Model" ).toString();
}

void
Config::detectCurrentKeyboardLayout()
{
    if ( m_state != State::Initial )
    {
        return;
    }
    cScopedAssignment returnToIntial( &m_state, State::Initial );
    m_state = State::Guessing;

    //### Detect current keyboard layout, variant, and model
    QString currentLayout;
    QString currentVariant;
    QString currentModel;

    if ( m_configureLocale1 )
    {
        getCurrentKeyboardLayoutLocale1( currentLayout, currentVariant, currentModel );
    }
    else
    {
        getCurrentKeyboardLayoutXkb( currentLayout, currentVariant, currentModel );
    }

    //### Layouts and Variants
    QPersistentModelIndex currentLayoutItem = findLayout( m_keyboardLayoutsModel, currentLayout );
    if ( !currentLayoutItem.isValid() && ( ( currentLayout == "latin" ) || ( currentLayout == "pc" ) ) )
    {
        currentLayout = "us";
        currentLayoutItem = findLayout( m_keyboardLayoutsModel, currentLayout );
    }

    // Set current layout and variant
    if ( currentLayoutItem.isValid() )
    {
        m_keyboardLayoutsModel->setCurrentIndex( currentLayoutItem.row() );
        updateVariants( currentLayoutItem, currentVariant );
    }

    // Default to the first available layout if none was set
    // Do this after unblocking signals so we get the default variant handling.
    if ( !currentLayoutItem.isValid() && m_keyboardLayoutsModel->rowCount() > 0 )
    {
        m_keyboardLayoutsModel->setCurrentIndex( m_keyboardLayoutsModel->index( 0 ).row() );
    }

    //### Keyboard model
    for ( int i = 0; i < m_keyboardModelsModel->rowCount(); ++i )
    {
        QModelIndex idx = m_keyboardModelsModel->index( i );
        if ( idx.isValid() && idx.data( XKBListModel::KeyRole ).toString() == currentModel )
        {
            m_keyboardModelsModel->setCurrentIndex( idx.row() );
            break;
        }
    }
    // The models have updated the m_current settings, copy them
    m_original = m_current;
}

void
Config::cancel()
{
    const auto extra = getAdditionalLayoutInfo( m_original.selectedLayout );
    if ( m_configureXkb )
    {
        applyXkb( m_original, m_additionalLayoutInfo );
    }
    if ( m_configureLocale1 )
    {
        applyLocale1( m_original, m_additionalLayoutInfo );
    }
    if ( m_configureKWin )
    {
        applyKWin( m_original, m_additionalLayoutInfo );
    }
}

QString
Config::prettyStatus() const
{
    QString status
        = tr( "Keyboard model has been set to %1.", "@label, %1 is keyboard model, as in Apple Magic Keyboard" )
              .arg( m_keyboardModelsModel->label( m_keyboardModelsModel->currentIndex() ) );
    status += QStringLiteral( "<br/>" );

    QString layout = m_keyboardLayoutsModel->item( m_keyboardLayoutsModel->currentIndex() ).second.description;
    QString variant = m_keyboardVariantsModel->currentIndex() >= 0
        ? m_keyboardVariantsModel->label( m_keyboardVariantsModel->currentIndex() )
        : QString( "<default>" );
    status += tr( "Keyboard layout has been set to %1/%2.", "@label, %1 is layout, %2 is layout variant" )
                  .arg( layout, variant );

    return status;
}

Calamares::JobList
Config::createJobs()
{
    QList< Calamares::job_ptr > list;

    Calamares::Job* j = new SetKeyboardLayoutJob( m_current.selectedModel,
                                                  m_current.selectedLayout,
                                                  m_current.selectedVariant,
                                                  m_additionalLayoutInfo,
                                                  m_xOrgConfFileName,
                                                  m_convertedKeymapPath,
                                                  m_configureEtcDefaultKeyboard,
                                                  m_configureLocale1 );
    list.append( Calamares::job_ptr( j ) );

    return list;
}

static void
guessLayout( const QStringList& langParts, KeyboardLayoutModel* layouts, KeyboardVariantsModel* variants )
{
    bool foundCountryPart = false;
    for ( auto countryPart = langParts.rbegin(); !foundCountryPart && countryPart != langParts.rend(); ++countryPart )
    {
        cDebug() << Logger::SubEntry << "looking for locale part" << *countryPart;
        for ( int i = 0; i < layouts->rowCount(); ++i )
        {
            QModelIndex idx = layouts->index( i );
            QString name
                = idx.isValid() ? idx.data( KeyboardLayoutModel::KeyboardLayoutKeyRole ).toString() : QString();
            if ( idx.isValid() && ( name.compare( *countryPart, Qt::CaseInsensitive ) == 0 ) )
            {
                cDebug() << Logger::SubEntry << "matched" << name;
                layouts->setCurrentIndex( i );
                foundCountryPart = true;
                break;
            }
        }
        if ( foundCountryPart )
        {
            ++countryPart;
            if ( countryPart != langParts.rend() )
            {
                cDebug() << "Next level:" << *countryPart;
                for ( int variantnumber = 0; variantnumber < variants->rowCount(); ++variantnumber )
                {
                    if ( variants->key( variantnumber ).compare( *countryPart, Qt::CaseInsensitive ) == 0 )
                    {
                        variants->setCurrentIndex( variantnumber );
                        cDebug() << Logger::SubEntry << "matched variant" << *countryPart << ' '
                                 << variants->key( variantnumber );
                    }
                }
            }
        }
    }
}

void
Config::guessLocaleKeyboardLayout()
{
    if ( m_state != State::Initial || !m_guessLayout )
    {
        return;
    }
    cScopedAssignment returnToIntial( &m_state, State::Initial );
    m_state = State::Guessing;

    /* Guessing a keyboard layout based on the locale means
     * mapping between language identifiers in <lang>_<country>
     * format to keyboard mappings, which are <country>_<layout>
     * format; in addition, some countries have multiple languages,
     * so fr_BE and nl_BE want different layouts (both Belgian)
     * and sometimes the language-country name doesn't match the
     * keyboard-country name at all (e.g. Ellas vs. Greek).
     *
     * This is a table of language-to-keyboard mappings. The
     * language identifier is the key, while the value is
     * a string that is used instead of the real language
     * identifier in guessing -- so it should be something
     * like <layout>_<country>.
     */
    static constexpr char arabic[] = "ara";
    static const auto specialCaseMap = QMap< std::string, std::string >( {
        /* Most Arab countries map to Arabic keyboard (Default) */
        { "ar_AE", arabic },
        { "ar_BH", arabic },
        { "ar_DZ", arabic },
        { "ar_EG", arabic },
        { "ar_IN", arabic },
        { "ar_IQ", arabic },
        { "ar_JO", arabic },
        { "ar_KW", arabic },
        { "ar_LB", arabic },
        { "ar_LY", arabic },
        /* Not Morocco: use layout ma */
        { "ar_OM", arabic },
        { "ar_QA", arabic },
        { "ar_SA", arabic },
        { "ar_SD", arabic },
        { "ar_SS", arabic },
        /* Not Syria: use layout sy */
        { "ar_TN", arabic },
        { "ar_YE", arabic },
        { "ca_ES", "cat_ES" }, /* Catalan */
        { "en_CA", "us" }, /* Canadian English */
        { "el_CY", "gr" }, /* Greek in Cyprus */
        { "el_GR", "gr" }, /* Greek in Greece */
        { "ig_NG", "igbo_NG" }, /* Igbo in Nigeria */
        { "ha_NG", "hausa_NG" }, /* Hausa */
        { "en_IN", "us" }, /* India, US English keyboards are common in India */
    } );

    // Try to preselect a layout, depending on language and locale
    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
    QString lang = Calamares::Locale::readGS( *gs, QStringLiteral( "LANG" ) );

    cDebug() << "Got locale language" << lang;
    if ( !lang.isEmpty() )
    {
        // Chop off .codeset and @modifier
        int index = lang.indexOf( '.' );
        if ( index >= 0 )
        {
            lang.truncate( index );
        }
        index = lang.indexOf( '@' );
        if ( index >= 0 )
        {
            lang.truncate( index );
        }

        lang.replace( '-', '_' );  // Normalize separators
    }
    if ( !lang.isEmpty() )
    {
        std::string lang_s = lang.toStdString();
        if ( specialCaseMap.contains( lang_s ) )
        {
            QString newLang = QString::fromStdString( specialCaseMap.value( lang_s ) );
            cDebug() << Logger::SubEntry << "special case language" << lang << "becomes" << newLang;
            lang = newLang;
        }
    }
    if ( !lang.isEmpty() )
    {
        guessLayout( lang.split( '_', SplitSkipEmptyParts ), m_keyboardLayoutsModel, m_keyboardVariantsModel );
    }
}

void
Config::finalize()
{
    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
    if ( !m_current.selectedLayout.isEmpty() )
    {
        gs->insert( "keyboardLayout", m_current.selectedLayout );
        gs->insert( "keyboardVariant", m_current.selectedVariant );  //empty means default variant

        if ( !m_additionalLayoutInfo.additionalLayout.isEmpty() )
        {
            gs->insert( "keyboardAdditionalLayout", m_additionalLayoutInfo.additionalLayout );
            gs->insert( "keyboardAdditionalVariant", m_additionalLayoutInfo.additionalVariant );
            gs->insert( "keyboardGroupSwitcher", m_additionalLayoutInfo.groupSwitcher );
            gs->insert( "keyboardVConsoleKeymap", m_additionalLayoutInfo.vconsoleKeymap );
        }
    }

    //FIXME: also store keyboard model for something?
}

void
Config::updateVariants( const QPersistentModelIndex& currentItem, QString currentVariant )
{
    const auto variants = m_keyboardLayoutsModel->item( currentItem.row() ).second.variants;
    m_keyboardVariantsModel->setVariants( variants );

    auto index = -1;
    for ( const auto& key : variants.keys() )
    {
        index++;
        if ( variants[ key ] == currentVariant )
        {
            m_keyboardVariantsModel->setCurrentIndex( index );
            return;
        }
    }
}

void
Config::setConfigurationMap( const QVariantMap& configurationMap )
{
    using namespace Calamares;
    bool isX11 = QGuiApplication::platformName() == "xcb";

    const auto xorgConfDefault = QStringLiteral( "00-keyboard.conf" );
    m_xOrgConfFileName = getString( configurationMap, "xOrgConfFileName", xorgConfDefault );
    if ( m_xOrgConfFileName.isEmpty() )
    {
        m_xOrgConfFileName = xorgConfDefault;
    }
    m_convertedKeymapPath = getString( configurationMap, "convertedKeymapPath" );
    m_configureEtcDefaultKeyboard = getBool( configurationMap, "writeEtcDefaultKeyboard", true );
    m_configureLocale1 = getBool( configurationMap, "useLocale1", !isX11 );

    bool bogus = false;
    const auto configureItems = getSubMap( configurationMap, "configure", bogus );
    m_configureKWin = getBool( configureItems, "kwin", false );

    m_guessLayout = getBool( configurationMap, "guessLayout", true );
}

void
Config::retranslate()
{
    retranslateKeyboardModels();
}

void
Config::selectionChange()
{
    if ( m_state == State::Initial )
    {
        m_state = State::UserSelected;
    }
}
