/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2007 Free Software Foundation, Inc.
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017-2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Originally from the Manjaro Installation Framework
 *   by Roland Singer <roland@manjaro.org>
 *   Copyright (C) 2007 Free Software Foundation, Inc.
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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

static QPoint
getLocationPosition( const CalamaresUtils::Locale::TimeZoneData* l )
{
    return TimeZoneImageList::getLocationPosition( l->longitude(), l->latitude() );
}


TimeZoneWidget::TimeZoneWidget( const CalamaresUtils::Locale::ZonesModel* zones, QWidget* parent )
    : QWidget( parent )
    , timeZoneImages( TimeZoneImageList::fromQRC() )
    , m_zonesData( zones )
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
TimeZoneWidget::setCurrentLocation( const TimeZoneData* location )
{
    if ( location == m_currentLocation )
    {
        return;
    }

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
}


//###
//### Private
//###

struct PainterEnder
{
    QPainter& p;
    ~PainterEnder() { p.end(); }
};

void
TimeZoneWidget::paintEvent( QPaintEvent* )
{
    QFontMetrics fontMetrics( font );
    QPainter painter( this );
    PainterEnder painter_end { painter };

    painter.setRenderHint( QPainter::Antialiasing );
    painter.setFont( font );

    // Draw background
    painter.drawImage( 0, 0, background );

    // Draw zone image
    painter.drawImage( 0, 0, currentZoneImage );

    if ( !m_currentLocation )
    {
        return;
    }

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
    auto textwidth = [ & ]( const QString& s ) { return fontMetrics.horizontalAdvance( s ); };
#else
    auto textwidth = [ & ]( const QString& s ) { return fontMetrics.width( s ); };
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
}


void
TimeZoneWidget::mousePressEvent( QMouseEvent* event )
{
    if ( event->button() != Qt::LeftButton )
    {
        return;
    }

    int mX = event->pos().x();
    int mY = event->pos().y();
    auto distance = [ & ]( const CalamaresUtils::Locale::TimeZoneData* zone )
    {
        QPoint locPos = TimeZoneImageList::getLocationPosition( zone->longitude(), zone->latitude() );
        return double( abs( mX - locPos.x() ) + abs( mY - locPos.y() ) );
    };

    const auto* closest = m_zonesData->find( distance );
    if ( closest )
    {
        // Set zone image and repaint widget
        setCurrentLocation( closest );
        // Emit signal
        emit locationChanged( closest );
    }
}
