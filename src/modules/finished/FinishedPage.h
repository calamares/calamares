/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef FINISHEDPAGE_H
#define FINISHEDPAGE_H

#include <QWidget>

#include "FinishedViewStep.h"

namespace Ui
{
class FinishedPage;
}

class FinishedPage : public QWidget
{
    Q_OBJECT
public:
    explicit FinishedPage( QWidget* parent = nullptr );

    void setRestart( FinishedViewStep::RestartMode mode );
    void setRestartNowCommand( const QString& command );

    void setUpRestart();

public slots:
    void onInstallationFailed( const QString& message, const QString& details );

protected:
    void focusInEvent( QFocusEvent* e ) override;  //choose the child widget to focus

private:
    Ui::FinishedPage* ui;

    FinishedViewStep::RestartMode m_mode;
    QString m_restartNowCommand;
};

#endif  // FINISHEDPAGE_H
