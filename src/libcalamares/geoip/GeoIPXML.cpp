/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2018, Adriaan de Groot <groot@kde.org>
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
