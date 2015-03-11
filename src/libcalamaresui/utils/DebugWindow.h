/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2015, Teo Mrnjavac <teo@kde.org>
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

#ifndef CALAMARES_DEBUGWINDOW_H
#define CALAMARES_DEBUGWINDOW_H

#include "ui_DebugWindow.h"

#include <QWidget>

namespace Calamares {

class DebugWindow : public QWidget, private Ui::DebugWindow
{
    Q_OBJECT

public:
    explicit DebugWindow();

signals:
    void closed();

protected:
    void closeEvent( QCloseEvent* e ) override;

};


} // namespace Calamares
#endif // CALAMARES_DEBUGWINDOW_H
