/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "ClickableLabel.h"

#include <QApplication>  // for doubleClickInterval()

namespace Calamares
{
namespace Widgets
{

ClickableLabel::ClickableLabel( QWidget* parent )
    : QLabel( parent )
{
}


ClickableLabel::ClickableLabel( const QString& text, QWidget* parent )
    : QLabel( text, parent )
{
}


ClickableLabel::~ClickableLabel() {}


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
    {
        emit clicked();
    }
}
}  // namespace Widgets
}  // namespace Calamares
