/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef PLASMALNFJOB_H
#define PLASMALNFJOB_H

#include <QObject>
#include <QVariantMap>

#include "Job.h"

class PlasmaLnfJob : public Calamares::Job
{
    Q_OBJECT

public:
    explicit PlasmaLnfJob( const QString& lnfPath, const QString& id );
    ~PlasmaLnfJob() override;

    QString prettyName() const override;

    Calamares::JobResult exec() override;

private:
    QString m_lnfPath;
    QString m_id;
};

#endif  // PLASMALNFJOB_H
