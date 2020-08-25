/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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
};


#endif
