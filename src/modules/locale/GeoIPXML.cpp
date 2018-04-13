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

#include <QNetworkReply>
#include <QtXml/QDomDocument>

GeoIP::RegionZonePair
XMLGeoIP::processReply( const QByteArray& data )
{
    QString domError;
    int errorLine, errorColumn;

    QDomDocument doc;
    if ( doc.setContent( data, false, &domError, &errorLine, &errorColumn ) )
    {
        const auto tzElements = doc.elementsByTagName( "TimeZone" );
        cDebug() << "GeoIP found" << tzElements.length() << "elements";
        for ( int it = 0; it < tzElements.length(); ++it )
        {
            auto e = tzElements.at(it).toElement();
            return splitTZString( e.text() );
        }
    }
    else
    {
        cDebug() << "GeoIP XML data error:" << domError << "(line" << errorLine << errorColumn << ')';
    }

    return qMakePair( QString(), QString() );

}
