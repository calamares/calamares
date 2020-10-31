/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "TimeZoneImage.h"

#include "utils/Logger.h"

#include <QDir>

#include <cmath>

static const char* zoneNames[]
    = { "0.0",  "1.0",  "2.0",  "3.0",  "3.5",  "4.0",  "4.5",  "5.0",   "5.5",  "5.75",  "6.0",  "6.5",  "7.0",
        "8.0",  "9.0",  "9.5",  "10.0", "10.5", "11.0", "12.0", "12.75", "13.0", "-1.0",  "-2.0", "-3.0", "-3.5",
        "-4.0", "-4.5", "-5.0", "-5.5", "-6.0", "-7.0", "-8.0", "-9.0",  "-9.5", "-10.0", "-11.0" };
static_assert( TimeZoneImageList::zoneCount == ( sizeof( zoneNames ) / sizeof( zoneNames[ 0 ] ) ),
               "Incorrect number of zones" );

#define ZONE_NAME QStringLiteral( "zone" )

static_assert( TimeZoneImageList::zoneCount == 37, "Incorrect number of zones" );

TimeZoneImageList::TimeZoneImageList() {}

TimeZoneImageList
TimeZoneImageList::fromQRC()
{
    TimeZoneImageList l;
    for ( const auto* zoneName : zoneNames )
    {
        l.append( QImage( QStringLiteral( ":/images/timezone_" ) + zoneName + ".png" ) );
        l.last().setText( ZONE_NAME, zoneName );
    }

    return l;
}

TimeZoneImageList
TimeZoneImageList::fromDirectory( const QString& dirName )
{
    TimeZoneImageList l;
    QDir dir( dirName );
    if ( !dir.exists() )
    {
        cWarning() << "TimeZone images directory" << dirName << "does not exist.";
        return l;
    }

    for ( const auto* zoneName : zoneNames )
    {
        l.append( QImage( dir.filePath( QStringLiteral( "timezone_" ) + zoneName + ".png" ) ) );
        l.last().setText( ZONE_NAME, zoneName );
    }

    return l;
}

QPoint
TimeZoneImageList::getLocationPosition( double longitude, double latitude )
{
    constexpr double MAP_Y_OFFSET = 0.125;
    constexpr double MAP_X_OFFSET = -0.0370;
    constexpr double MATH_PI = 3.14159265;

    const int width = imageSize.width();
    const int height = imageSize.height();

    double x = ( width / 2.0 + ( width / 2.0 ) * longitude / 180.0 ) + MAP_X_OFFSET * width;
    double y = ( height / 2.0 - ( height / 2.0 ) * latitude / 90.0 ) + MAP_Y_OFFSET * height;

    // Far north, the MAP_Y_OFFSET no longer holds, cancel the Y offset; it's noticeable
    // from 62 degrees north, so scale those 28 degrees as if the world is flat south
    // of there, and we have a funny "rounded" top of the world. In practice the locations
    // of the different cities / regions looks ok -- at least Thule ends up in the right
    // country, and Inuvik isn't in the ocean.
    if ( latitude > 70.0 )
    {
        y -= sin( MATH_PI * ( latitude - 70.0 ) / 56.0 ) * MAP_Y_OFFSET * height * 0.8;
    }
    if ( latitude > 74.0 )
    {
        y += 4;
    }
    if ( latitude > 69.0 )
    {
        y -= 2;
    }
    if ( latitude > 59.0 )
    {
        y -= 4 * int( ( latitude - 54.0 ) / 5.0 );
    }
    if ( latitude > 54.0 )
    {
        y -= 2;
    }
    if ( latitude > 49.0 )
    {
        y -= int( ( latitude - 44.0 ) / 5.0 );
    }
    // Far south, some stretching occurs as well, but it is less pronounced.
    // Move down by 1 pixel per 5 degrees past 10 south
    if ( latitude < 0 )
    {
        y += int( ( -latitude ) / 5.0 );
    }
    // Antarctica isn't shown on the map, but you could try clicking there
    if ( latitude < -60 )
    {
        y = height - 1;
    }

    if ( x < 0 )
    {
        x = width + x;
    }
    if ( x >= width )
    {
        x -= width;
    }
    if ( y < 0 )
    {
        y = height + y;
    }
    if ( y >= height )
    {
        y -= height;
    }

    return QPoint( int( x ), int( y ) );
}

// Pixel value indicating that a spot is outside of a zone
static constexpr const int RGB_TRANSPARENT = 0;

int
TimeZoneImageList::index( QPoint pos, int& count ) const
{
    count = 0;

#ifdef DEBUG_TIMEZONES
    for ( int i = 0; i < size(); ++i )
    {
        const QImage& zone = at( i );

        // If not transparent set as current
        if ( zone.pixel( pos ) != RGB_TRANSPARENT )
        {
            // Log *all* the zones that contain this point,
            // but only pick the first.
            if ( !count )
            {
                cDebug() << Logger::SubEntry << "First zone found" << i << zone.text( ZONE_NAME );
            }
            else
            {
                cDebug() << Logger::SubEntry << "Also in zone" << i << zone.text( ZONE_NAME );
            }
            count++;
        }
    }
    if ( !count )
    {
        return -1;
    }
#endif
    return index( pos );
}

int
TimeZoneImageList::index( QPoint pos ) const
{
    for ( int i = 0; i < size(); ++i )
    {
        const QImage& zone = at( i );

        // If not transparent set as current
        if ( zone.pixel( pos ) != RGB_TRANSPARENT )
        {
            return i;
        }
    }
    return -1;
}

QImage
TimeZoneImageList::find( QPoint p ) const
{
    int i = index( p );
    if ( i < 0 || size() <= i )
    {
        return QImage();
    }
    return at( i );
}
