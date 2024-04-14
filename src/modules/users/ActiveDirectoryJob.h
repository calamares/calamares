/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2024 Simon Quigley <tsimonq2@ubuntu.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef ACTIVEDIRECTORYJOB_H
#define ACTIVEDIRECTORYJOB_H

#include "Job.h"

class ActiveDirectoryJob : public Calamares::Job
{
    Q_OBJECT
public:
    ActiveDirectoryJob( const QString& adminLogin,
                        const QString& adminPassword,
                        const QString& domain,
                        const QString& ip );
    QString prettyName() const override;
    QString prettyStatusMessage() const override;
    Calamares::JobResult exec() override;

private:
    QString m_adminLogin;  // Admin credentials to do the enrollment
    QString m_adminPassword;
    QString m_domain;
    QString m_ip;
};

#endif /* ACTIVEDIRECTORYJOB_H */
