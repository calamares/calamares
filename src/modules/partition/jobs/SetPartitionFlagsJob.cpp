/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2016, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2020, Adriaan de Groot <groot@kde.org>
 *
 *   Based on the SetPartFlagsJob class from KDE Partition Manager,
 *   Copyright 2008, 2010, Volker Lanz <vl@fidra.de>
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

#include "SetPartitionFlagsJob.h"

#include "partition/FileSystem.h"
#include "utils/Logger.h"
#include "utils/Units.h"

#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>
#include <kpmcore/fs/filesystem.h>
#include <kpmcore/ops/setpartflagsoperation.h>
#include <kpmcore/util/report.h>

using CalamaresUtils::BytesToMiB;
using CalamaresUtils::Partition::untranslatedFS;
using CalamaresUtils::Partition::userVisibleFS;

SetPartFlagsJob::SetPartFlagsJob( Device* device, Partition* partition, PartitionTable::Flags flags )
    : PartitionJob( partition )
    , m_device( device )
    , m_flags( flags )
{
}


QString
SetPartFlagsJob::prettyName() const
{
    if ( !partition()->partitionPath().isEmpty() )
    {
        return tr( "Set flags on partition %1." ).arg( partition()->partitionPath() );
    }

    QString fsNameForUser = userVisibleFS( partition()->fileSystem() );
    if ( !fsNameForUser.isEmpty() )
    {
        return tr( "Set flags on %1MiB %2 partition." )
            .arg( BytesToMiB( partition()->capacity() ) )
            .arg( fsNameForUser );
    }
    return tr( "Set flags on new partition." );
}


QString
SetPartFlagsJob::prettyDescription() const
{
    QStringList flagsList = PartitionTable::flagNames( m_flags );
    if ( flagsList.count() == 0 )
    {
        if ( !partition()->partitionPath().isEmpty() )
        {
            return tr( "Clear flags on partition <strong>%1</strong>." ).arg( partition()->partitionPath() );
        }

        QString fsNameForUser = userVisibleFS( partition()->fileSystem() );
        if ( !fsNameForUser.isEmpty() )
        {
            return tr( "Clear flags on %1MiB <strong>%2</strong> partition." )
                .arg( BytesToMiB( partition()->capacity() ) )
                .arg( fsNameForUser );
        }
        return tr( "Clear flags on new partition." );
    }

    if ( !partition()->partitionPath().isEmpty() )
    {
        return tr( "Flag partition <strong>%1</strong> as "
                   "<strong>%2</strong>." )
            .arg( partition()->partitionPath() )
            .arg( flagsList.join( ", " ) );
    }

    QString fsNameForUser = userVisibleFS( partition()->fileSystem() );
    if ( !fsNameForUser.isEmpty() )
    {
        return tr( "Flag %1MiB <strong>%2</strong> partition as "
                   "<strong>%3</strong>." )
            .arg( BytesToMiB( partition()->capacity() ) )
            .arg( fsNameForUser )
            .arg( flagsList.join( ", " ) );
    }

    return tr( "Flag new partition as <strong>%1</strong>." ).arg( flagsList.join( ", " ) );
}


QString
SetPartFlagsJob::prettyStatusMessage() const
{
    QStringList flagsList = PartitionTable::flagNames( m_flags );
    if ( flagsList.count() == 0 )
    {
        if ( !partition()->partitionPath().isEmpty() )
        {
            return tr( "Clearing flags on partition <strong>%1</strong>." ).arg( partition()->partitionPath() );
        }

        QString fsNameForUser = userVisibleFS( partition()->fileSystem() );
        if ( !fsNameForUser.isEmpty() )
        {
            return tr( "Clearing flags on %1MiB <strong>%2</strong> partition." )
                .arg( BytesToMiB( partition()->capacity() ) )
                .arg( fsNameForUser );
        }

        return tr( "Clearing flags on new partition." );
    }

    if ( !partition()->partitionPath().isEmpty() )
    {
        return tr( "Setting flags <strong>%2</strong> on partition "
                   "<strong>%1</strong>." )
            .arg( partition()->partitionPath() )
            .arg( flagsList.join( ", " ) );
    }

    QString fsNameForUser = userVisibleFS( partition()->fileSystem() );
    if ( !fsNameForUser.isEmpty() )
    {
        return tr( "Setting flags <strong>%3</strong> on "
                   "%1MiB <strong>%2</strong> partition." )
            .arg( BytesToMiB( partition()->capacity() ) )
            .arg( fsNameForUser )
            .arg( flagsList.join( ", " ) );
    }

    return tr( "Setting flags <strong>%1</strong> on new partition." ).arg( flagsList.join( ", " ) );
}


Calamares::JobResult
SetPartFlagsJob::exec()
{
    cDebug() << "Setting flags on" << m_device->deviceNode() << "partition" << partition()->deviceNode() << "to"
             << m_flags;

    Report report( nullptr );
    SetPartFlagsOperation op( *m_device, *partition(), m_flags );
    op.setStatus( Operation::StatusRunning );
    connect( &op, &Operation::progress, this, &SetPartFlagsJob::iprogress );

    QString errorMessage
        = tr( "The installer failed to set flags on partition %1." ).arg( m_partition->partitionPath() );
    if ( op.execute( report ) )
    {
        return Calamares::JobResult::ok();
    }

    return Calamares::JobResult::error( errorMessage, report.toText() );
}
