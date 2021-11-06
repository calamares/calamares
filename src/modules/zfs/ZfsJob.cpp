/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 Evan James <dalto@fastmail.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "ZfsJob.h"

#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"
#include "utils/Variant.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "Settings.h"

ZfsJob::ZfsJob( QObject* parent )
    : Calamares::CppJob( parent )
{
}

ZfsJob::~ZfsJob() {}

QString
ZfsJob::prettyName() const
{
    return tr( "Create ZFS pools and datasets" );
}

Calamares::JobResult
ZfsJob::exec()
{
    QList< QVariant > partitions;
    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
    if ( gs && gs->contains( "partitions" ) && gs->value( "partitions" ).canConvert( QVariant::List ) )
    {
        partitions = gs->value( "partitions" ).toList();
    }
    else
    {
        cWarning() << "No *partitions* defined.";
        return Calamares::JobResult::internalError( tr( "Configuration Error" ),
                                                    tr( "No partitions are available for Zfs." ),
                                                    Calamares::JobResult::InvalidConfiguration );
    }

    const CalamaresUtils::System* system = CalamaresUtils::System::instance();

    for ( auto& partition : qAsConst( partitions ) )
    {
        QVariantMap pMap;
        if ( partition.canConvert( QVariant::Map ) )
        {
            pMap = partition.toMap();
        }

        // If it isn't a zfs partition, ignore it
        if ( pMap[ "fsName" ] != "zfs" )
        {
            continue;
        }

        // Find the best device identifier, if one isn't available, skip this partition
        QString deviceName;
        if ( pMap[ "partuuid" ].toString() != "" )
        {
            deviceName = "/dev/disk/by-partuuid/" + pMap[ "partuuid" ].toString().toLower();
        }
        else if ( pMap[ "device" ].toString() != "" )
        {
            deviceName = pMap[ "device" ].toString().toLower();
        }
        else
        {
            continue;
        }

        // Create the zpool
        auto r
            = system->runCommand( { "sh", "-c", "zpool create " + m_poolOptions + " " + m_poolName + " " + deviceName },
                                  std::chrono::seconds( 10 ) );
        if ( r.getExitCode() != 0 )
        {
            return Calamares::JobResult::error( tr( "zpool failure" ),
                                                tr( "Failed to create zpool on " + deviceName.toLocal8Bit() ) );
        }

        // Create the datasets
        for ( const auto& dataset : qAsConst( m_datasets ) )
        {
            QVariantMap dsMap = dataset.toMap();

            // Make sure all values are valid
            if ( dsMap[ "dsName" ].toString().isEmpty() || dsMap[ "mountpoint" ].toString().isEmpty()
                 || dsMap[ "canMount" ].toString().isEmpty() )
            {
                cWarning() << "Bad dataset entry";
                continue;
            }

            // Create the dataset.  We set canmount=no regardless of the setting for now.
            // It is modified to the correct value in the mount module to ensure mount order is maintained
            r = system->runCommand( { "sh",
                                      "-c",
                                      "zfs create " + m_datasetOptions
                                          + " -o canmount=off -o mountpoint=" + dsMap[ "mountpoint" ].toString() + " "
                                          + m_poolName + "/" + dsMap[ "dsName" ].toString() },
                                    std::chrono::seconds( 10 ) );
            if ( r.getExitCode() != 0 )
            {
                cWarning() << "Failed to create dataset" << dsMap[ "dsName" ].toString();
            }
        }
    }

    return Calamares::JobResult::ok();
}


void
ZfsJob::setConfigurationMap( const QVariantMap& map )
{
    m_poolName = CalamaresUtils::getString( map, "poolName" );
    m_poolOptions = CalamaresUtils::getString( map, "poolOptions" );
    m_datasetOptions = CalamaresUtils::getString( map, "datasetOptions" );

    m_datasets = CalamaresUtils::getList( map, "datasets" );
}

CALAMARES_PLUGIN_FACTORY_DEFINITION( ZfsJobFactory, registerPlugin< ZfsJob >(); )
