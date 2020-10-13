/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef CREATEUSERJOB_H
#define CREATEUSERJOB_H

#include "Job.h"

class Config;

class CreateUserJob : public Calamares::Job
{
    Q_OBJECT
public:
    CreateUserJob( const Config* config );
    QString prettyName() const override;
    QString prettyDescription() const override;
    QString prettyStatusMessage() const override;
    Calamares::JobResult exec() override;

private:
    const Config* m_config;
    QString m_status;
};

#endif /* CREATEUSERJOB_H */
