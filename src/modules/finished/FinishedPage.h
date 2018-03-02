/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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

#ifndef FINISHEDPAGE_H
#define FINISHEDPAGE_H

#include <QWidget>

namespace Ui
{
class FinishedPage;
}

class FinishedPage : public QWidget
{
    Q_OBJECT
public:
    explicit FinishedPage( QWidget* parent = nullptr );

    void setRestartNowEnabled( bool enabled );
    void setRestartNowChecked( bool checked );
    void setRestartNowCommand( const QString& command );

    void setUpRestart();

public slots:
    void onInstallationFailed( const QString& message, const QString& details );

protected:
    void focusInEvent( QFocusEvent* e ) override; //choose the child widget to focus

private:
    Ui::FinishedPage* ui;

    QString m_restartNowCommand;

    bool m_restartSetUp;
};

#endif // FINISHEDPAGE_H
