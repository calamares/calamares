/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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

#ifndef SETTIMEZONEJOB_H
#define SETTIMEZONEJOB_H

#include <Job.h>


class SetTimezoneJob : public Calamares::Job
{
    Q_OBJECT
public:
    SetTimezoneJob( const QString& region,
                   const QString& zone );

    QString prettyName() const override;
    Calamares::JobResult exec() override;

private:
    QString m_region;
    QString m_zone;
};

#endif /* SETTIMEZONEJOB_H */
