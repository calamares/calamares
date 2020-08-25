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
