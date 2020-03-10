/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2018, Adriaan de Groot <groot@kde.org>
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

#ifndef RESIZEFSJOB_H
#define RESIZEFSJOB_H

#include <QObject>
#include <QVariantMap>

#include "CppJob.h"

#include "partition/KPMManager.h"
#include "partition/PartitionSize.h"
#include "utils/PluginFactory.h"

#include "DllMacro.h"

class CoreBackend;  // From KPMCore
class Device;  // From KPMCore
class Partition;

using PartitionSize = CalamaresUtils::Partition::PartitionSize;

class PLUGINDLLEXPORT ResizeFSJob : public Calamares::CppJob
{
    Q_OBJECT

public:
    explicit ResizeFSJob( QObject* parent = nullptr );
    virtual ~ResizeFSJob() override;

    QString prettyName() const override;

    Calamares::JobResult exec() override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;

    /** @brief Is the configuration of this job valid? */
    bool isValid() const
    {
        return ( !m_fsname.isEmpty() || !m_devicename.isEmpty() ) &&
               m_size.isValid();
    }

    QString name() const
    {
        return m_fsname.isEmpty() ? m_devicename : m_fsname;
    }

    PartitionSize size() const
    {
        return m_size;
    }

    PartitionSize minimumSize() const
    {
        return m_atleast;
    }

private:
    CalamaresUtils::Partition::KPMManager m_kpmcore;
    PartitionSize m_size;
    PartitionSize m_atleast;
    QString m_fsname;  // Either this, or devicename, is set, not both
    QString m_devicename;
    bool m_required;

    using PartitionMatch = QPair<Device*, Partition*>;
    /** @brief Find the configured FS */
    PartitionMatch findPartition();

    /** @brief Return a new end-sector for the given dev-part pair. */
    qint64 findGrownEnd( PartitionMatch );
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( ResizeFSJobFactory )

#endif // RESIZEFSJOB_H
