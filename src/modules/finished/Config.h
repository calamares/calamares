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

    Q_PROPERTY( bool notifyOnFinished READ notifyOnFinished CONSTANT FINAL )

    Q_PROPERTY( QString failureMessage READ failureMessage NOTIFY failureMessageChanged )
    Q_PROPERTY( QString failureDetails READ failureDetails NOTIFY failureDetailsChanged )
    Q_PROPERTY( bool failed READ hasFailed NOTIFY failureChanged )

public:
    Config( QObject* parent = nullptr );

    void setConfigurationMap( const QVariantMap& configurationMap );

public Q_SLOTS:
    bool notifyOnFinished() const { return m_notifyOnFinished; }

    QString failureMessage() const { return m_failureMessage; }
    QString failureDetails() const { return m_failureDetails; }
    /// Failure is if any of the failure messages is non-empty
    bool hasFailed() const { return !m_failureMessage.isEmpty() || !m_failureDetails.isEmpty(); }

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

    /// @brief Does whatever restart-action is selected / configured
    void doRestart();

Q_SIGNALS:
    void failureMessageChanged( const QString& );
    void failureDetailsChanged( const QString& );
    void failureChanged( bool );

private:
    // Configuration parts
    bool m_notifyOnFinished = false;

    // Dynamic parts
    bool m_hasFailed = false;
    QString m_failureMessage;
    QString m_failureDetails;
};

#endif
