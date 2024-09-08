/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "WaitingWidget.h"

#include "utils/Gui.h"
#include "utils/Logger.h"

#include <QBoxLayout>
#include <QEvent>
#include <QLabel>
#include <QTimer>

static void
colorSpinner( WaitingSpinnerWidget* spinner )
{
    const auto color = spinner->palette().text().color();
    spinner->setTextColor( color );
    spinner->setColor( color );
}

static void
styleSpinner( WaitingSpinnerWidget* spinner, int size )
{
    spinner->setFixedSize( size, size );
    spinner->setInnerRadius( size / 2 );
    spinner->setLineLength( size / 2 );
    spinner->setLineWidth( size / 8 );
    colorSpinner( spinner );
}


WaitingWidget::WaitingWidget( const QString& text, QWidget* parent )
    : WaitingSpinnerWidget( parent, false, false )
{
    int spnrSize = Calamares::defaultFontHeight() * 4;
    styleSpinner( this, spnrSize );
    setAlignment( Qt::AlignmentFlag::AlignBottom );
    setText( text );
    start();
}

WaitingWidget::~WaitingWidget() {}

void
WaitingWidget::changeEvent( QEvent* event )
{
    if ( event->type() == QEvent::PaletteChange )
    {
        colorSpinner( this );
    }
    WaitingSpinnerWidget::changeEvent( event );
}

struct CountdownWaitingWidget::Private
{
    std::chrono::seconds duration;
    // int because we count down, need to be able to show a 0,
    // and then wrap around to duration a second later.
    int count = 0;
    QTimer* timer = nullptr;

    Private( std::chrono::seconds seconds, QWidget* parent )
        : duration( seconds )
        , timer( new QTimer( parent ) )
    {
    }
};

CountdownWaitingWidget::CountdownWaitingWidget( std::chrono::seconds duration, QWidget* parent )
    : WaitingSpinnerWidget( parent, false, false )
    , d( std::make_unique< Private >( duration, this ) )
{
    // Set up the label first for sizing
    const int labelHeight = qBound( 16, Calamares::defaultFontHeight() * 3 / 2, 64 );
    styleSpinner( this, labelHeight );
    setRevolutionsPerSecond( 1.0 / double( duration.count() ) );
    setAlignment( Qt::AlignmentFlag::AlignVCenter );

    // Last because it updates the text
    setInterval( duration );

    d->timer->setInterval( std::chrono::seconds( 1 ) );
    connect( d->timer, &QTimer::timeout, this, &CountdownWaitingWidget::tick );
}

CountdownWaitingWidget::~CountdownWaitingWidget()
{
    d->timer->stop();
}

void
CountdownWaitingWidget::setInterval( std::chrono::seconds duration )
{
    d->duration = duration;
    d->count = int( duration.count() );
    tick();
}

void
CountdownWaitingWidget::start()
{
    // start it from the top
    if ( d->count <= 0 )
    {
        d->count = int( d->duration.count() );
        tick();
    }
    d->timer->start();
    WaitingSpinnerWidget::start();
}

void
CountdownWaitingWidget::stop()
{
    d->timer->stop();
    WaitingSpinnerWidget::stop();
}

void
CountdownWaitingWidget::tick()
{
    // We do want to **display** a 0 which is why we wrap around only
    // after counting down from 0.
    d->count--;
    if ( d->count < 0 )
    {
        d->count = int( d->duration.count() );
    }
    setText( QString::number( d->count ) );
    if ( d->count == 0 )
    {
        timeout();
    }
}

void
CountdownWaitingWidget::changeEvent( QEvent* event )
{
    if ( event->type() == QEvent::PaletteChange )
    {
        colorSpinner( this );
    }
    WaitingSpinnerWidget::changeEvent( event );
}
