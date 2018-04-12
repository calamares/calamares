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

/**
 * This is a test-application that does one GeoIP parse.
 */

#include <iostream>

#include "GeoIPFreeGeoIP.h"
#ifdef HAVE_XML
#include "GeoIPXML.h"
#endif

using std::cerr;

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        cerr << "Usage: curl url | test_geoip <format>\n";
        return 1;
    }

    GeoIP* handler = nullptr;
    if ( QLatin1String( "json" ) == argv[1] )
        handler = new FreeGeoIP;
#ifdef HAVE_XML
    else if ( QLatin1String( "xml" ) == argv[1] )
        handler = new XMLGeoIP;
#endif

    if ( !handler )
    {
        cerr << "Unknown format '" << argv[1] << "'\n";
        return 1;
    }

    QByteArray ba;
    while( !std::cin.eof() ) {
        char arr[1024];
        std::cin.read(arr,sizeof(arr));
        int s = std::cin.gcount();
        ba.append(arr, s);
    }

    auto tz = handler->processReply( ba );
    if ( tz.first.isEmpty() )
    {
        std::cout << "No TimeZone determined from input.\n";
    }
    else
    {
        std::cout << "TimeZone Region=" << tz.first.toLatin1().constData() << "\nTimeZone Zone=" << tz.second.toLatin1().constData() << '\n';
    }

    return 0;
}
