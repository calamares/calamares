/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019, Adriaan de Groot <groot@kde.org>
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

#ifndef IDJOB_H
#define IDJOB_H

#include "Job.h"

#include <QString>

class IDJob : public Calamares::Job
{
    Q_OBJECT
public:
    explicit IDJob( const QString& id, QObject* parent = nullptr );

    virtual QString prettyName() const override;
    virtual Calamares::JobResult exec() override;

private:
    Calamares::JobResult writeId( const QString&, const QString&, const QString& );

    QString m_batchIdentifier;
} ;


#endif
