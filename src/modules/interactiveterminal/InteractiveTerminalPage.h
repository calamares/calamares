/* === This file is part of Calamares - <https://github.com/calamares> ===
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

#ifndef INTERACTIVETERMINALPAGE_H
#define INTERACTIVETERMINALPAGE_H

#include <QWidget>

class QLabel;
class QVBoxLayout;

class InteractiveTerminalPage : public QWidget
{
    Q_OBJECT
public:
    explicit InteractiveTerminalPage( QWidget* parent = nullptr );

    void onActivate();

    void setCommand( const QString& command );

private:
    QVBoxLayout* m_layout;
    QWidget* m_termHostWidget;
    QString m_command;
    QLabel* m_headerLabel;

    void errorKonsoleNotInstalled();
};

#endif // INTERACTIVETERMINALPAGE_H
