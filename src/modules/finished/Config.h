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

class Config : public QObject
{
    Q_OBJECT

    Q_PROPERTY( RestartMode restartNowMode READ restartNowMode WRITE setRestartNowMode NOTIFY restartModeChanged )
    Q_PROPERTY( bool restartNowWanted READ restartNowWanted WRITE setRestartNowWanted NOTIFY restartNowWantedChanged )

    Q_PROPERTY( QString restartNowCommand READ restartNowCommand CONSTANT FINAL )
    Q_PROPERTY( bool notifyOnFinished READ notifyOnFinished CONSTANT FINAL )

    Q_PROPERTY( QString failureMessage READ failureMessage NOTIFY failureMessageChanged )
    Q_PROPERTY( QString failureDetails READ failureDetails NOTIFY failureDetailsChanged )
    Q_PROPERTY( bool failed READ hasFailed NOTIFY failureChanged )

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

    void setConfigurationMap( const QVariantMap& configurationMap );

public Q_SLOTS:
    RestartMode restartNowMode() const { return m_restartNowMode; }
    void setRestartNowMode( RestartMode m );

    bool restartNowWanted() const
    {
        if ( restartNowMode() == RestartMode::Never )
        {
            return false;
        }
        return ( restartNowMode() == RestartMode::Always ) || m_userWantsRestart;
    }
    void setRestartNowWanted( bool w );

    QString restartNowCommand() const { return m_restartNowCommand; }
    bool notifyOnFinished() const { return m_notifyOnFinished; }

    QString failureMessage() const { return m_failureMessage; }
    QString failureDetails() const { return m_failureDetails; }
    /// Failure is if any of the failure messages is non-empty
    bool hasFailed() const { return !m_failureMessage.isEmpty() || !m_failureDetails.isEmpty(); }

    /** @brief Run the restart command, if desired.
     *
     * This should generally not be called somewhere during the
     * application's execution, but only in response to QApplication::quit()
     * or something like that when the user expects the system to restart.
     *
     * The "if desired" part is: only if the restart mode allows it,
     * **and** the user has checked the box (or done whatever to
     * turn on restartNowWanted()).
     *
     * - The one-argument form ignores what the user wants and restarts
     *   if @p restartAnyway is @c true **unless** the mode is Never
     * - The no-argument form uses the user setting
     */
    void doRestart( bool restartAnyway );
    void doRestart() { doRestart( restartNowWanted() ); }

    /** @brief Send DBus notification
     *
     * At the end of installation (when the FinishedViewStep is activated),
     * send a desktop notification via DBus that the install is done.
     *
     * - The two-argument form sends success or failure, and can be
     *   forced to send by setting @p sendAnyway to @c true.
     * - The one-argument form sends success or failure and takes
     *   the notifyOnFinished() configuration into account.
     * - The no-argument form checks if a failure was signalled previously
     *   and uses that to decide if it was a failure.
     *
     */
    void doNotify( bool hasFailed, bool sendAnyway );
    void doNotify( bool hasFailed ) { doNotify( hasFailed, notifyOnFinished() ); }
    void doNotify() { doNotify( hasFailed() ); }

    /** @brief Tell the config the install failed
     *
     * This should be connected to the JobQueue and is called by
     * the queue when the installation fails, with a suitable message.
     */
    void onInstallationFailed( const QString& message, const QString& details );

signals:
    void restartModeChanged( RestartMode m );
    void restartNowWantedChanged( bool w );
    void failureMessageChanged( const QString& );
    void failureDetailsChanged( const QString& );
    void failureChanged( bool );

private:
    // Configuration parts
    QString m_restartNowCommand;
    RestartMode m_restartNowMode = RestartMode::Never;
    bool m_userWantsRestart = false;
    bool m_notifyOnFinished = false;

    // Dynamic parts
    bool m_hasFailed = false;
    QString m_failureMessage;
    QString m_failureDetails;
};

const NamedEnumTable< Config::RestartMode >& restartModes();

#endif
