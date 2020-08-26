/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef SETPASSWORDJOB_H
#define SETPASSWORDJOB_H

#include "Job.h"


class SetPasswordJob : public Calamares::Job
{
    Q_OBJECT
public:
    SetPasswordJob( const QString& userName, const QString& newPassword );
    QString prettyName() const override;
    QString prettyStatusMessage() const override;
    Calamares::JobResult exec() override;

    static QString make_salt( int length );

private:
    QString m_userName;
    QString m_newPassword;
};

#endif /* SETPASSWORDJOB_H */
