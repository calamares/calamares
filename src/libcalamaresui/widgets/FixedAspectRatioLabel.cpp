/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "FixedAspectRatioLabel.h"


FixedAspectRatioLabel::FixedAspectRatioLabel( QWidget* parent )
    : QLabel( parent )
{
}


FixedAspectRatioLabel::~FixedAspectRatioLabel() {}


void
FixedAspectRatioLabel::setPixmap( const QPixmap& pixmap )
{
    m_pixmap = pixmap;
    QLabel::setPixmap( pixmap.scaled( contentsRect().size(), Qt::KeepAspectRatio, Qt::SmoothTransformation ) );
}


void
FixedAspectRatioLabel::resizeEvent( QResizeEvent* event )
{
    Q_UNUSED( event )
    QLabel::setPixmap( m_pixmap.scaled( contentsRect().size(), Qt::KeepAspectRatio, Qt::SmoothTransformation ) );
}
