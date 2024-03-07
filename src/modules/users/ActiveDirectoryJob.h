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
    ActiveDirectoryJob( QStringList& activeDirectoryInfo );
    QString prettyName() const override;
    QString prettyDescription() const override;
    QString prettyStatusMessage() const override;
    Calamares::JobResult exec() override;

private:
    QStringList m_activeDirectoryInfo;
};

#endif /* ACTIVEDIRECTORYJOB_H */
