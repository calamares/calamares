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

#include "locale/TimeZone.h"
#include "utils/Logger.h"

#include "timezonewidget.h"

#include <QMouseEvent>
#include <QPainter>

#ifdef DEBUG_TIMEZONES
// Adds a label to the timezone with this name
#define ZONE_NAME QStringLiteral( "zone" )
#endif

TimeZoneWidget::TimeZoneWidget( QWidget* parent )
    : QWidget( parent )
    , timeZoneImages( TimeZoneImageList::fromQRC() )
{
    setMouseTracking( false );
    setCursor( Qt::PointingHandCursor );

    // Font
    font.setPointSize( 12 );
    font.setBold( false );

    // Images
    background = QImage( ":/images/bg.png" );
    pin = QImage( ":/images/pin.png" );

    // Set size
    setMinimumSize( background.size() );
    setMaximumSize( background.size() );
    setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );
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
    cDebug() << "Setting location" << location->region() << location->zone() << '(' << location->country() << '@'
             << location->latitude() << 'N' << location->longitude() << 'E' << ')';
    cDebug() << Logger::SubEntry << "pixel x" << pos.x() << "pixel y" << pos.y();
#endif

    currentZoneImage = timeZoneImages.find( pos );

    // Repaint widget
    repaint();
    emit locationChanged( m_currentLocation );
}


//###
//### Private
//###

void
TimeZoneWidget::paintEvent( QPaintEvent* )
{
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
        QPoint latLine0( TimeZoneImageList::getLocationPosition( 0, y_lat ) );
        painter.drawLine( 0, latLine0.y(), this->width() - 1, latLine0.y() );
    }
    // Just a dot in the selected location, no label
    painter.setPen( Qt::red );
    painter.drawPoint( point );
#else
    const int width = this->width();
    const int height = this->height();

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
                    QPoint locPos = TimeZoneImageList::getLocationPosition( zone->longitude(), zone->latitude() );

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
