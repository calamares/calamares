/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "DeletePartitionJob.h"

#include "core/KPMHelpers.h"

#include "utils/CalamaresUtilsSystem.h"

#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>
#include <kpmcore/core/partitiontable.h>
#include <kpmcore/fs/filesystem.h>
#include <kpmcore/ops/deleteoperation.h>
#include <kpmcore/util/report.h>

#include <QCoreApplication>

/** @brief Determine if the given partition is of type Zfs
 *
 * Returns true if @p partition is of type Zfs
 *
 */
static bool
isZfs( Partition* partition )
{
    return partition->fileSystem().type() == FileSystem::Type::Zfs;
}

/** @brief Remove the given partition manually
 *
 * Uses sfdisk to remove @p partition.  This should only be used in cases
 * where using kpmcore to remove the partition would not be appropriate
 *
 */
static Calamares::JobResult
removePartition( Partition* partition )
{
    auto r = CalamaresUtils::System::instance()->runCommand(
        { "sfdisk", "--delete", "--force", partition->devicePath(), QString::number( partition->number() ) },
        std::chrono::seconds( 5 ) );
    if ( r.getExitCode() != 0 || r.getOutput().contains( "failed" ) )
    {
        return Calamares::JobResult::error(
            QCoreApplication::translate( DeletePartitionJob::staticMetaObject.className(), "Deletion Failed" ),
            QCoreApplication::translate( DeletePartitionJob::staticMetaObject.className(),
                                         "Failed to delete the partition with output: " )
                + r.getOutput() );
    }
    else
    {
        return Calamares::JobResult::ok();
    }
}

DeletePartitionJob::DeletePartitionJob( Device* device, Partition* partition )
    : PartitionJob( partition )
    , m_device( device )
{
}

QString
DeletePartitionJob::prettyName() const
{
    return tr( "Delete partition %1." ).arg( m_partition->partitionPath() );
}


QString
DeletePartitionJob::prettyDescription() const
{
    return tr( "Delete partition <strong>%1</strong>." ).arg( m_partition->partitionPath() );
}


QString
DeletePartitionJob::prettyStatusMessage() const
{
    return tr( "Deleting partition %1." ).arg( m_partition->partitionPath() );
}


Calamares::JobResult
DeletePartitionJob::exec()
{
    // The current implementation of remove() for zfs in kpmcore trys to destroy the zpool by label
    // This isn't what we want here so we delete the partition instead.
    if ( isZfs( m_partition ) )
    {
        return removePartition( m_partition );
    }

    return KPMHelpers::execute( DeleteOperation( *m_device, m_partition ),
                                tr( "The installer failed to delete partition %1." ).arg( m_partition->devicePath() ) );
}

void
DeletePartitionJob::updatePreview()
{
    m_partition->parent()->remove( m_partition );
    m_device->partitionTable()->updateUnallocated( *m_device );

    // Copied from PM DeleteOperation::checkAdjustLogicalNumbers():
    //
    // If the deleted partition is a logical one, we need to adjust the numbers
    // of the other logical partitions in the extended one, if there are any,
    // because the OS will do that, too: Logicals must be numbered without gaps,
    // i.e., a numbering like sda5, sda6, sda8 (after sda7 is deleted) will
    // become sda5, sda6, sda7
    Partition* parentPartition = dynamic_cast< Partition* >( m_partition->parent() );
    if ( parentPartition && parentPartition->roles().has( PartitionRole::Extended ) )
    {
        parentPartition->adjustLogicalNumbers( m_partition->number(), -1 );
    }
}
