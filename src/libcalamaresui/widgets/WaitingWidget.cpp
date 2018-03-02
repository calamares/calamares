/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
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

#include "WaitingWidget.h"

#include "utils/CalamaresUtilsGui.h"
#include "waitingspinnerwidget.h"

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
