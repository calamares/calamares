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

struct ZfsResult {
    bool success;
    QString failureMessage;
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

    QList<QVariant> m_datasets;

    /** @brief Creates a zpool based on the provided arguments
     *
     * Creates a zpool
     * @p deviceName is a full path to the device the zpool should be created on
     * @p poolName is a string containing the name of the pool to create
     * @p poolOptions are the options to pass to zpool create
     * @p encrypt is a boolean which determines if the pool should be encrypted
     * @p passphrase is a string continaing the passphrase
     *
     */
    ZfsResult CreateZpool(QString deviceName, QString poolName, QString poolOptions, bool encrypt, QString passphrase = QString() ) const;


};

CALAMARES_PLUGIN_FACTORY_DECLARATION( ZfsJobFactory )

#endif  // ZFSJOB_H
