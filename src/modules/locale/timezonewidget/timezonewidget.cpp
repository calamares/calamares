/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017-2019, Adriaan de Groot <groot@kde.org>
 *
 *   Originally from the Manjaro Installation Framework
 *   by Roland Singer <roland@manjaro.org>
 *   Copyright (C) 2007 Free Software Foundation, Inc.
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

#include <cmath>

#include "locale/TimeZone.h"
#include "utils/Logger.h"

#include "timezonewidget.h"

// Pixel value indicating that a spot is outside of a zone
#define RGB_TRANSPARENT 0

static constexpr double MAP_Y_OFFSET = 0.125;
static constexpr double MAP_X_OFFSET = -0.0370;
constexpr static double MATH_PI = 3.14159265;

#ifdef DEBUG_TIMEZONES
// Adds a label to the timezone with this name
constexpr static QLatin1String ZONE_NAME( "zone" );
#endif

TimeZoneWidget::TimeZoneWidget( QWidget* parent )
    : QWidget( parent )
{
    setMouseTracking( false );
    setCursor( Qt::PointingHandCursor );

    // Font
    font.setPointSize( 12 );
    font.setBold( false );

    // Images
    background = QImage( ":/images/bg.png" );
    pin = QImage( ":/images/pin.png" );

#ifdef DEBUG_TIMEZONES
    if ( background.size() != QSize( 780, 340 ) )
    {
        cWarning() << "Timezone background size mitsmatch" << background.size();
    }
#endif

    // Set size
    setMinimumSize( background.size() );
    setMaximumSize( background.size() );

    // Zone images
    for ( const auto* zoneName :
          { "0.0",  "1.0",  "2.0",  "3.0",  "3.5",  "4.0",  "4.5",  "5.0",  "5.5",   "5.75", "6.0",   "6.5",  "7.0",
            "8.0",  "9.0",  "9.5",  "10.0", "10.5", "11.0", "11.5", "12.0", "12.75", "13.0", "-1.0",  "-2.0", "-3.0",
            "-3.5", "-4.0", "-4.5", "-5.0", "-5.5", "-6.0", "-7.0", "-8.0", "-9.0",  "-9.5", "-10.0", "-11.0" } )
    {
        timeZoneImages.append( QImage( QStringLiteral( ":/images/timezone_" ) + zoneName + ".png" ) );
#ifdef DEBUG_TIMEZONES
        if ( timeZoneImages.last().size() != background.size() )
        {
            cWarning() << "Timezone image size mismatch" << zoneName << timeZoneImages.last().size();
        }
        timeZoneImages.last().setText( ZONE_NAME, zoneName );
#endif
    }
}


void
TimeZoneWidget::setCurrentLocation( QString regionName, QString zoneName )
{
    using namespace CalamaresUtils::Locale;
    const auto& regions = TZRegion::fromZoneTab();
    auto* region = regions.find< TZRegion >( regionName );
    if ( !region )
    {
        return;
    }

    auto* zone = region->zones().find< TZZone >( zoneName );
    if ( zone )
    {
        setCurrentLocation( zone );
    }
}


void
TimeZoneWidget::setCurrentLocation( const CalamaresUtils::Locale::TZZone* location )
{
    m_currentLocation = location;

    // Set zone
    QPoint pos = getLocationPosition( location );

#ifdef DEBUG_TIMEZONES
    cDebug() << "Setting location" << location->region() << location->zone() << '(' << location->country() << '@' << location->latitude() << 'N' << location->longitude() << 'E' << ')';
    cDebug() << Logger::SubEntry << "pixel x" << pos.x() << "pixel y" << pos.y();

    bool found = false;
#endif


    for ( int i = 0; i < timeZoneImages.size(); ++i )
    {
        QImage zone = timeZoneImages[ i ];

        // If not transparent set as current
        if ( zone.pixel( pos ) != RGB_TRANSPARENT )
        {
#ifdef DEBUG_TIMEZONES
            // Log *all* the zones that contain this point,
            // but only pick the first.
            if ( !found )
            {
                currentZoneImage = zone;
                found = true;
                cDebug() << Logger::SubEntry << "First zone found" << i << zone.text( ZONE_NAME );
            }
            else
            {
                cDebug() << Logger::SubEntry << "Also in zone" << i << zone.text( ZONE_NAME );
            }
#else
            currentZoneImage = zone;
            break;
#endif
        }
    }

    // Repaint widget
    repaint();
    emit locationChanged( m_currentLocation );
}


//###
//### Private
//###


QPoint
TimeZoneWidget::getLocationPosition( double longitude, double latitude )
{
    const int width = this->width();
    const int height = this->height();

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


void
TimeZoneWidget::paintEvent( QPaintEvent* )
{
    const int width = this->width();
    const int height = this->height();
    QFontMetrics fontMetrics( font );
    QPainter painter( this );

    painter.setRenderHint( QPainter::Antialiasing );
    painter.setFont( font );

    // Draw background
    painter.drawImage( 0, 0, background );

    // Draw zone image
    painter.drawImage( 0, 0, currentZoneImage );

#ifdef DEBUG_TIMEZONES
    QPoint point = getLocationPosition( m_currentLocation );
    // Draw latitude lines
    for ( int y_lat = -50; y_lat < 80; y_lat += 5 )
    {
        QPen p( y_lat ? Qt::black : Qt::red );
        p.setWidth( 0 );
        painter.setPen( p );
        QPoint latLine0( getLocationPosition( 0, y_lat ) );
        int llx = latLine0.x() + ( ( y_lat & 1 ) ? -10 : 0 );
        int lly = latLine0.y();

        for ( int c = 0; c < width; ++c )
        {
            painter.drawPoint( c, lly );
        }
    }
    // Just a dot in the selected location, no label
    painter.setPen( Qt::red );
    painter.drawPoint( point );
#else
    // Draw pin at current location
    QPoint point = getLocationPosition( m_currentLocation );

    painter.drawImage( point.x() - pin.width() / 2, point.y() - pin.height() / 2, pin );

    // Draw text and box
    // .. the lambda manages deprecations: the old one works in Qt 5.9 and Qt 5.10,
    //    while the new one avoids deprecation messages in Qt 5.13 and later.
#if QT_VERSION >= QT_VERSION_CHECK( 5, 11, 0 )
    auto textwidth = [&]( const QString& s ) { return fontMetrics.horizontalAdvance( s ); };
#else
    auto textwidth = [&]( const QString& s ) { return fontMetrics.width( s ); };
#endif
    const int textWidth = textwidth( m_currentLocation ? m_currentLocation->tr() : QString() );
    const int textHeight = fontMetrics.height();

    QRect rect = QRect( point.x() - textWidth / 2 - 5, point.y() - textHeight - 8, textWidth + 10, textHeight - 2 );

    if ( rect.x() <= 5 )
    {
        rect.moveLeft( 5 );
    }
    if ( rect.right() >= width - 5 )
    {
        rect.moveRight( width - 5 );
    }
    if ( rect.y() <= 5 )
    {
        rect.moveTop( 5 );
    }
    if ( rect.y() >= height - 5 )
    {
        rect.moveBottom( height - 5 );
    }

    painter.setPen( QPen() );  // no pen
    painter.setBrush( QColor( 40, 40, 40 ) );
    painter.drawRoundedRect( rect, 3, 3 );
    painter.setPen( Qt::white );
    painter.drawText( rect.x() + 5, rect.bottom() - 4, m_currentLocation ? m_currentLocation->tr() : QString() );
#endif

    painter.end();
}


void
TimeZoneWidget::mousePressEvent( QMouseEvent* event )
{
    if ( event->button() != Qt::LeftButton )
    {
        return;
    }

    // Set nearest location
    int nX = 999999, mX = event->pos().x();
    int nY = 999999, mY = event->pos().y();

    using namespace CalamaresUtils::Locale;
    const TZZone* closest = nullptr;
    for ( const auto* region_p : TZRegion::fromZoneTab() )
    {
        const auto* region = dynamic_cast< const TZRegion* >( region_p );
        if ( region )
        {
            for ( const auto* zone_p : region->zones() )
            {
                const auto* zone = dynamic_cast< const TZZone* >( zone_p );
                if ( zone )
                {
                    QPoint locPos = getLocationPosition( zone->longitude(), zone->latitude() );

                    if ( ( abs( mX - locPos.x() ) + abs( mY - locPos.y() ) < abs( mX - nX ) + abs( mY - nY ) ) )
                    {
                        closest = zone;
                        nX = locPos.x();
                        nY = locPos.y();
                    }
                }
            }
        }
    }

    if ( closest )
    {
        // Set zone image and repaint widget
        setCurrentLocation( closest );
        // Emit signal
        emit locationChanged( m_currentLocation );
    }
}
