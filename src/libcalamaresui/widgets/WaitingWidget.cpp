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

#include "utils/CalamaresUtilsGui.h"

#include <QBoxLayout>
#include <QLabel>
#include <QTimer>

WaitingWidget::WaitingWidget( const QString& text, QWidget* parent )
    : WaitingSpinnerWidget( parent, false, false )
{
    int spnrSize = CalamaresUtils::defaultFontHeight() * 4;
    setFixedSize( spnrSize, spnrSize );
    setInnerRadius( spnrSize / 2 );
    setLineLength( spnrSize / 2 );
    setLineWidth( spnrSize / 8 );
    setAlignment( Qt::AlignmentFlag::AlignBottom );
    setText( text );
    start();
}

WaitingWidget::~WaitingWidget() {}

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
    const int labelHeight = qBound( 16, CalamaresUtils::defaultFontHeight() * 3 / 2, 64 );

    // Set up the spinner
    setFixedSize( labelHeight, labelHeight );
    setRevolutionsPerSecond( 1.0 / double( duration.count() ) );
    setInnerRadius( labelHeight / 2 );
    setLineLength( labelHeight / 2 );
    setLineWidth( labelHeight / 8 );
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
