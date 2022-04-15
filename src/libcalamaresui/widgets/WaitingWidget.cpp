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

#include "3rdparty/waitingspinnerwidget.h"

#include <QBoxLayout>
#include <QLabel>
#include <QTimer>

WaitingWidget::WaitingWidget( const QString& text, QWidget* parent )
    : QWidget( parent )
{
    QBoxLayout* waitingLayout = new QVBoxLayout;
    setLayout( waitingLayout );
    waitingLayout->addStretch();
    QBoxLayout* pbLayout = new QHBoxLayout;
    waitingLayout->addLayout( pbLayout );
    pbLayout->addStretch();

    WaitingSpinnerWidget* spnr = new WaitingSpinnerWidget();
    pbLayout->addWidget( spnr );

    pbLayout->addStretch();

    m_waitingLabel = new QLabel( text );

    int spnrSize = m_waitingLabel->fontMetrics().height() * 4;
    spnr->setFixedSize( spnrSize, spnrSize );
    spnr->setInnerRadius( spnrSize / 2 );
    spnr->setLineLength( spnrSize / 2 );
    spnr->setLineWidth( spnrSize / 8 );
    spnr->start();

    m_waitingLabel->setAlignment( Qt::AlignCenter );
    waitingLayout->addSpacing( spnrSize / 2 );
    waitingLayout->addWidget( m_waitingLabel );
    waitingLayout->addStretch();

    CalamaresUtils::unmarginLayout( waitingLayout );
}


void
WaitingWidget::setText( const QString& text )
{
    m_waitingLabel->setText( text );
}

struct CountdownWaitingWidget::Private
{
    std::chrono::seconds duration;
    // int because we count down, need to be able to show a 0,
    // and then wrap around to duration a second later.
    int count = 0;
    WaitingSpinnerWidget* spinner = nullptr;
    QLabel* label = nullptr;
    QTimer* timer = nullptr;

    Private( std::chrono::seconds seconds, QWidget* parent )
        : duration( seconds )
        , spinner( new WaitingSpinnerWidget( parent ) )
        , label( new QLabel( parent ) )
        , timer( new QTimer( parent ) )
    {
    }
};

CountdownWaitingWidget::CountdownWaitingWidget( std::chrono::seconds duration, QWidget* parent )
    : QWidget( parent )
    , d( std::make_unique< Private >( duration, this ) )
{
    // Set up the label first for sizing
    const int labelHeight = d->label->fontMetrics().height() * 3 / 2;

    // Set up the spinner
    d->spinner->setFixedSize( labelHeight, labelHeight );

    // Overall UI layout
    QBoxLayout* box = new QHBoxLayout;
    box->addWidget( d->spinner );
    box->addWidget( d->label );
    setLayout( box );

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
}

void
CountdownWaitingWidget::stop()
{
    d->timer->stop();
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
    d->label->setText( QString::number( d->count ) );
    if ( d->count == 0 )
    {
        timeout();
    }
}
