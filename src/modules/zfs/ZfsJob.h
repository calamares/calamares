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
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( ZfsJobFactory )

#endif  // ZFSJOB_H
