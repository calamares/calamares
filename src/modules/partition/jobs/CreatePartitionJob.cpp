/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 2020, Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "CreatePartitionJob.h"

#include "partition/FileSystem.h"
#include "partition/PartitionQuery.h"
#include "utils/Logger.h"
#include "utils/Units.h"

#include <kpmcore/core/device.h>
#include <kpmcore/core/lvmdevice.h>
#include <kpmcore/core/partition.h>
#include <kpmcore/core/partitiontable.h>
#include <kpmcore/fs/filesystem.h>
#include <kpmcore/ops/newoperation.h>
#include <kpmcore/util/report.h>

using CalamaresUtils::Partition::untranslatedFS;
using CalamaresUtils::Partition::userVisibleFS;

CreatePartitionJob::CreatePartitionJob( Device* device, Partition* partition )
    : PartitionJob( partition )
    , m_device( device )
{
}

static const QMap < QString, QString > gptTypePrettyStrings = {
    { "44479540-f297-41b2-9af7-d131d5f0458a", "Root Partition (x86)" },
    { "4f68bce3-e8cd-4db1-96e7-fbcaf984b709", "Root Partition (x86-64)" },
    { "69dad710-2ce4-4e3c-b16c-21a1d49abed3", "Root Partition (32-bit ARM)" },
    { "b921b045-1df0-41c3-af44-4c6f280d3fae", "Root Partition (64-bit ARM)" },
    { "993d8d3d-f80e-4225-855a-9daf8ed7ea97", "Root Partition (Itanium/IA-64)" },
    { "d13c5d3b-b5d1-422a-b29f-9454fdc89d76", "Root Verity Partition (x86)" },
    { "2c7357ed-ebd2-46d9-aec1-23d437ec2bf5", "Root Verity Partition (x86-64)" },
    { "7386cdf2-203c-47a9-a498-f2ecce45a2d6", "Root Verity Partition (32-bit ARM)" },
    { "df3300ce-d69f-4c92-978c-9bfb0f38d820", "Root Verity Partition (64-bit ARM/AArch64)" },
    { "86ed10d5-b607-45bb-8957-d350f23d0571", "Root Verity Partition (Itanium/IA-64)" },
    { "75250d76-8cc6-458e-bd66-bd47cc81a812", "/usr Partition (x86)" },
    { "8484680c-9521-48c6-9c11-b0720656f69e", "/usr Partition (x86-64)" },
    { "7d0359a3-02b3-4f0a-865c-654403e70625", "/usr Partition (32-bit ARM)" },
    { "b0e01050-ee5f-4390-949a-9101b17104e9", "/usr Partition (64-bit ARM/AArch64)" },
    { "4301d2a6-4e3b-4b2a-bb94-9e0b2c4225ea", "/usr Partition (Itanium/IA-64)" },
    { "8f461b0d-14ee-4e81-9aa9-049b6fb97abd", "/usr Verity Partition (x86)" },
    { "77ff5f63-e7b6-4633-acf4-1565b864c0e6", "/usr Verity Partition (x86-64)" },
    { "c215d751-7bcd-4649-be90-6627490a4c05", "/usr Verity Partition (32-bit ARM)" },
    { "6e11a4e7-fbca-4ded-b9e9-e1a512bb664e", "/usr Verity Partition (64-bit ARM/AArch64)" },
    { "6a491e03-3be7-4545-8e38-83320e0ea880", "/usr Verity Partition (Itanium/IA-64)" },
    { "933ac7e1-2eb4-4f13-b844-0e14e2aef915", "Home Partition" },
    { "3b8f8425-20e0-4f3b-907f-1a25a76f98e8", "Server Data Partition" },
    { "4d21b016-b534-45c2-a9fb-5c16e091fd2d", "Variable Data Partition" },
    { "7ec6f557-3bc5-4aca-b293-16ef5df639d1", "Temporary Data Partition" },
    { "0657fd6d-a4ab-43c4-84e5-0933c84b4f4f", "Swap" },
    { "c12a7328-f81f-11d2-ba4b-00a0c93ec93b", "EFI System Partition" },
    { "bc13c2ff-59e6-4262-a352-b275fd6f7172", "Extended Boot Loader Partition" },
    { "0fc63daf-8483-4772-8e79-3d69d8477de4", "Other Data Partitions" },
    { "ebd0a0a2-b9e5-4433-87c0-68b6b72699c7", "Microsoft basic data" },
};

static QString
prettyGptType( const QString& type )
{
    return gptTypePrettyStrings.value( type.toLower(), type );
}

static QString
prettyGptAttributes( quint64 attributes )
{
    QStringList list;

    if ( attributes & ( 1UL << 0 ) )
    {
        list += QString( "RequiredPartition" );
    }

    if ( attributes & ( 1UL << 1 ) )
    {
        list += QString( "NoBlockIOProtocol" );
    }

    if ( attributes & ( 1UL << 2 ) )
    {
        list += QString( "LegacyBIOSBootable" );
    }

    for ( qint8 bit = 3; bit < 64; bit++ )
    {
        if ( attributes & ( 1UL << bit ) )
        {
            list += QString( "Bit" ) + QString::number( bit );
        }
    }

    QString string = list.join( QStringLiteral( " and " ) );
    if ( string.size() > 64 )   
    {
        return QString( "0x" ) + QString::number( attributes, 0x10 );
    }

    return string;
}

static QString
prettyGptEntries( const Partition* partition )
{
    if ( !partition )
    {
        return QString("");
    }

    QStringList list;

    if ( partition->label().size() )
    {
        list += partition->label();
    }

    if ( partition->uuid().size() )
    {
        list += partition->uuid();
    }

    QString type = prettyGptType( partition->type() );
    if ( type.size() )
    {
        list += type;
    }

    QString attributes = prettyGptAttributes( partition->attributes() );
    if ( attributes.size() && attributes != QString( "0" ) )
    {
        list += attributes;
    }

    return list.join( QStringLiteral( ", " ) );
}

QString
CreatePartitionJob::prettyName() const
{
    if ( CalamaresUtils::Partition::getPartitionTable( m_partition )->type() == PartitionTable::TableType::gpt )
    {
        QString entries = prettyGptEntries( m_partition );
        if ( entries.size() )
        {
             entries = QString( " with entries " ) + entries;
        }

        return tr( "Create new %1MiB partition on %3 (%2)%4." )
                   .arg( CalamaresUtils::BytesToMiB( m_partition->capacity() ) )
                   .arg( m_device->name() )
                   .arg( m_device->deviceNode() )
                   .arg( prettyGptEntries( m_partition ) );
    }

    return tr( "Create new %2MiB partition on %4 (%3) with file system %1." )
        .arg( userVisibleFS( m_partition->fileSystem() ) )
        .arg( CalamaresUtils::BytesToMiB( m_partition->capacity() ) )
        .arg( m_device->name() )
        .arg( m_device->deviceNode() );
}


QString
CreatePartitionJob::prettyDescription() const
{
    if ( CalamaresUtils::Partition::getPartitionTable( m_partition )->type() == PartitionTable::TableType::gpt )
    {
        QString entries = prettyGptEntries( m_partition );
        if ( entries.size() )
        {
             entries = QString( " with entries <em>" ) + entries + QString( "</em>" );
        }

        return tr( "Create new <strong>%1MiB</strong> partition on <strong>%3</strong> (%2)%4." )
                   .arg( CalamaresUtils::BytesToMiB( m_partition->capacity() ) )
                   .arg( m_device->name() )
                   .arg( m_device->deviceNode() )
                   .arg( entries );
    }

    return tr( "Create new <strong>%2MiB</strong> partition on <strong>%4</strong> "
               "(%3) with file system <strong>%1</strong>." )
        .arg( userVisibleFS( m_partition->fileSystem() ) )
        .arg( CalamaresUtils::BytesToMiB( m_partition->capacity() ) )
        .arg( m_device->name() )
        .arg( m_device->deviceNode() );
}


QString
CreatePartitionJob::prettyStatusMessage() const
{
    if ( CalamaresUtils::Partition::getPartitionTable( m_partition )->type() == PartitionTable::TableType::gpt )
    {
        QString type = prettyGptType( m_partition->type() );
        if ( !type.size() )
        {
            type = m_partition->label();
        }
        if ( !type.size() )
        {
            type = userVisibleFS( m_partition->fileSystem() );
        }

        return tr( "Creating new %1 partition on %2." )
                   .arg( type )
                   .arg( m_device->deviceNode() );
    }

    return tr( "Creating new %1 partition on %2." )
        .arg( userVisibleFS( m_partition->fileSystem() ) )
        .arg( m_device->deviceNode() );
}

Calamares::JobResult
CreatePartitionJob::exec()
{
    Report report( nullptr );
    NewOperation op( *m_device, m_partition );
    op.setStatus( Operation::StatusRunning );

    QString message = tr( "The installer failed to create partition on disk '%1'." ).arg( m_device->name() );
    if ( op.execute( report ) )
    {
        return Calamares::JobResult::ok();
    }

    return Calamares::JobResult::error( message, report.toText() );
}

void
CreatePartitionJob::updatePreview()
{
    m_device->partitionTable()->removeUnallocated();
    m_partition->parent()->insert( m_partition );
    m_device->partitionTable()->updateUnallocated( *m_device );
}
