/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017-2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2018 Raul Rodrigo Segura (raurodse)
 *   SPDX-FileCopyrightText: 2019 Camilo Higuita <milo.h@aol.com>
 *   SPDX-FileCopyrightText: 2021 Anubhav Choudhary <ac.10edu@gmail.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "Branding.h"

#include "GlobalStorage.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/ImageRegistry.h"
#include "utils/Logger.h"
#include "utils/NamedEnum.h"
#include "utils/Units.h"
#include "utils/Yaml.h"

#include <QDir>
#include <QFile>
#include <QIcon>
#include <QMetaEnum>
#include <QPixmap>
#include <QVariantMap>

#include <functional>

#ifdef WITH_KOSRelease
#include <KMacroExpander>
#include <KOSRelease>
#endif

[[noreturn]] static void
bail( const QString& descriptorPath, const QString& message )
{
    cError() << "FATAL in" << descriptorPath << Logger::Continuation << Logger::NoQuote << message;
    ::exit( EXIT_FAILURE );
}

namespace Calamares
{

Branding* Branding::s_instance = nullptr;

Branding*
Branding::instance()
{
    if ( !s_instance )
    {
        cWarning() << "No Branding instance created yet.";
    }
    return s_instance;
}


// *INDENT-OFF*
// clang-format off
const QStringList Branding::s_stringEntryStrings =
{
    "productName",
    "version",
    "shortVersion",
    "versionedName",
    "shortVersionedName",
    "shortProductName",
    "bootloaderEntryName",
    "productUrl",
    "supportUrl",
    "knownIssuesUrl",
    "releaseNotesUrl",
    "donateUrl"
};


const QStringList Branding::s_imageEntryStrings =
{
    "productBanner",
    "productIcon",
    "productLogo",
    "productWallpaper",
    "productWelcome"
};

const QStringList Branding::s_uploadServerStrings =
{
    "type",
    "url",
    "port"
};
// clang-format on
// *INDENT-ON*

/** @brief Check that all the entries in the @p style map make sense
 *
 * This will catch typo's in key names.
 */
static bool
validateStyleEntries( const QMap< QString, QString >& style )
{
    using SE = Branding::StyleEntry;

    Logger::Once o;
    bool valid = true;

    const auto meta = QMetaEnum::fromType< SE >();
    QSet< QString > validNames;
    for ( SE i : { SE::SidebarBackground, SE::SidebarBackgroundCurrent, SE::SidebarText, SE::SidebarTextCurrent } )
    {
        validNames.insert( meta.valueToKey( i ) );
    }

    for ( const auto& k : style.keys() )
    {
        if ( !validNames.contains( k ) )
        {
            cWarning() << o << "Unknown branding *style* entry" << k;
            valid = false;
        }
    }

    return valid;
}

const NamedEnumTable< Branding::WindowDimensionUnit >&
Branding::WindowDimension::suffixes()
{
    using Unit = Branding::WindowDimensionUnit;
    // *INDENT-OFF*
    // clang-format off
    static const NamedEnumTable<Unit> names{
        {"px", Unit::Pixies},
        {"em", Unit::Fonties}
    };
    // clang-format on
    // *INDENT-ON*

    return names;
}

/** @brief Load the @p map with strings from @p doc
 *
 * Each key-value pair from the sub-map in @p doc identified by @p key
 * is inserted into the @p map, but the value is first transformed by
 * the @p transform function, which may change strings.
 */
static void
loadStrings( QMap< QString, QString >& map,
             const YAML::Node& doc,
             const std::string& key,
             const std::function< QString( const QString& ) >& transform )
{
    if ( !doc[ key ].IsMap() )
    {
        throw YAML::Exception( YAML::Mark(), std::string( "Branding configuration is not a map: " ) + key );
    }

    const QVariantMap config = CalamaresUtils::yamlMapToVariant( doc[ key ] );
    for ( auto it = config.constBegin(); it != config.constEnd(); ++it )
    {
        map.insert( it.key(), transform( it.value().toString() ) );
    }
}

static Branding::UploadServerInfo
uploadServerFromMap( const QVariantMap& map )
{
    using Type = Branding::UploadServerType;
    // *INDENT-OFF*
    // clang-format off
    static const NamedEnumTable< Type > names {
        { "none", Type::None },
        { "fiche", Type::Fiche }
    };
    // clang-format on
    // *INDENT-ON*

    QString typestring = map[ "type" ].toString();
    QString urlstring = map[ "url" ].toString();
    qint64 sizeLimitKiB = map[ "sizeLimit" ].toLongLong();

    if ( typestring.isEmpty() || urlstring.isEmpty() )
    {
        return Branding::UploadServerInfo { Branding::UploadServerType::None, QUrl(), 0 };
    }

    bool bogus = false;  // we don't care about type-name lookup success here
    return Branding::UploadServerInfo {
        names.find( typestring, bogus ),
        QUrl( urlstring, QUrl::ParsingMode::StrictMode ),
        sizeLimitKiB >= 0 ? CalamaresUtils::KiBtoBytes( static_cast< unsigned long long >( sizeLimitKiB ) ) : -1
    };
}

/** @brief Load the @p map with strings from @p config
 *
 * If os-release is supported (with KF5 CoreAddons >= 5.58) then
 * special substitutions can be done as well. See the branding
 * documentation for details.
 */

Branding::Branding( const QString& brandingFilePath, QObject* parent )
    : QObject( parent )
    , m_descriptorPath( brandingFilePath )
    , m_slideshowAPI( 1 )
    , m_welcomeStyleCalamares( false )
    , m_welcomeExpandingLogo( true )
{
    cDebug() << "Using Calamares branding file at" << brandingFilePath;

    QDir componentDir( componentDirectory() );
    if ( !componentDir.exists() )
    {
        bail( m_descriptorPath, "Bad component directory path." );
    }

    QFile file( brandingFilePath );
    if ( file.exists() && file.open( QFile::ReadOnly | QFile::Text ) )
    {
        QByteArray ba = file.readAll();

        try
        {
            YAML::Node doc = YAML::Load( ba.constData() );
            Q_ASSERT( doc.IsMap() );

            m_componentName = QString::fromStdString( doc[ "componentName" ].as< std::string >() );
            if ( m_componentName != componentDir.dirName() )
                bail( m_descriptorPath,
                      "The branding component name should match the name of the "
                      "component directory." );

            initSimpleSettings( doc );
            initSlideshowSettings( doc );

#ifdef WITH_KOSRelease
            // Copy the os-release information into a QHash for use by KMacroExpander.
            KOSRelease relInfo;

            QHash< QString, QString > relMap { std::initializer_list< std::pair< QString, QString > > {
                { QStringLiteral( "NAME" ), relInfo.name() },
                { QStringLiteral( "VERSION" ), relInfo.version() },
                { QStringLiteral( "ID" ), relInfo.id() },
                { QStringLiteral( "ID_LIKE" ), relInfo.idLike().join( ' ' ) },
                { QStringLiteral( "VERSION_CODENAME" ), relInfo.versionCodename() },
                { QStringLiteral( "VERSION_ID" ), relInfo.versionId() },
                { QStringLiteral( "PRETTY_NAME" ), relInfo.prettyName() },
                { QStringLiteral( "HOME_URL" ), relInfo.homeUrl() },
                { QStringLiteral( "DOCUMENTATION_URL" ), relInfo.documentationUrl() },
                { QStringLiteral( "SUPPORT_URL" ), relInfo.supportUrl() },
                { QStringLiteral( "BUG_REPORT_URL" ), relInfo.bugReportUrl() },
                { QStringLiteral( "PRIVACY_POLICY_URL" ), relInfo.privacyPolicyUrl() },
                { QStringLiteral( "BUILD_ID" ), relInfo.buildId() },
                { QStringLiteral( "VARIANT" ), relInfo.variant() },
                { QStringLiteral( "VARIANT_ID" ), relInfo.variantId() },
                { QStringLiteral( "LOGO" ), relInfo.logo() } } };
            auto expand = [ & ]( const QString& s ) -> QString
            { return KMacroExpander::expandMacros( s, relMap, QLatin1Char( '@' ) ); };
#else
            auto expand = []( const QString& s ) -> QString { return s; };
#endif
            // Massage the strings, images and style sections.
            loadStrings( m_strings, doc, "strings", expand );
            loadStrings( m_images,
                         doc,
                         "images",
                         [ & ]( const QString& s ) -> QString
                         {
                             // See also image()
                             const QString imageName( expand( s ) );
                             QFileInfo imageFi( componentDir.absoluteFilePath( imageName ) );
                             if ( !imageFi.exists() )
                             {
                                 const auto icon = QIcon::fromTheme( imageName );
                                 // Not found, bail out with the filename used
                                 if ( icon.isNull() )
                                 {
                                     bail(
                                         m_descriptorPath,
                                         QString( "Image file %1 does not exist." ).arg( imageFi.absoluteFilePath() ) );
                                 }
                                 return imageName;  // Not turned into a path
                             }
                             return imageFi.absoluteFilePath();
                         } );
            loadStrings( m_style, doc, "style", []( const QString& s ) -> QString { return s; } );

            m_uploadServer = uploadServerFromMap( CalamaresUtils::yamlMapToVariant( doc[ "uploadServer" ] ) );
        }
        catch ( YAML::Exception& e )
        {
            CalamaresUtils::explainYamlException( e, ba, file.fileName() );
            bail( m_descriptorPath, e.what() );
        }

        QDir translationsDir( componentDir.filePath( "lang" ) );
        if ( !translationsDir.exists() )
        {
            cWarning() << "the branding component" << componentDir.absolutePath() << "does not ship translations.";
        }
        m_translationsPathPrefix = translationsDir.absolutePath();
        m_translationsPathPrefix.append( QString( "%1calamares-%2" ).arg( QDir::separator() ).arg( m_componentName ) );
    }
    else
    {
        cWarning() << "Cannot read branding file" << file.fileName();
    }

    s_instance = this;
    if ( m_componentName.isEmpty() )
    {
        cWarning() << "Failed to load component from" << brandingFilePath;
    }
    else
    {
        cDebug() << "Loaded branding component" << m_componentName;
    }
    validateStyleEntries( m_style );
}


QString
Branding::componentDirectory() const
{
    QFileInfo fi( m_descriptorPath );
    return fi.absoluteDir().absolutePath();
}


QString
Branding::string( Branding::StringEntry stringEntry ) const
{
    return m_strings.value( s_stringEntryStrings.value( stringEntry ) );
}


QString
Branding::styleString( Branding::StyleEntry styleEntry ) const
{
    const auto meta = QMetaEnum::fromType< Branding::StyleEntry >();
    return m_style.value( meta.valueToKey( styleEntry ) );
}


QString
Branding::imagePath( Branding::ImageEntry imageEntry ) const
{
    return m_images.value( s_imageEntryStrings.value( imageEntry ) );
}

QPixmap
Branding::image( Branding::ImageEntry imageEntry, const QSize& size ) const
{
    const auto path = imagePath( imageEntry );
    if ( path.contains( '/' ) )
    {
        QPixmap pixmap = ImageRegistry::instance()->pixmap( path, size );

        Q_ASSERT( !pixmap.isNull() );
        return pixmap;
    }
    else
    {
        auto icon = QIcon::fromTheme( path );

        Q_ASSERT( !icon.isNull() );
        return icon.pixmap( size );
    }
}

QPixmap
Branding::image( const QString& imageName, const QSize& size ) const
{
    QDir componentDir( componentDirectory() );
    QFileInfo imageFi( componentDir.absoluteFilePath( imageName ) );
    if ( imageFi.exists() )
    {
        return ImageRegistry::instance()->pixmap( imageFi.absoluteFilePath(), size );
    }
    else
    {
        const auto icon = QIcon::fromTheme( imageName );
        // Not found, bail out with the filename used
        if ( !icon.isNull() )
        {
            return icon.pixmap( size );
        }
    }
    return QPixmap();
}

QPixmap
Branding::image( const QStringList& list, const QSize& size ) const
{
    QDir componentDir( componentDirectory() );
    for ( const QString& imageName : list )
    {
        auto p = image( imageName, size );
        if ( !p.isNull() )
        {
            return p;
        }
    }
    return QPixmap();
}


static QString
_stylesheet( const QDir& dir )
{
    QFileInfo importQSSPath( dir.filePath( "stylesheet.qss" ) );
    if ( importQSSPath.exists() && importQSSPath.isReadable() )
    {
        QFile stylesheetFile( importQSSPath.filePath() );
        stylesheetFile.open( QFile::ReadOnly );
        return stylesheetFile.readAll();
    }
    else
    {
        cWarning() << "The branding component" << dir.absolutePath() << "does not ship stylesheet.qss.";
    }
    return QString();
}

QString
Branding::stylesheet() const
{
    return _stylesheet( QFileInfo( m_descriptorPath ).absoluteDir() );
}

void
Branding::setGlobals( GlobalStorage* globalStorage ) const
{
    QVariantMap brandingMap;
    for ( const QString& key : s_stringEntryStrings )
    {
        brandingMap.insert( key, m_strings.value( key ) );
    }
    globalStorage->insert( "branding", brandingMap );
}

bool
Branding::WindowDimension::isValid() const
{
    return ( unit() != none ) && ( value() > 0 );
}


/// @brief Get a string (empty is @p key doesn't exist) from @p key in @p doc
static inline QString
getString( const YAML::Node& doc, const char* key )
{
    if ( doc[ key ] )
    {
        return QString::fromStdString( doc[ key ].as< std::string >() );
    }
    return QString();
}

/// @brief Get a node (throws if @p key doesn't exist) from @p key in @p doc
static inline YAML::Node
get( const YAML::Node& doc, const char* key )
{
    auto r = doc[ key ];
    if ( !r.IsDefined() )
    {
        throw YAML::KeyNotFound( YAML::Mark::null_mark(), std::string( key ) );
    }
    return r;
}

static inline void
flavorAndSide( const YAML::Node& doc, const char* key, Branding::PanelFlavor& flavor, Branding::PanelSide& side )
{
    using PanelFlavor = Branding::PanelFlavor;
    using PanelSide = Branding::PanelSide;

    // *INDENT-OFF*
    // clang-format off
    static const NamedEnumTable< PanelFlavor > sidebarFlavorNames {
        { QStringLiteral( "widget" ), PanelFlavor::Widget },
        { QStringLiteral( "none" ), PanelFlavor::None },
        { QStringLiteral( "hidden" ), PanelFlavor::None }
#ifdef WITH_QML
        ,
        { QStringLiteral( "qml" ), PanelFlavor::Qml }
#endif
    };
    static const NamedEnumTable< PanelSide > panelSideNames {
        { QStringLiteral( "left" ), PanelSide::Left },
        { QStringLiteral( "right" ), PanelSide::Right },
        { QStringLiteral( "top" ), PanelSide::Top },
        { QStringLiteral( "bottom" ), PanelSide::Bottom }
    };
    // clang-format on
    // *INDENT-ON*

    bool ok = false;
    QString configValue = getString( doc, key );
    if ( configValue.isEmpty() )
    {
        // Complain with the original values
        cWarning() << "Branding setting for" << key << "is missing, using" << sidebarFlavorNames.find( flavor, ok )
                   << panelSideNames.find( side, ok );
        return;
    }

    QStringList parts = configValue.split( ',' );
    if ( parts.length() == 1 )
    {
        PanelFlavor f = sidebarFlavorNames.find( configValue, ok );
        if ( ok )
        {
            flavor = f;
        }
        else
        {
            // Complain with the original value
            cWarning() << "Branding setting for" << key << "interpreted as" << sidebarFlavorNames.find( flavor, ok )
                       << panelSideNames.find( side, ok );
        }
        return;
    }

    for ( const QString& spart : parts )
    {
        bool isFlavor = false;
        bool isSide = false;
        PanelFlavor f = sidebarFlavorNames.find( spart, isFlavor );
        PanelSide s = panelSideNames.find( spart, isSide );
        if ( isFlavor )
        {
            flavor = f;
        }
        else if ( isSide )
        {
            side = s;
        }
        else
        {
            cWarning() << "Branding setting for" << key << "contains unknown" << spart << "interpreted as"
                       << sidebarFlavorNames.find( flavor, ok ) << panelSideNames.find( side, ok );
            return;
        }
    }
}

void
Branding::initSimpleSettings( const YAML::Node& doc )
{
    // *INDENT-OFF*
    // clang-format off
    static const NamedEnumTable< WindowExpansion > expansionNames {
        { QStringLiteral( "normal" ), WindowExpansion::Normal },
        { QStringLiteral( "fullscreen" ), WindowExpansion::Fullscreen },
        { QStringLiteral( "noexpand" ), WindowExpansion::Fixed }
    };
    static const NamedEnumTable< WindowPlacement > placementNames {
        { QStringLiteral( "free" ), WindowPlacement::Free },
        { QStringLiteral( "center" ), WindowPlacement::Center }
    };
    // clang-format on
    // *INDENT-ON*
    bool ok = false;

    m_welcomeStyleCalamares = doc[ "welcomeStyleCalamares" ].as< bool >( false );
    m_welcomeExpandingLogo = doc[ "welcomeExpandingLogo" ].as< bool >( true );
    m_windowExpansion = expansionNames.find( getString( doc, "windowExpanding" ), ok );
    if ( !ok )
    {
        cWarning() << "Branding module-setting *windowExpanding* interpreted as"
                   << expansionNames.find( m_windowExpansion, ok );
    }
    m_windowPlacement = placementNames.find( getString( doc, "windowPlacement" ), ok );
    if ( !ok )
    {
        cWarning() << "Branding module-setting *windowPlacement* interpreted as"
                   << placementNames.find( m_windowPlacement, ok );
    }
    flavorAndSide( doc, "sidebar", m_sidebarFlavor, m_sidebarSide );
    flavorAndSide( doc, "navigation", m_navigationFlavor, m_navigationSide );

    QString windowSize = getString( doc, "windowSize" );
    if ( !windowSize.isEmpty() )
    {
        auto l = windowSize.split( ',' );
        if ( l.count() == 2 )
        {
            m_windowWidth = WindowDimension( l[ 0 ] );
            m_windowHeight = WindowDimension( l[ 1 ] );
        }
    }
    if ( !m_windowWidth.isValid() )
    {
        m_windowWidth = WindowDimension( CalamaresUtils::windowPreferredWidth, WindowDimensionUnit::Pixies );
    }
    if ( !m_windowHeight.isValid() )
    {
        m_windowHeight = WindowDimension( CalamaresUtils::windowPreferredHeight, WindowDimensionUnit::Pixies );
    }
}

void
Branding::initSlideshowSettings( const YAML::Node& doc )
{
    QDir componentDir( componentDirectory() );

    auto slideshow = get( doc, "slideshow" );
    if ( slideshow.IsSequence() )
    {
        QStringList slideShowPictures;
        slideshow >> slideShowPictures;
        for ( int i = 0; i < slideShowPictures.count(); ++i )
        {
            QString pathString = slideShowPictures[ i ];
            QFileInfo imageFi( componentDir.absoluteFilePath( pathString ) );
            if ( !imageFi.exists() )
            {
                bail( m_descriptorPath,
                      QString( "Slideshow file %1 does not exist." ).arg( imageFi.absoluteFilePath() ) );
            }

            slideShowPictures[ i ] = imageFi.absoluteFilePath();
        }

        m_slideshowFilenames = slideShowPictures;
        m_slideshowAPI = -1;
    }
#ifdef WITH_QML
    else if ( slideshow.IsScalar() )
    {
        QString slideshowPath = QString::fromStdString( slideshow.as< std::string >() );
        QFileInfo slideshowFi( componentDir.absoluteFilePath( slideshowPath ) );
        if ( !slideshowFi.exists() || !slideshowFi.fileName().toLower().endsWith( ".qml" ) )
            bail( m_descriptorPath,
                  QString( "Slideshow file %1 does not exist or is not a valid QML file." )
                      .arg( slideshowFi.absoluteFilePath() ) );
        m_slideshowPath = slideshowFi.absoluteFilePath();

        // API choice is relevant for QML slideshow
        // TODO:3.3: use get(), make slideshowAPI required
        int api
            = ( doc[ "slideshowAPI" ] && doc[ "slideshowAPI" ].IsScalar() ) ? doc[ "slideshowAPI" ].as< int >() : -1;
        if ( ( api < 1 ) || ( api > 2 ) )
        {
            cWarning() << "Invalid or missing *slideshowAPI* in branding file.";
            api = 1;
        }
        m_slideshowAPI = api;
    }
#else
    else if ( slideshow.IsScalar() )
    {
        cWarning() << "Invalid *slideshow* setting, must be list of images.";
    }
#endif
    else
    {
        bail( m_descriptorPath, "Syntax error in slideshow sequence." );
    }
}


}  // namespace Calamares
