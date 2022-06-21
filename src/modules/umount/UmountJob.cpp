/* === This file is part of Calamares - <https://calamares.io> ===
 *
 * Tags from the Python version of this module:
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2016 Anke Boersma <demm@kaosx.us>
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 * Tags for the C++ version of this module:
 *   SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "UmountJob.h"

#include "partition/Mount.h"
#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"
#include "utils/Variant.h"

#include "GlobalStorage.h"
#include "JobQueue.h"

#include <QCoreApplication>
#include <QDir>
#include <QList>

UmountJob::UmountJob( QObject* parent )
    : Calamares::CppJob( parent )
{
}

UmountJob::~UmountJob() {}

QString
UmountJob::prettyName() const
{
    return tr( "Unmount file systems." );
}

static Calamares::JobResult
unmountTargetMounts( const QString& rootMountPoint )
{
    QDir targetMount( rootMountPoint );
    if ( !targetMount.exists() )
    {
        return Calamares::JobResult::internalError(
            QCoreApplication::translate( UmountJob::staticMetaObject.className(), "Could not unmount target system." ),
            QCoreApplication::translate( UmountJob::staticMetaObject.className(),
                                         "The target system is not mounted at '%1'." )
                .arg( rootMountPoint ),
            Calamares::JobResult::GenericError );
    }
    QString targetMountPath = targetMount.absolutePath();
    if ( !targetMountPath.endsWith( '/' ) )
    {
        targetMountPath.append( '/' );
    }

    using MtabInfo = CalamaresUtils::Partition::MtabInfo;
    auto targetMounts = MtabInfo::fromMtabFilteredByPrefix( targetMountPath );
    std::sort( targetMounts.begin(), targetMounts.end(), MtabInfo::mountPointOrder );

    cDebug() << "Read" << targetMounts.count() << "entries from" << targetMountPath;
    for ( const auto& m : qAsConst( targetMounts ) )
    {
        // Returns the program's exit code, so 0 is success and non-0
        // (truthy) is a failure.
        if ( CalamaresUtils::Partition::unmount( m.mountPoint, { "-lv" } ) )
        {
            return Calamares::JobResult::error(
                QCoreApplication::translate( UmountJob::staticMetaObject.className(),
                                             "Could not unmount target system." ),
                QCoreApplication::translate( UmountJob::staticMetaObject.className(),
                                             "The device '%1' is mounted in the target system. It is mounted at '%2'. "
                                             "The device could not be unmounted." )
                    .arg( m.device, m.mountPoint ) );
        }
    }
    return Calamares::JobResult::ok();
}

static Calamares::JobResult
exportZFSPools()
{
    auto* gs = Calamares::JobQueue::instance()->globalStorage();
    QStringList poolNames;
    {
        // The pools are dictionaries / VariantMaps
        auto zfs_pool_list = gs->value( "zfsPoolInfo" ).toList();
        for ( const auto& v : zfs_pool_list )
        {
            auto m = v.toMap();
            QString poolName = m.value( "poolName" ).toString();
            if ( !poolName.isEmpty() )
            {
                poolNames.append( poolName );
            }
        }
        poolNames.sort();
    }

    for ( const auto& poolName : poolNames )
    {
        auto result = CalamaresUtils::System::runCommand( { "zpool", "export", poolName }, std::chrono::seconds( 30 ) );
        if ( result.getExitCode() )
        {
            cWarning() << "Failed to export pool" << result.getOutput();
        }
    }
    // Exporting ZFS pools does not cause the install to fail
    return Calamares::JobResult::ok();
}


Calamares::JobResult
UmountJob::exec()
{
    const auto* sys = CalamaresUtils::System::instance();
    if ( !sys )
    {
        return Calamares::JobResult::internalError(
            "UMount", tr( "No target system available." ), Calamares::JobResult::InvalidConfiguration );
    }

    Calamares::GlobalStorage* gs
        = Calamares::JobQueue::instance() ? Calamares::JobQueue::instance()->globalStorage() : nullptr;
    if ( !gs || gs->value( "rootMountPoint" ).toString().isEmpty() )
    {
        return Calamares::JobResult::internalError(
            "UMount", tr( "No rootMountPoint is set." ), Calamares::JobResult::InvalidConfiguration );
    }

    // Do the unmounting of target-system filesystems
    {
        auto r = unmountTargetMounts( gs->value( "rootMountPoint" ).toString() );
        if ( !r )
        {
            return r;
        }
    }
    // For ZFS systems, export the pools
    {
        auto r = exportZFSPools();
        if ( !r )
        {
            return r;
        }
    }

    return Calamares::JobResult::ok();
}

void
UmountJob::setConfigurationMap( const QVariantMap& map )
{
    Q_UNUSED( map )
}

CALAMARES_PLUGIN_FACTORY_DEFINITION( UmountJobFactory, registerPlugin< UmountJob >(); )
