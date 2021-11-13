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

#include <QProcess>

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

QString
ZfsJob::AlphaNumeric( QString input ) const
{
    return input.remove( QRegExp( "[^a-zA-Z\\d\\s]" ) );
}

void
ZfsJob::CollectMountpoints( const QVariantList& partitions )
{
    m_mountpoints.empty();
    for ( const QVariant& partition : partitions )
    {
        if ( partition.canConvert( QVariant::Map ) )
        {
            QString mountpoint = partition.toMap().value( "mountPoint" ).toString();
            if ( !mountpoint.isEmpty() )
            {
                m_mountpoints.append( mountpoint );
            }
        }
    }
}

bool
ZfsJob::IsMountpointOverlapping( const QString& targetMountpoint ) const
{
    for ( const QString& mountpoint : m_mountpoints )
    {
        if ( mountpoint != '/' && targetMountpoint.startsWith( mountpoint ) )
        {
            return true;
        }
    }
    return false;
}


ZfsResult
ZfsJob::CreateZpool( QString deviceName, QString poolName, QString poolOptions, bool encrypt, QString passphrase ) const
{
    // zfs doesn't wait for the devices so pause for 2 seconds to ensure we give time for the device files to be created
    QString command;
    if ( encrypt )
    {
        command = "sleep 2 ; echo \"" + passphrase + "\" | zpool create " + poolOptions
            + " -O encryption=aes-256-gcm -O keyformat=passphrase " + poolName + " " + deviceName;
    }
    else
    {
        command = "sleep 2 ; zpool create " + poolOptions + " " + poolName + " " + deviceName;
    }

    // We use a qProcess instead of runCommand so the password will not end up in the logs
    QProcess process;

    process.setProcessChannelMode( QProcess::MergedChannels );
    cDebug() << Logger::SubEntry << "Running zpool create";

    process.start( "sh", QStringList() << "-c" << command );

    if ( !process.waitForStarted() )
    {
        return { false, tr( "zpool create process failed to start" ) };
    }

    if ( !process.waitForFinished( 5000 ) )
    {
        return { false, tr( "Process for zpool create timed out" ) };
    }

    QString output = QString::fromLocal8Bit( process.readAllStandardOutput() ).trimmed();

    if ( process.exitStatus() == QProcess::CrashExit )
    {
        return { false, tr( "The output from the crash was: " ) + output };
    }

    auto exitcode = process.exitCode();
    if ( exitcode != 0 )
    {
        cWarning() << "Failed to run zpool create.  The output was: " + output;
        return { false, tr( "Failed to create zpool on " ) + deviceName };
    }

    return { true, QString() };
}

Calamares::JobResult
ZfsJob::exec()
{
    QVariantList partitions;
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

    QVariantList poolNames;

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

        // If the partition doesn't have a mountpoint, skip it
        QString mountpoint = pMap[ "mountPoint" ].toString();
        if ( mountpoint.isEmpty() )
        {
            continue;
        }

        // Build a poolname off config pool name and the mountpoint, this is not ideal but should work until there is UI built for zfs
        QString poolName = m_poolName;
        if ( mountpoint != '/' )
        {
            poolName += AlphaNumeric( mountpoint );
        }

        // Check to ensure the list of zfs info from the partition module is available and convert it to a list
        if ( !gs->contains( "zfsInfo" ) && gs->value( "zfsInfo" ).canConvert( QVariant::List ) )
        {
            return Calamares::JobResult::error( tr( "Internal data missing" ), tr( "Failed to create zpool" ) );
        }
        QVariantList zfsInfoList = gs->value( "zfsInfo" ).toList();

        // Look in the zfs info list to see if this partition should be encrypted
        bool encrypt = false;
        QString passphrase;
        for ( const QVariant& zfsInfo : qAsConst( zfsInfoList ) )
        {
            if ( zfsInfo.canConvert( QVariant::Map ) && zfsInfo.toMap().value( "encrypted" ).toBool()
                 && mountpoint == zfsInfo.toMap().value( "mountpoint" ) )
            {
                encrypt = true;
                passphrase = zfsInfo.toMap().value( "passphrase" ).toString();
            }
        }

        // Create the zpool
        ZfsResult zfsResult;
        if ( encrypt )
        {
            zfsResult = CreateZpool( deviceName, poolName, m_poolOptions, true, passphrase );
        }
        else
        {
            zfsResult = CreateZpool( deviceName, poolName, m_poolOptions, false );
        }

        if ( !zfsResult.success )
        {
            return Calamares::JobResult::error( tr( "Failed to create zpool" ), zfsResult.failureMessage );
        }

        // Save the poolname, dataset name and mountpoint.  It will later be added to a list and placed in global storage.
        // This will be used by later modules including mount and umount
        QVariantMap poolNameEntry;
        poolNameEntry[ "poolName" ] = poolName;
        poolNameEntry[ "mountpoint" ] = mountpoint;
        poolNameEntry[ "dsName" ] = "none";

        // If the mountpoint is /, create datasets per the config file. If not, create a single dataset mounted at the partitions mountpoint
        if ( mountpoint == '/' )
        {
            CollectMountpoints( partitions );
            QVariantList datasetList;
            for ( const auto& dataset : qAsConst( m_datasets ) )
            {
                QVariantMap datasetMap = dataset.toMap();

                // Make sure all values are valid
                if ( datasetMap[ "dsName" ].toString().isEmpty() || datasetMap[ "mountpoint" ].toString().isEmpty()
                     || datasetMap[ "canMount" ].toString().isEmpty() )
                {
                    cWarning() << "Bad dataset entry";
                    continue;
                }

                // We should skip this dataset if it conflicts with a permanent mountpoint
                if ( IsMountpointOverlapping( datasetMap[ "mountpoint" ].toString() ) )
                {
                    continue;
                }

                // Create the dataset.  We set canmount=no regardless of the setting for now.
                // It is modified to the correct value in the mount module to ensure mount order is maintained
                auto r = system->runCommand( { "sh",
                                               "-c",
                                               "zfs create " + m_datasetOptions + " -o canmount=off -o mountpoint="
                                                   + datasetMap[ "mountpoint" ].toString() + " " + poolName + "/"
                                                   + datasetMap[ "dsName" ].toString() },
                                             std::chrono::seconds( 10 ) );
                if ( r.getExitCode() != 0 )
                {
                    cWarning() << "Failed to create dataset" << datasetMap[ "dsName" ].toString();
                    continue;
                }

                // Add the dataset to the list for global storage this information is used later to properly set
                // the mount options on each dataset
                datasetMap[ "zpool" ] = m_poolName;
                datasetList.append( datasetMap );
            }

            // If the list isn't empty, add it to global storage
            if ( !datasetList.isEmpty() )
            {
                gs->insert( "zfsDatasets", datasetList );
            }
        }
        else
        {
            // This is a zpool with a single dataset We again set canmount=no regardless of the desired setting.
            // It is modified to the correct value in the mount module to ensure mount order is maintained
            QString dsName = mountpoint;
            dsName = AlphaNumeric( mountpoint );
            auto r = system->runCommand( { "sh",
                                           "-c",
                                           "zfs create " + m_datasetOptions + " -o canmount=off -o mountpoint="
                                               + mountpoint + " " + poolName + "/" + dsName },
                                         std::chrono::seconds( 10 ) );
            if ( r.getExitCode() != 0 )
            {
                cWarning() << "Failed to create dataset" << dsName;
            }
            poolNameEntry[ "dsName" ] = dsName;
        }

        poolNames.append( poolNameEntry );

        // Export the zpool so it can be reimported at the correct location later
        auto r = system->runCommand( { "zpool", "export", poolName }, std::chrono::seconds( 10 ) );
        if ( r.getExitCode() != 0 )
        {
            cWarning() << "Failed to export pool" << m_poolName;
        }
    }

    // Put the list of zpools into global storage
    if ( !poolNames.isEmpty() )
    {
        gs->insert( "zfsPoolInfo", poolNames );
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
