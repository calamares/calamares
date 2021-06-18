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

#include "CreatePartitionTableJob.h"

#include "partition/PartitionIterator.h"
#include "utils/Logger.h"

// KPMcore
#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>
#include <kpmcore/core/partitiontable.h>
#include <kpmcore/fs/filesystem.h>
#include <kpmcore/ops/createpartitiontableoperation.h>
#include <kpmcore/util/report.h>

// Qt
#include <QProcess>

using CalamaresUtils::Partition::PartitionIterator;

CreatePartitionTableJob::CreatePartitionTableJob( Device* device, PartitionTable::TableType type )
    : m_device( device )
    , m_type( type )
{
}

QString
CreatePartitionTableJob::prettyName() const
{
    return tr( "Create new %1 partition table on %2." )
        .arg( PartitionTable::tableTypeToName( m_type ) )
        .arg( m_device->deviceNode() );
}

QString
CreatePartitionTableJob::prettyDescription() const
{
    return tr( "Create new <strong>%1</strong> partition table on <strong>%2</strong> (%3)." )
        .arg( PartitionTable::tableTypeToName( m_type ).toUpper() )
        .arg( m_device->deviceNode() )
        .arg( m_device->name() );
}


QString
CreatePartitionTableJob::prettyStatusMessage() const
{
    return tr( "Creating new %1 partition table on %2." )
        .arg( PartitionTable::tableTypeToName( m_type ).toUpper() )
        .arg( m_device->deviceNode() );
}


Calamares::JobResult
CreatePartitionTableJob::exec()
{
    Report report( nullptr );
    QString message = tr( "The installer failed to create a partition table on %1." ).arg( m_device->name() );

    PartitionTable* table = m_device->partitionTable();

    if ( Logger::logLevelEnabled( Logger::LOGDEBUG ) )
    {
        cDebug() << "Creating new partition table of type" << table->typeName() << ", uncommitted partitions:";
        for ( auto it = PartitionIterator::begin( table ); it != PartitionIterator::end( table ); ++it )
        {
            cDebug() << Logger::SubEntry << ( ( *it ) ? ( *it )->deviceNode() : QString( "<null device>" ) );
        }

        QProcess lsblk;
        lsblk.setProgram( "lsblk" );
        lsblk.setProcessChannelMode( QProcess::MergedChannels );
        lsblk.start();
        lsblk.waitForFinished();
        cDebug() << Logger::SubEntry << "lsblk output:\n" << Logger::NoQuote << lsblk.readAllStandardOutput();

        QProcess mount;
        mount.setProgram( "mount" );  // Debug output only, not mounting something
        mount.setProcessChannelMode( QProcess::MergedChannels );
        mount.start();
        mount.waitForFinished();
        cDebug() << Logger::SubEntry << "mount output:\n" << Logger::NoQuote << mount.readAllStandardOutput();
    }

    CreatePartitionTableOperation op( *m_device, table );
    op.setStatus( Operation::StatusRunning );

    if ( op.execute( report ) )
    {
        return Calamares::JobResult::ok();
    }

    return Calamares::JobResult::error( message, report.toText() );
}

void
CreatePartitionTableJob::updatePreview()
{
    // Device takes ownership of its table, but does not destroy the current
    // one when setPartitionTable() is called, so do it ourself
    delete m_device->partitionTable();
    m_device->setPartitionTable( createTable() );
    m_device->partitionTable()->updateUnallocated( *m_device );
}

PartitionTable*
CreatePartitionTableJob::createTable()
{
    cDebug() << "CreatePartitionTableJob::createTable trying to make table for device" << m_device->deviceNode();
    return new PartitionTable( m_type,
                               PartitionTable::defaultFirstUsable( *m_device, m_type ),
                               PartitionTable::defaultLastUsable( *m_device, m_type ) );
}
