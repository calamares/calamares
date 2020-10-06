/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef FILLGLOBALSTORAGEJOB_H
#define FILLGLOBALSTORAGEJOB_H

#include "Job.h"

#include <QList>
#include <QVariantList>

class Config;
class Device;
class Partition;

/**
 * This job does not touch devices. It inserts in GlobalStorage the
 * partition-related keys (see hacking/GlobalStorage.md)
 *
 * Inserting the keys after partitioning makes it possible to access
 * information such as the partition path or the UUID.
 */
class FillGlobalStorageJob : public Calamares::Job
{
    Q_OBJECT
public:
    FillGlobalStorageJob( const Config* config, QList< Device* > devices, const QString& bootLoaderPath );

    QString prettyName() const override;
    QString prettyDescription() const override;
    QString prettyStatusMessage() const override;
    Calamares::JobResult exec() override;

private:
    QList< Device* > m_devices;
    QString m_bootLoaderPath;

    QVariantList createPartitionList() const;
    QVariant createBootLoaderMap() const;
};

#endif /* FILLGLOBALSTORAGEJOB_H */
