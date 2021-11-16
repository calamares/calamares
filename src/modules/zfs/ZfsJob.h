/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 Evan James <dalto@fastmail.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef ZFSJOB_H
#define ZFSJOB_H

#include <QObject>
#include <QStringList>
#include <QVariantMap>

#include "CppJob.h"

#include "utils/PluginFactory.h"

#include "DllMacro.h"

struct ZfsResult
{
    bool success;
    QString failureMessage;  // This message is displayed to the user and should be translated at the time of population
};

/** @brief Create zpools and zfs datasets
 *
 */
class PLUGINDLLEXPORT ZfsJob : public Calamares::CppJob
{
    Q_OBJECT

public:
    explicit ZfsJob( QObject* parent = nullptr );
    ~ZfsJob() override;

    QString prettyName() const override;

    Calamares::JobResult exec() override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;

private:
    QString m_poolName;
    QString m_poolOptions;
    QString m_datasetOptions;
    QStringList m_mountpoints;

    QList< QVariant > m_datasets;

    /** @brief Creates a zpool based on the provided arguments
     *
     * @p deviceName is a full path to the device the zpool should be created on
     * @p poolName is a string containing the name of the pool to create
     * @p poolOptions are the options to pass to zpool create
     * @p encrypt is a boolean which determines if the pool should be encrypted
     * @p passphrase is a string continaing the passphrase
     *
     */
    ZfsResult createZpool( QString deviceName,
                           QString poolName,
                           QString poolOptions,
                           bool encrypt,
                           QString passphrase = QString() ) const;

    /** @brief Collects all the mountpoints from the partitions
     *
     * Iterates over @p partitions to gather each mountpoint present
     * in the list of maps and populates m_mountpoints
     *
     */
    void collectMountpoints( const QVariantList& partitions );

    /** @brief Check to see if a given mountpoint overlaps with one of the defined moutnpoints
     *
     * Iterates over m_partitions and checks if @p targetMountpoint overlaps with them by comparing
     * the beginning of targetMountpoint with all the values in m_mountpoints.  Of course, / is excluded
     * since all the mountpoints would begin with /
     *
     */
    bool isMountpointOverlapping( const QString& targetMountpoint ) const;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( ZfsJobFactory )

#endif  // ZFSJOB_H
