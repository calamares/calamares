/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef FINISHED_CONFIG_H
#define FINISHED_CONFIG_H

#include "utils/NamedEnum.h"

#include <QObject>

#include <memory>

class Config : public QObject
{
    Q_OBJECT

    Q_PROPERTY( RestartMode restartNowMode READ restartNowMode WRITE setRestartNowMode NOTIFY restartModeChanged )
    Q_PROPERTY( bool restartNowWanted READ restartNowWanted WRITE setRestartNowWanted NOTIFY restartNowWantedChanged )

    Q_PROPERTY( QString restartNowCommand READ restartNowCommand CONSTANT FINAL )
    Q_PROPERTY( bool notifyOnFinished READ notifyOnFinished CONSTANT FINAL )

public:
    Config( QObject* parent = nullptr );

    enum class RestartMode
    {
        Never,
        UserDefaultUnchecked,
        UserDefaultChecked,
        Always
    };
    Q_ENUM( RestartMode )

    RestartMode restartNowMode() const { return m_restartNowMode; }
    bool restartNowWanted() const { return m_userWantsRestart; }

    QString restartNowCommand() const { return m_restartNowCommand; }
    bool notifyOnFinished() const { return m_notifyOnFinished; }

    void setConfigurationMap( const QVariantMap& configurationMap );

public slots:
    void setRestartNowMode( RestartMode m );
    void setRestartNowWanted( bool w );

signals:
    void restartModeChanged( RestartMode m );
    void restartNowWantedChanged( bool w );

private:
    QString m_restartNowCommand;
    RestartMode m_restartNowMode = RestartMode::Never;
    bool m_userWantsRestart = false;
    bool m_notifyOnFinished = false;
};

const NamedEnumTable< Config::RestartMode >& restartModes();

#endif
