/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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

#include "PrettyRadioButton.h"

#include "utils/CalamaresUtilsGui.h"
#include "widgets/ClickableLabel.h"

#include <QComboBox>
#include <QGridLayout>
#include <QLabel>


PrettyRadioButton::PrettyRadioButton( QWidget* parent )
    : QWidget( parent )
{
    m_mainLayout = new QGridLayout;
    setLayout( m_mainLayout );

    m_radio = new QRadioButton;
    m_label = new ClickableLabel;

    connect( m_label, &ClickableLabel::clicked,
             m_radio, &QRadioButton::click );
    m_label->setBuddy( m_radio );

    m_label->setWordWrap( true );
    m_label->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Preferred );

    m_mainLayout->addWidget( m_radio, 0, 0 );
    m_mainLayout->addWidget( m_label, 0, 1, -1, 1 );  // Row span to right edge
    m_mainLayout->setContentsMargins( 0, 0, 0, 0 );
}


void
PrettyRadioButton::setText( const QString& text )
{
    m_label->setText( text );
}


void
PrettyRadioButton::setIconSize( const QSize& size )
{
    m_radio->setIconSize( size );
}


void
PrettyRadioButton::setIcon( const QIcon& icon )
{
    m_radio->setIcon( icon );
}


QSize
PrettyRadioButton::iconSize() const
{
    return m_radio->iconSize();
}


QRadioButton*
PrettyRadioButton::buttonWidget() const
{
    return m_radio;
}

void
PrettyRadioButton::addOptionsComboBox( QComboBox* box )
{
    int row = m_mainLayout->rowCount();  // Rows index from 0, count from 1
    m_mainLayout->addWidget( box, row, 1 );
}
