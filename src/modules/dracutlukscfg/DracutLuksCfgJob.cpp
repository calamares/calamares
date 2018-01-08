/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2016, Kevin Kofler <kevin.kofler@chello.at>
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

#include "DracutLuksCfgJob.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>

#include "CalamaresVersion.h"
#include "JobQueue.h"
#include "GlobalStorage.h"

#include "utils/Logger.h"

// static
const QLatin1Literal DracutLuksCfgJob::CONFIG_FILE( "/etc/dracut.conf.d/calamares-luks.conf" );

// static
const char *DracutLuksCfgJob::CONFIG_FILE_HEADER =
    "# Configuration file automatically written by the Calamares system installer\n"
    "# (This file is written once at install time and should be safe to edit.)\n"
    "# Enables support for LUKS full disk encryption with single sign on from GRUB.\n"
    "\n";

// static
const char *DracutLuksCfgJob::CONFIG_FILE_CRYPTTAB_KEYFILE_LINE =
    "# force installing /etc/crypttab even if hostonly=\"no\", install the keyfile\n"
    "install_items+=\" /etc/crypttab /crypto_keyfile.bin \"\n";

// static
const char *DracutLuksCfgJob::CONFIG_FILE_CRYPTTAB_LINE =
    "# force installing /etc/crypttab even if hostonly=\"no\"\n"
    "install_items+=\" /etc/crypttab \"\n";

// static
const QLatin1Literal DracutLuksCfgJob::CONFIG_FILE_SWAPLINE( "# enable automatic resume from swap\nadd_device+=\" /dev/disk/by-uuid/%1 \"\n" );

// static
QString
DracutLuksCfgJob::rootMountPoint()
{
    Calamares::GlobalStorage *globalStorage = Calamares::JobQueue::instance()->globalStorage();
    return globalStorage->value( QStringLiteral( "rootMountPoint" ) ).toString();
}

// static
QVariantList
DracutLuksCfgJob::partitions()
{
    Calamares::GlobalStorage *globalStorage = Calamares::JobQueue::instance()->globalStorage();
    return globalStorage->value( QStringLiteral( "partitions" ) ).toList();
}

// static
bool
DracutLuksCfgJob::isRootEncrypted()
{
    const QVariantList partitions = DracutLuksCfgJob::partitions();
    for ( const QVariant &partition : partitions )
    {
        QVariantMap partitionMap = partition.toMap();
        QString mountPoint = partitionMap.value( QStringLiteral( "mountPoint" ) ).toString();
        if ( mountPoint == QStringLiteral( "/" ) )
            return partitionMap.contains( QStringLiteral( "luksMapperName" ) );
    }
    return false;
}

// static
bool
DracutLuksCfgJob::hasUnencryptedSeparateBoot()
{
    const QVariantList partitions = DracutLuksCfgJob::partitions();
    for ( const QVariant &partition : partitions )
    {
        QVariantMap partitionMap = partition.toMap();
        QString mountPoint = partitionMap.value( QStringLiteral( "mountPoint" ) ).toString();
        if ( mountPoint == QStringLiteral( "/boot" ) )
            return !partitionMap.contains( QStringLiteral( "luksMapperName" ) );
    }
    return false;
}

// static
QString
DracutLuksCfgJob::swapOuterUuid()
{
    const QVariantList partitions = DracutLuksCfgJob::partitions();
    for ( const QVariant &partition : partitions )
    {
        QVariantMap partitionMap = partition.toMap();
        QString fsType = partitionMap.value( QStringLiteral( "fs" ) ).toString();
        if ( fsType == QStringLiteral( "linuxswap" ) && partitionMap.contains( QStringLiteral( "luksMapperName" ) ) )
            return partitionMap.value( QStringLiteral( "luksUuid" ) ).toString();
    }
    return QString();
}

DracutLuksCfgJob::DracutLuksCfgJob( QObject* parent )
    : Calamares::CppJob( parent )
{
}


DracutLuksCfgJob::~DracutLuksCfgJob()
{
}


QString
DracutLuksCfgJob::prettyName() const
{
    if ( isRootEncrypted() )
        return tr( "Write LUKS configuration for Dracut to %1" ).arg( CONFIG_FILE );
    else
        return tr( "Skip writing LUKS configuration for Dracut: \"/\" partition is not encrypted" );
}


Calamares::JobResult
DracutLuksCfgJob::exec()
{
    if ( isRootEncrypted() )
    {
        const QString realConfigFilePath = rootMountPoint() + CONFIG_FILE;
        cDebug() << "[DRACUTLUKSCFG]: Writing" << realConfigFilePath;
        QDir( QStringLiteral( "/" ) ).mkpath( QFileInfo( realConfigFilePath ).absolutePath() );
        QFile configFile( realConfigFilePath );
        if ( ! configFile.open( QIODevice::WriteOnly | QIODevice::Text ) )
        {
            cDebug() << "[DRACUTLUKSCFG]: Failed to open" << realConfigFilePath;
            return Calamares::JobResult::error( tr( "Failed to open %1" ).arg( realConfigFilePath ) );
        }
        QTextStream outStream( &configFile );
        outStream << CONFIG_FILE_HEADER
                  << ( hasUnencryptedSeparateBoot() ? CONFIG_FILE_CRYPTTAB_LINE
                                                    : CONFIG_FILE_CRYPTTAB_KEYFILE_LINE );
        const QString swapOuterUuid = DracutLuksCfgJob::swapOuterUuid();
        if ( ! swapOuterUuid.isEmpty() )
        {
            cDebug() << "[DRACUTLUKSCFG]: Swap outer UUID" << swapOuterUuid;
            outStream << QString(CONFIG_FILE_SWAPLINE).arg( swapOuterUuid ).toLatin1();
        }
        cDebug() << "[DRACUTLUKSCFG]: Wrote config to" << realConfigFilePath;
    } else
        cDebug() << "[DRACUTLUKSCFG]: / not encrypted, skipping";

    return Calamares::JobResult::ok();
}

CALAMARES_PLUGIN_FACTORY_DEFINITION( DracutLuksCfgJobFactory, registerPlugin<DracutLuksCfgJob>(); )
