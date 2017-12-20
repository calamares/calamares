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

#include "ClickableLabel.h"

#include <QApplication>


ClickableLabel::ClickableLabel( QWidget* parent )
    : QLabel( parent )
{}


ClickableLabel::ClickableLabel( const QString& text, QWidget* parent )
    : QLabel( text, parent )
{}


ClickableLabel::~ClickableLabel()
{}


void
ClickableLabel::mousePressEvent( QMouseEvent* event )
{
    QLabel::mousePressEvent( event );
    m_time.start();
}


void
ClickableLabel::mouseReleaseEvent( QMouseEvent* event )
{
    QLabel::mouseReleaseEvent( event );
    if ( m_time.elapsed() < qApp->doubleClickInterval() )
        emit clicked();
}
