/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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

#ifndef CALAMARESWINDOW_H
#define CALAMARESWINDOW_H

#include <QPointer>
#include <QWidget>

namespace Calamares
{
class DebugWindow;
}

/**
 * @brief The CalamaresWindow class represents the main window of the Calamares UI.
 */
class CalamaresWindow : public QWidget
{
    Q_OBJECT
public:
    CalamaresWindow( QWidget* parent = nullptr );
    virtual ~CalamaresWindow() {}

private:
    QPointer< Calamares::DebugWindow > m_debugWindow;
};

#endif //CALAMARESWINDOW_H
