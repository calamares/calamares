/* === This file is part of Calamares - <http://github.com/calamares> ===
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

#include <QLabel>
#include <QBoxLayout>


PrettyRadioButton::PrettyRadioButton( QWidget* parent )
    : QWidget( parent )
{
    QHBoxLayout* mainLayout = new QHBoxLayout;
    setLayout( mainLayout );

    m_radio = new QRadioButton;
    m_label = new ClickableLabel;

    connect( m_label, &ClickableLabel::clicked,
             m_radio, &QRadioButton::click );
    m_label->setBuddy( m_radio );

    m_label->setWordWrap( true );
    m_label->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Preferred );

    mainLayout->addWidget( m_radio );
    mainLayout->addWidget( m_label );
    mainLayout->setContentsMargins( 0, 0, 0, 0 );
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
