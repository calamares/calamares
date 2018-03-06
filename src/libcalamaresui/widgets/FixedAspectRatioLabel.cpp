/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2015, Teo Mrnjavac <teo@kde.org>
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

#include "FixedAspectRatioLabel.h"


FixedAspectRatioLabel::FixedAspectRatioLabel( QWidget* parent )
    : QLabel( parent )
{}


FixedAspectRatioLabel::~FixedAspectRatioLabel()
{}


void
FixedAspectRatioLabel::setPixmap( const QPixmap& pixmap )
{
    m_pixmap = pixmap;
    QLabel::setPixmap( pixmap.scaled(
                           contentsRect().size(),
                           Qt::KeepAspectRatio,
                           Qt::SmoothTransformation ) );
}


void
FixedAspectRatioLabel::resizeEvent( QResizeEvent* event )
{
    Q_UNUSED( event );
    QLabel::setPixmap( m_pixmap.scaled(
                           contentsRect().size(),
                           Qt::KeepAspectRatio,
                           Qt::SmoothTransformation ) );
}

