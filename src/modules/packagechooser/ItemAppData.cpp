/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

/** @brief Loading items from AppData XML files.
 *
 * Only used if QtXML is found, implements PackageItem::fromAppData().
 */
#include "PackageModel.h"

#include "utils/Logger.h"
#include "utils/Variant.h"

#include <QDomDocument>
#include <QDomNodeList>
#include <QFile>

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

PackageItem
fromAppData( const QVariantMap& item_map )
{
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
}
