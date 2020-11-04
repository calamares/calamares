/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

/**
 * This is a test-application that does one GeoIP parse.
 */


#include "GeoIPFixed.h"
#include "GeoIPJSON.h"
#ifdef QT_XML_LIB
#include "GeoIPXML.h"
#endif

#include "utils/Logger.h"

#include <iostream>

using std::cerr;
using namespace CalamaresUtils::GeoIP;

int
main( int argc, char** argv )
{
    if ( ( argc != 2 ) && ( argc != 3 ) )
    {
        cerr << "Usage: curl url | test_geoip <format> [selector]\n";
        return 1;
    }

    QString format( argv[ 1 ] );
    QString selector = argc == 3 ? QString( argv[ 2 ] ) : QString();

    Logger::setupLogLevel( Logger::LOGVERBOSE );
    cDebug() << "Doing GeoIP interpretation with format=" << format << "selector=" << selector;

    Interface* handler = nullptr;
    if ( QStringLiteral( "json" ) == format )
    {
        handler = new GeoIPJSON( selector );
    }
#ifdef QT_XML_LIB
    else if ( QStringLiteral( "xml" ) == format )
    {
        handler = new GeoIPXML( selector );
    }
#endif
    else if ( QStringLiteral( "fixed" ) == format )
    {
        handler = new GeoIPFixed( selector );
    }

    if ( !handler )
    {
        cerr << "Unknown format '" << format.toLatin1().constData() << "'\n";
        return 1;
    }

    QByteArray ba;
    while ( !std::cin.eof() )
    {
        char arr[ 1024 ];
        std::cin.read( arr, sizeof( arr ) );
        int s = static_cast< int >( std::cin.gcount() );
        ba.append( arr, s );
    }

    auto tz = handler->processReply( ba );
    if ( tz.first.isEmpty() )
    {
        std::cout << "No TimeZone determined from input.\n";
    }
    else
    {
        std::cout << "TimeZone Region=" << tz.first.toLatin1().constData()
                  << "\nTimeZone Zone=" << tz.second.toLatin1().constData() << '\n';
    }

    return 0;
}
