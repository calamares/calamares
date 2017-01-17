/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2016, Lisa Vitolo <shainer@chakralinux.org>
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

#ifndef SETAVATARJOB_CPP_H
#define SETAVATARJOB_CPP_H

#include <Job.h>

class SetAvatarJob : public Calamares::Job
{
    Q_OBJECT
public:
    SetAvatarJob( const QString& avatarFile, const QString& destPath, const QString& owner, const QString& group );
    QString prettyName() const override;
    QString prettyDescription() const override;
    QString prettyStatusMessage() const override;
    Calamares::JobResult exec() override;
private:
    const QString m_avatarFile;
    const QString m_destPath;
    // Owner and group of the destination avatar file.
    const QString m_owner;
    const QString m_group;
};


#endif // SETAVATARJOB_CPP_H
