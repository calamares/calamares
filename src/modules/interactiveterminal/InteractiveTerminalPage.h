/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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

#endif  // INTERACTIVETERMINALPAGE_H
