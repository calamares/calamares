/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017-2018, Adriaan de Groot <groot@kde.org>
 *   Copyright 2018, Raul Rodrigo Segura (raurodse)
 *
 *   Calamares is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Calamares is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Calamares. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Branding.h"

#include "GlobalStorage.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/ImageRegistry.h"
#include "utils/Logger.h"
#include "utils/NamedEnum.h"
#include "utils/Yaml.h"

#include <QDir>
#include <QFile>
#include <QPixmap>
#include <QVariantMap>

namespace Calamares
{

Branding* Branding::s_instance = nullptr;

Branding*
Branding::instance()
{
    return s_instance;
}


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
    "releaseNotesUrl"
};


const QStringList Branding::s_imageEntryStrings =
{
    "productLogo",
    "productIcon",
    "productWelcome"
};

const QStringList Branding::s_styleEntryStrings =
{
    "sidebarBackground",
    "sidebarText",
    "sidebarTextSelect",
    "sidebarTextHighlight"
};

const NamedEnumTable<Branding::WindowDimensionUnit>&
Branding::WindowDimension::suffixes()
{
    using Unit = Branding::WindowDimensionUnit;
    static const NamedEnumTable<Unit> names{
        {"px", Unit::Pixies},
        {"em", Unit::Fonties}
    };

    return names;
}

Branding::Branding( const QString& brandingFilePath,
                    QObject* parent )
    : QObject( parent )
    , m_descriptorPath( brandingFilePath )
    , m_welcomeStyleCalamares( false )
    , m_welcomeExpandingLogo( true )
{
    cDebug() << "Using Calamares branding file at" << brandingFilePath;
    QFile file( brandingFilePath );
    if ( file.exists() && file.open( QFile::ReadOnly | QFile::Text ) )
    {
        QByteArray ba = file.readAll();

        QFileInfo fi ( m_descriptorPath );
        QDir componentDir = fi.absoluteDir();
        if ( !componentDir.exists() )
            bail( "Bad component directory path." );

        try
        {
            YAML::Node doc = YAML::Load( ba.constData() );
            Q_ASSERT( doc.IsMap() );

            m_componentName = QString::fromStdString( doc[ "componentName" ]
                                                      .as< std::string >() );
            if ( m_componentName != QFileInfo( m_descriptorPath ).absoluteDir().dirName() )
                bail( "The branding component name should match the name of the "
                      "component directory." );

            initSimpleSettings( doc );

            if ( !doc[ "strings" ].IsMap() )
                bail( "Syntax error in strings map." );

            QVariantMap strings =
                CalamaresUtils::yamlMapToVariant( doc[ "strings" ] ).toMap();
            m_strings.clear();
            for ( auto it = strings.constBegin(); it != strings.constEnd(); ++it )
                m_strings.insert( it.key(), it.value().toString() );

            if ( !doc[ "images" ].IsMap() )
                bail( "Syntax error in images map." );

            QVariantMap images =
                CalamaresUtils::yamlMapToVariant( doc[ "images" ] ).toMap();
            m_images.clear();
            for ( auto it = images.constBegin(); it != images.constEnd(); ++it )
            {
                QString pathString = it.value().toString();
                QFileInfo imageFi( componentDir.absoluteFilePath( pathString ) );
                if ( !imageFi.exists() )
                    bail( QString( "Image file %1 does not exist." )
                            .arg( imageFi.absoluteFilePath() ) );

                m_images.insert( it.key(), imageFi.absoluteFilePath() );
            }

            if ( doc[ "slideshow" ].IsSequence() )
            {
                QStringList slideShowPictures;
                doc[ "slideshow" ] >> slideShowPictures;
                for ( int i = 0; i < slideShowPictures.count(); ++i )
                {
                    QString pathString = slideShowPictures[ i ];
                    QFileInfo imageFi( componentDir.absoluteFilePath( pathString ) );
                    if ( !imageFi.exists() )
                        bail( QString( "Slideshow file %1 does not exist." )
                                .arg( imageFi.absoluteFilePath() ) );

                    slideShowPictures[ i ] = imageFi.absoluteFilePath();
                }

                //FIXME: implement a GenericSlideShow.qml that uses these slideShowPictures
            }
            else if ( doc[ "slideshow" ].IsScalar() )
            {
                QString slideshowPath = QString::fromStdString( doc[ "slideshow" ]
                                                          .as< std::string >() );
                QFileInfo slideshowFi( componentDir.absoluteFilePath( slideshowPath ) );
                if ( !slideshowFi.exists() ||
                     !slideshowFi.fileName().toLower().endsWith( ".qml" ) )
                    bail( QString( "Slideshow file %1 does not exist or is not a valid QML file." )
                            .arg( slideshowFi.absoluteFilePath() ) );
                m_slideshowPath = slideshowFi.absoluteFilePath();
            }
            else
                bail( "Syntax error in slideshow sequence." );

            if ( !doc[ "style" ].IsMap() )
                bail( "Syntax error in style map." );

            QVariantMap style =
                CalamaresUtils::yamlMapToVariant( doc[ "style" ] ).toMap();
            m_style.clear();
            for ( auto it = style.constBegin(); it != style.constEnd(); ++it )
                m_style.insert( it.key(), it.value().toString() );

        }
        catch ( YAML::Exception& e )
        {
            CalamaresUtils::explainYamlException( e, ba, file.fileName() );
        }

        QDir translationsDir( componentDir.filePath( "lang" ) );
        if ( !translationsDir.exists() )
            cWarning() << "the branding component" << componentDir.absolutePath() << "does not ship translations.";
        m_translationsPathPrefix = translationsDir.absolutePath();
        m_translationsPathPrefix.append( QString( "%1calamares-%2" )
                                            .arg( QDir::separator() )
                                            .arg( m_componentName ) );

        QFileInfo importQSSPath( componentDir.filePath( "stylesheet.qss" ) );
        if ( importQSSPath.exists() && importQSSPath.isReadable() )
        {
            QFile stylesheetFile( importQSSPath.filePath() );
            stylesheetFile.open( QFile::ReadOnly );
            m_stylesheet = stylesheetFile.readAll();
        }
        else
            cWarning() << "the branding component" << componentDir.absolutePath() << "does not ship stylesheet.qss.";
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
}


QString
Branding::componentDirectory() const
{
    QFileInfo fi ( m_descriptorPath );
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
    return m_style.value( s_styleEntryStrings.value( styleEntry ) );
}


QString
Branding::imagePath( Branding::ImageEntry imageEntry ) const
{
    return m_images.value( s_imageEntryStrings.value( imageEntry ) );
}


QPixmap
Branding::image( Branding::ImageEntry imageEntry, const QSize& size ) const
{
    QPixmap pixmap =
        ImageRegistry::instance()->pixmap( imagePath( imageEntry ), size );

    if ( pixmap.isNull() )
    {
        Q_ASSERT( false );
        return QPixmap();
    }
    return pixmap;
}


void
Branding::setGlobals( GlobalStorage* globalStorage ) const
{
    QVariantMap brandingMap;
    for ( const QString& key : s_stringEntryStrings )
        brandingMap.insert( key, m_strings.value( key ) );
    globalStorage->insert( "branding", brandingMap );
}

bool
Branding::WindowDimension::isValid() const
{
    return ( unit() != none ) && ( value() > 0 );
}


/// @brief Guard against cases where the @p key doesn't exist in @p doc
static inline QString
getString( const YAML::Node& doc, const char* key )
{
    if ( doc[key] )
        return QString::fromStdString( doc[key].as< std::string >() );
    return QString();
}

void
Branding::initSimpleSettings( const YAML::Node& doc )
{
    static const NamedEnumTable< WindowExpansion > expansionNames{
        { QStringLiteral( "normal" ), WindowExpansion::Normal },
        { QStringLiteral( "fullscreen" ), WindowExpansion::Fullscreen },
        { QStringLiteral( "noexpand" ), WindowExpansion::Fixed }
    };
    bool ok = false;

    m_welcomeStyleCalamares = doc[ "welcomeStyleCalamares" ].as< bool >( false );
    m_welcomeExpandingLogo = doc[ "welcomeExpandingLogo" ].as< bool >( true );
    m_windowExpansion = expansionNames.find( getString( doc, "windowExpanding" ), ok );
    if ( !ok )
        cWarning() << "Branding module-setting *windowExpanding* interpreted as" << expansionNames.find( m_windowExpansion, ok );

    QString windowSize = getString( doc, "windowSize" );
    if ( !windowSize.isEmpty() )
    {
        auto l = windowSize.split( ',' );
        if ( l.count() == 2 )
        {
            m_windowWidth = WindowDimension( l[0] );
            m_windowHeight = WindowDimension( l[1] );
        }
    }
    if ( !m_windowWidth.isValid() )
        m_windowWidth = WindowDimension( CalamaresUtils::windowPreferredWidth, WindowDimensionUnit::Pixies );
    if ( !m_windowHeight.isValid() )
        m_windowHeight = WindowDimension( CalamaresUtils::windowPreferredHeight, WindowDimensionUnit::Pixies );
}


[[noreturn]] void
Branding::bail( const QString& message )
{
    cError() << "FATAL in"
           << m_descriptorPath
           << "\n" + message;
    ::exit( EXIT_FAILURE );
}

}
