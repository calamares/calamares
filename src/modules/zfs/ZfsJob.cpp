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

#include <unistd.h>

/** @brief Returns the alphanumeric portion of a string
 *
 * @p input is the input string
 *
 */
static QString
alphaNumeric( QString input )
{
    return input.remove( QRegExp( "[^a-zA-Z\\d\\s]" ) );
}

/** @brief Returns the best available device for zpool creation
 *
 * zfs partitions generally don't have UUID until the zpool is created. Generally,
 * they are formed using either the id or the partuuid.  The id isn't stored by kpmcore
 * so this function checks to see if we have a partuuid.  If so, it forms a device path
 * for it.  As a backup, it uses the device name i.e. /dev/sdax.
 *
 * The function returns a fully qualified path to the device or an empty string if no device
 * is found
 *
 * @p pMap is the partition map from global storage
 *
 */
static QString
findBestZfsDevice( QVariantMap pMap )
{
    // Find the best device identifier, if one isn't available, skip this partition
    QString deviceName;
    if ( pMap[ "partuuid" ].toString() != "" )
    {
        return "/dev/disk/by-partuuid/" + pMap[ "partuuid" ].toString().toLower();
    }
    else if ( pMap[ "device" ].toString() != "" )
    {
        return pMap[ "device" ].toString().toLower();
    }
    else
    {
        return QString();
    }
}

/** @brief Converts the value in a QVariant to a string which is a valid option for canmount
 *
 * Storing "on" and "off" in QVariant results in a conversion to boolean.  This function takes
 * the Qvariant in @p canMount and converts it to a QString holding "on", "off" or the string
 * value in the QVariant.
 *
 */
static QString
convertCanMount( QVariant canMount )
{
    if ( canMount == true )
    {
        return "on";
    }
    else if ( canMount == false )
    {
        return "off";
    }
    else
    {
        return canMount.toString();
    }
}

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

void
ZfsJob::collectMountpoints( const QVariantList& partitions )
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
ZfsJob::isMountpointOverlapping( const QString& targetMountpoint ) const
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
ZfsJob::createZpool( QString deviceName, QString poolName, QString poolOptions, bool encrypt, QString passphrase ) const
{
    // zfs doesn't wait for the devices so pause for 2 seconds to ensure we give time for the device files to be created
    sleep( 2 );

    QStringList command;
    if ( encrypt )
    {
        command = QStringList() << "zpool"
                                << "create" << poolOptions.split( ' ' ) << "-O"
                                << "encryption=aes-256-gcm"
                                << "-O"
                                << "keyformat=passphrase" << poolName << deviceName;
    }
    else
    {
        command = QStringList() << "zpool"
                                << "create" << poolOptions.split( ' ' ) << poolName << deviceName;
    }

    auto r = CalamaresUtils::System::instance()->runCommand(
        CalamaresUtils::System::RunLocation::RunInHost, command, QString(), passphrase, std::chrono::seconds( 10 ) );

    if ( r.getExitCode() != 0 )
    {
        cWarning() << "Failed to run zpool create.  The output was: " + r.getOutput();
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
                                                    tr( "No partitions are available for ZFS." ),
                                                    Calamares::JobResult::InvalidConfiguration );
    }

    const CalamaresUtils::System* system = CalamaresUtils::System::instance();

    QVariantList poolNames;

    // Check to ensure the list of zfs info from the partition module is available and convert it to a list
    if ( !gs->contains( "zfsInfo" ) && gs->value( "zfsInfo" ).canConvert( QVariant::List ) )
    {
        return Calamares::JobResult::error( tr( "Internal data missing" ), tr( "Failed to create zpool" ) );
    }
    QVariantList zfsInfoList = gs->value( "zfsInfo" ).toList();

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
        QString deviceName = findBestZfsDevice( pMap );
        if ( deviceName.isEmpty() )
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
            poolName += alphaNumeric( mountpoint );
        }

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
            zfsResult = createZpool( deviceName, poolName, m_poolOptions, true, passphrase );
        }
        else
        {
            zfsResult = createZpool( deviceName, poolName, m_poolOptions, false );
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
            collectMountpoints( partitions );
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
                if ( isMountpointOverlapping( datasetMap[ "mountpoint" ].toString() ) )
                {
                    continue;
                }

                QString canMount = convertCanMount( datasetMap[ "canMount" ].toString() );

                // Create the dataset
                auto r = system->runCommand( { QStringList() << "zfs"
                                                             << "create" << m_datasetOptions.split( ' ' ) << "-o"
                                                             << "canmount=" + canMount << "-o"
                                                             << "mountpoint=" + datasetMap[ "mountpoint" ].toString()
                                                             << poolName + "/" + datasetMap[ "dsName" ].toString() },
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
            QString dsName = mountpoint;
            dsName = alphaNumeric( mountpoint );
            auto r = system->runCommand( { QStringList() << "zfs"
                                                         << "create" << m_datasetOptions.split( ' ' ) << "-o"
                                                         << "canmount=on"
                                                         << "-o"
                                                         << "mountpoint=" + mountpoint << poolName + "/" + dsName },
                                         std::chrono::seconds( 10 ) );
            if ( r.getExitCode() != 0 )
            {
                return Calamares::JobResult::error( tr( "Failed to create dataset" ),
                                                    tr( "The output was: " ) + r.getOutput() );
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
