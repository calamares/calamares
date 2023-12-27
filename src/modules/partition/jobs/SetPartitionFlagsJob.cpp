/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2008 2010, Volker Lanz <vl@fidra.de>
 *   SPDX-FileCopyrightText: 2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Based on the SetPartFlagsJob class from KDE Partition Manager
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "SetPartitionFlagsJob.h"

#include "core/KPMHelpers.h"

#include "partition/FileSystem.h"
#include "utils/Logger.h"
#include "utils/Units.h"

#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>
#include <kpmcore/fs/filesystem.h>
#include <kpmcore/ops/setpartflagsoperation.h>
#include <kpmcore/util/report.h>

using Calamares::BytesToMiB;
using Calamares::Partition::untranslatedFS;
using Calamares::Partition::userVisibleFS;

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
        return tr( "Setting flags on partition %1…", "@status" ).arg( partition()->partitionPath() );
    }

    QString fsNameForUser = userVisibleFS( partition()->fileSystem() );
    if ( !fsNameForUser.isEmpty() )
    {
        return tr( "Setting flags on %1MiB %2 partition…", "@status" )
            .arg( BytesToMiB( partition()->capacity() ) )
            .arg( fsNameForUser );
    }
    return tr( "Setting flags on new partition…", "@status" );
}

QString
SetPartFlagsJob::prettyDescription() const
{
    QStringList flagsList = PartitionTable::flagNames( m_flags );
    if ( flagsList.count() == 0 )
    {
        if ( !partition()->partitionPath().isEmpty() )
        {
            return tr( "Clearing flags on partition <strong>%1</strong>…", "@status" ).arg( partition()->partitionPath() );
        }

        QString fsNameForUser = userVisibleFS( partition()->fileSystem() );
        if ( !fsNameForUser.isEmpty() )
        {
            return tr( "Clearing flags on %1MiB <strong>%2</strong> partition…", "@status" )
                .arg( BytesToMiB( partition()->capacity() ) )
                .arg( fsNameForUser );
        }
        return tr( "Clearing flags on new partition…", "@status" );
    }

    if ( !partition()->partitionPath().isEmpty() )
    {
        return tr( "Flagging partition <strong>%1</strong> as "
                   "<strong>%2</strong>…", "@status" )
            .arg( partition()->partitionPath() )
            .arg( flagsList.join( ", " ) );
    }

    QString fsNameForUser = userVisibleFS( partition()->fileSystem() );
    if ( !fsNameForUser.isEmpty() )
    {
        return tr( "Flagging %1MiB <strong>%2</strong> partition as "
                   "<strong>%3</strong>…", "@status" )
            .arg( BytesToMiB( partition()->capacity() ) )
            .arg( fsNameForUser )
            .arg( flagsList.join( ", " ) );
    }

    return tr( "Flagging new partition as <strong>%1</strong>…", "@status" ).arg( flagsList.join( ", " ) );
}

QString
SetPartFlagsJob::prettyStatusMessage() const
{
    QStringList flagsList = PartitionTable::flagNames( m_flags );
    if ( flagsList.count() == 0 )
    {
        if ( !partition()->partitionPath().isEmpty() )
        {
            return tr( "Clearing flags on partition <strong>%1</strong>…", "@status" ).arg( partition()->partitionPath() );
        }

        QString fsNameForUser = userVisibleFS( partition()->fileSystem() );
        if ( !fsNameForUser.isEmpty() )
        {
            return tr( "Clearing flags on %1MiB <strong>%2</strong> partition…", "@status" )
                .arg( BytesToMiB( partition()->capacity() ) )
                .arg( fsNameForUser );
        }

        return tr( "Clearing flags on new partition…", "@status" );
    }

    if ( !partition()->partitionPath().isEmpty() )
    {
        return tr( "Setting flags <strong>%2</strong> on partition "
                   "<strong>%1</strong>…", "@status" )
            .arg( partition()->partitionPath() )
            .arg( flagsList.join( ", " ) );
    }

    QString fsNameForUser = userVisibleFS( partition()->fileSystem() );
    if ( !fsNameForUser.isEmpty() )
    {
        return tr( "Setting flags <strong>%3</strong> on "
                   "%1MiB <strong>%2</strong> partition…", "@status" )
            .arg( BytesToMiB( partition()->capacity() ) )
            .arg( fsNameForUser )
            .arg( flagsList.join( ", " ) );
    }

    return tr( "Setting flags <strong>%1</strong> on new partition…", "@status" ).arg( flagsList.join( ", " ) );
}

Calamares::JobResult
SetPartFlagsJob::exec()
{
    QStringList flagsList = PartitionTable::flagNames( m_flags );
    cDebug() << "Setting flags on" << m_device->deviceNode() << "partition" << partition()->deviceNode()
             << Logger::DebugList( flagsList );

    SetPartFlagsOperation op( *m_device, *partition(), m_flags );
    connect( &op, &Operation::progress, this, &SetPartFlagsJob::iprogress );
    return KPMHelpers::execute(
        op, tr( "The installer failed to set flags on partition %1." ).arg( m_partition->partitionPath() ) );
}
