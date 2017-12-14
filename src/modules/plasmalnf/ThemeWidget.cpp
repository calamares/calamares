/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
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

#include "ThemeWidget.h"

#include "ThemeInfo.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QRadioButton>

ThemeWidget::ThemeWidget(const ThemeInfo& info, QWidget* parent)
    : QWidget( parent )
    , m_check( new QRadioButton( info.name.isEmpty() ? info.id : info.name, parent ) )
    , m_id( info.id )
{
    QHBoxLayout* layout = new QHBoxLayout( this );
    this->setLayout( layout );

    layout->addWidget( m_check, 1 );
    layout->addWidget( new QLabel( "Image", this ), 1 );
    layout->addWidget( new QLabel( info.description, this ), 3 );

    connect( m_check, &QRadioButton::clicked, this, &ThemeWidget::clicked );
}

void
ThemeWidget::clicked( bool checked )
{
    if ( checked )
        emit themeSelected( m_id );
}

QAbstractButton*
ThemeWidget::button() const
{
    return m_check;
}
