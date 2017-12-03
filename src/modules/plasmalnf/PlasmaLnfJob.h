/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
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

#ifndef PLASMALNFJOB_H
#define PLASMALNFJOB_H

#include <QObject>
#include <QVariantMap>

#include <Job.h>

class PlasmaLnfJob : public Calamares::Job
{
    Q_OBJECT

public:
    explicit PlasmaLnfJob( const QString& lnfPath, const QString& id );
    virtual ~PlasmaLnfJob() override;

    QString prettyName() const override;
    QString prettyDescription() const override;
    QString prettyStatusMessage() const override;

    Calamares::JobResult exec() override;

private:
    QString m_lnfPath;
    QString m_id;
};

#endif // PLASMALNFJOB_H
