/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "GeoIPXML.h"

#include "utils/Logger.h"

#include <QtXml/QDomDocument>

namespace CalamaresUtils
{
namespace GeoIP
{

GeoIPXML::GeoIPXML( const QString& element )
    : Interface( element.isEmpty() ? QStringLiteral( "TimeZone" ) : element )
{
}

static QStringList
getElementTexts( const QByteArray& data, const QString& tag )
{
    QStringList elements;

    QString domError;
    int errorLine, errorColumn;

    QDomDocument doc;
    if ( doc.setContent( data, false, &domError, &errorLine, &errorColumn ) )
    {
        const auto tzElements = doc.elementsByTagName( tag );
        cDebug() << "GeoIP found" << tzElements.length() << "elements";
        for ( int it = 0; it < tzElements.length(); ++it )
        {
            auto e = tzElements.at( it ).toElement();
            auto e_text = e.text();
            if ( !e_text.isEmpty() )
            {
                elements.append( e_text );
            }
        }
    }
    else
    {
        cWarning() << "GeoIP XML data error:" << domError << "(line" << errorLine << errorColumn << ')';
    }

    if ( elements.count() < 1 )
    {
        cWarning() << "GeopIP XML had no non-empty elements" << tag;
    }

    return elements;
}


QString
GeoIPXML::rawReply( const QByteArray& data )
{
    for ( const auto& e : getElementTexts( data, m_element ) )
    {
        if ( !e.isEmpty() )
        {
            return e;
        }
    }

    return QString();
}

GeoIP::RegionZonePair
GeoIPXML::processReply( const QByteArray& data )
{
    for ( const auto& e : getElementTexts( data, m_element ) )
    {
        auto tz = splitTZString( e );
        if ( !tz.first.isEmpty() )
        {
            return tz;
        }
    }

    return RegionZonePair();
}

}  // namespace GeoIP
}  // namespace CalamaresUtils
