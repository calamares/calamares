/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019, Adriaan de Groot <groot@kde.org>
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

#include "PackageModel.h"

#include "utils/Logger.h"
#include "utils/Variant.h"

#ifdef HAVE_XML
#include <QDomDocument>
#include <QDomNodeList>
#include <QFile>
#endif

const NamedEnumTable< PackageChooserMode >&
roleNames()
{
    static const NamedEnumTable< PackageChooserMode > names {
        { "optional", PackageChooserMode::Optional },
        { "required", PackageChooserMode::Required },
        { "optionalmultiple", PackageChooserMode::OptionalMultiple },
        { "requiredmultiple", PackageChooserMode::RequiredMultiple },
        // and a bunch of aliases
        { "zero-or-one", PackageChooserMode::Optional },
        { "radio", PackageChooserMode::Required },
        { "one", PackageChooserMode::Required },
        { "set", PackageChooserMode::OptionalMultiple },
        { "zero-or-more", PackageChooserMode::OptionalMultiple },
        { "multiple", PackageChooserMode::RequiredMultiple },
        { "one-or-more", PackageChooserMode::RequiredMultiple }
    };
    return names;
}

PackageItem::PackageItem() {}

PackageItem::PackageItem( const QString& a_id,
                          const QString& a_package,
                          const QString& a_name,
                          const QString& a_description )
    : id( a_id )
    , package( a_package )
    , name( a_name )
    , description( a_description )
{
}

PackageItem::PackageItem( const QString& a_id,
                          const QString& a_package,
                          const QString& a_name,
                          const QString& a_description,
                          const QString& screenshotPath )
    : id( a_id )
    , package( a_package )
    , name( a_name )
    , description( a_description )
    , screenshot( screenshotPath )
{
}

PackageItem::PackageItem::PackageItem( const QVariantMap& item_map )
    : id( CalamaresUtils::getString( item_map, "id" ) )
    , package( CalamaresUtils::getString( item_map, "package" ) )
    , name( CalamaresUtils::Locale::TranslatedString( item_map, "name" ) )
    , description( CalamaresUtils::Locale::TranslatedString( item_map, "description" ) )
    , screenshot( CalamaresUtils::getString( item_map, "screenshot" ) )
{
    if ( name.isEmpty() && id.isEmpty() )
    {
        name = QObject::tr( "No product" );
    }
    else if ( name.isEmpty() )
    {
        cWarning() << "PackageChooser item" << id << "has an empty name.";
    }
    if ( description.isEmpty() )
    {
        description = QObject::tr( "No description provided." );
    }
}

#ifdef HAVE_XML
/** @brief try to load the given @p fileName XML document
 *
 * Returns a QDomDocument, which will be valid iff the file can
 * be read and contains valid XML data.
 */
static inline QDomDocument
loadAppData( const QString& fileName )
{
    QFile file( fileName );
    if ( !file.open( QIODevice::ReadOnly ) )
    {
        return QDomDocument();
    }
    QDomDocument doc( "AppData" );
    if ( !doc.setContent( &file ) )
    {
        file.close();
        return QDomDocument();
    }
    file.close();
    return doc;
}

/** @brief gets the text of child element @p tagName
 */
static inline QString
getChildText( const QDomNode& n, const QString& tagName )
{
    QDomElement e = n.firstChildElement( tagName );
    return e.isNull() ? QString() : e.text();
}

/** @brief Gets a suitable screenshot path
 *
 * The <screenshots> element contains zero or more <screenshot>
 * elements, which can have a *type* associated with them.
 * Scan the screenshot elements, return the <image> path
 * for the one labeled with type=default or, if there is no
 * default, the first element.
 */
static inline QString
getScreenshotPath( const QDomNode& n )
{
    QDomElement shotsNode = n.firstChildElement( "screenshots" );
    if ( shotsNode.isNull() )
    {
        return QString();
    }

    const QDomNodeList shotList = shotsNode.childNodes();
    int firstScreenshot = -1;  // Use which screenshot node?
    for ( int i = 0; i < shotList.count(); ++i )
    {
        if ( !shotList.at( i ).isElement() )
        {
            continue;
        }
        QDomElement e = shotList.at( i ).toElement();
        if ( e.tagName() != "screenshot" )
        {
            continue;
        }
        // If none has the "type=default" attribute, use the first one
        if ( firstScreenshot < 0 )
        {
            firstScreenshot = i;
        }
        // But type=default takes precedence.
        if ( e.hasAttribute( "type" ) && e.attribute( "type" ) == "default" )
        {
            firstScreenshot = i;
            break;
        }
    }

    if ( firstScreenshot >= 0 )
    {
        return shotList.at( firstScreenshot ).firstChildElement( "image" ).text();
    }

    return QString();
}

/** @brief Returns language of the given element @p e
 *
 * Transforms the attribute value for xml:lang to something
 * suitable for TranslatedString (e.g. [lang]).
 */
static inline QString
getLanguage( const QDomElement& e )
{
    QString language = e.attribute( "xml:lang" );
    if ( !language.isEmpty() )
    {
        language.replace( '-', '_' );
        language.prepend( '[' );
        language.append( ']' );
    }
    return language;
}

/** @brief Scan the list of @p children for @p tagname elements and add them to the map
 *
 * Uses @p mapname instead of @p tagname for the entries in map @p m
 * to allow renaming from XML to map keys (in particular for
 * TranslatedString). Also transforms xml:lang attributes to suitable
 * key-decorations on @p mapname.
 */
static inline void
fillMap( QVariantMap& m, const QDomNodeList& children, const QString& tagname, const QString& mapname )
{
    for ( int i = 0; i < children.count(); ++i )
    {
        if ( !children.at( i ).isElement() )
        {
            continue;
        }

        QDomElement e = children.at( i ).toElement();
        if ( e.tagName() != tagname )
        {
            continue;
        }

        m[ mapname + getLanguage( e ) ] = e.text();
    }
}

/** @brief gets the <name> and <description> elements
*
* Builds up a map of the <name> elements (which may have a *lang*
* attribute to indicate translations and paragraphs of the
* <description> element (also with lang). Uses the <summary>
* elements to supplement the description if no description
* is available for a given language.
*
* Returns a map with keys suitable for use by TranslatedString.
*/
static inline QVariantMap
getNameAndSummary( const QDomNode& n )
{
    QVariantMap m;

    const QDomNodeList children = n.childNodes();
    fillMap( m, children, "name", "name" );
    fillMap( m, children, "summary", "description" );

    const QDomElement description = n.firstChildElement( "description" );
    if ( !description.isNull() )
    {
        fillMap( m, description.childNodes(), "p", "description" );
    }

    return m;
}
#endif

PackageItem
PackageItem::fromAppData( const QVariantMap& item_map )
{
#ifdef HAVE_XML
    QString fileName = CalamaresUtils::getString( item_map, "appdata" );
    if ( fileName.isEmpty() )
    {
        cWarning() << "Can't load AppData without a suitable key.";
        return PackageItem();
    }
    cDebug() << "Loading AppData XML from" << fileName;

    QDomDocument doc = loadAppData( fileName );
    if ( doc.isNull() )
    {
        return PackageItem();
    }

    QDomElement componentNode = doc.documentElement();
    if ( !componentNode.isNull() && componentNode.tagName() == "component" )
    {
        // An "id" entry in the Calamares config overrides ID in the AppData
        QString id = CalamaresUtils::getString( item_map, "id" );
        if ( id.isEmpty() )
        {
            id = getChildText( componentNode, "id" );
        }
        if ( id.isEmpty() )
        {
            return PackageItem();
        }

        // A "screenshot" entry in the Calamares config overrides AppData
        QString screenshotPath = CalamaresUtils::getString( item_map, "screenshot" );
        if ( screenshotPath.isEmpty() )
        {
            screenshotPath = getScreenshotPath( componentNode );
        }

        QVariantMap map = getNameAndSummary( componentNode );
        map.insert( "id", id );
        map.insert( "screenshot", screenshotPath );

        return PackageItem( map );
    }

    return PackageItem();
#else
    cWarning() << "Loading AppData XML is not supported.";

    return PackageItem();
#endif
}


PackageListModel::PackageListModel( QObject* parent )
    : QAbstractListModel( parent )
{
}

PackageListModel::PackageListModel( PackageList&& items, QObject* parent )
    : QAbstractListModel( parent )
    , m_packages( std::move( items ) )
{
}

PackageListModel::~PackageListModel() {}

void
PackageListModel::addPackage( PackageItem&& p )
{
    // Only add valid packages
    if ( p.isValid() )
    {
        int c = m_packages.count();
        beginInsertRows( QModelIndex(), c, c );
        m_packages.append( p );
        endInsertRows();
    }
}

int
PackageListModel::rowCount( const QModelIndex& index ) const
{
    // For lists, valid indexes have zero children; only the root index has them
    return index.isValid() ? 0 : m_packages.count();
}

QVariant
PackageListModel::data( const QModelIndex& index, int role ) const
{
    if ( !index.isValid() )
    {
        return QVariant();
    }
    int row = index.row();
    if ( row >= m_packages.count() || row < 0 )
    {
        return QVariant();
    }

    if ( role == Qt::DisplayRole /* Also PackageNameRole */ )
    {
        return m_packages[ row ].name.get();
    }
    else if ( role == DescriptionRole )
    {
        return m_packages[ row ].description.get();
    }
    else if ( role == ScreenshotRole )
    {
        return m_packages[ row ].screenshot;
    }
    else if ( role == IdRole )
    {
        return m_packages[ row ].id;
    }

    return QVariant();
}
