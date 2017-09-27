/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
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

// This class is heavily based on the MoveFileSystemJob class from KDE Partition
// Manager.
// The copyBlock functions come from Partition Manager Job class.
// Original copyright follow:

/***************************************************************************
 *   Copyright (C) 2008 by Volker Lanz <vl@fidra.de>                       *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA            *
 ***************************************************************************/

#include <jobs/MoveFileSystemJob.h>

#include <utils/Logger.h>

// KPMcore
#include <kpmcore/core/copysourcedevice.h>
#include <kpmcore/core/copytargetdevice.h>
#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>
#include <kpmcore/fs/filesystem.h>
#include <kpmcore/util/report.h>

MoveFileSystemJob::MoveFileSystemJob( Device* device, Partition* partition, qint64 oldFirstSector, qint64 newFirstSector, qint64 length )
    : PartitionJob( partition )
    , m_device( device )
    , m_oldFirstSector( oldFirstSector )
    , m_newFirstSector( newFirstSector )
    , m_length( length )
{}

QString
MoveFileSystemJob::prettyName() const
{
    return tr( "Move file system of partition %1." ).arg( partition()->partitionPath() );
}

Calamares::JobResult
MoveFileSystemJob::exec()
{
    Report report( nullptr );
    QString partitionPath = partition()->partitionPath();
    CopySourceDevice moveSource( *m_device, m_oldFirstSector, m_oldFirstSector + m_length - 1 );
    CopyTargetDevice moveTarget( *m_device, m_newFirstSector, m_newFirstSector + m_length - 1 );

    if ( !moveSource.open() )
        return Calamares::JobResult::error(
                   QString(),
                   tr( "Could not open file system on partition %1 for moving." ).arg( partitionPath )
               );

    if ( !moveTarget.open() )
        return Calamares::JobResult::error(
                   QString(),
                   tr( "Could not create target for moving file system on partition %1." ).arg( partitionPath )
               );

    bool ok = copyBlocks( report, moveTarget, moveSource );
    if ( !ok )
    {
        if ( rollbackCopyBlocks( report, moveTarget, moveSource ) )
            return Calamares::JobResult::error(
                       QString(),
                       tr( "Moving of partition %1 failed, changes have been rolled back." ).arg( partitionPath )
                       + '\n' + report.toText()
                   );
        else
            return Calamares::JobResult::error(
                       QString(),
                       tr( "Moving of partition %1 failed. Roll back of the changes have failed." ).arg( partitionPath )
                       + '\n' + report.toText()
                   );
    }

    FileSystem& fs = partition()->fileSystem();
    fs.setFirstSector( m_newFirstSector );
    fs.setLastSector( m_newFirstSector + m_length - 1 );

    if ( !fs.updateBootSector( report, partitionPath ) )
        return Calamares::JobResult::error(
                   QString(),
                   tr( "Updating boot sector after the moving of partition %1 failed." ).arg( partitionPath )
                   + '\n' + report.toText()
               );

    return Calamares::JobResult::ok();
}

bool
MoveFileSystemJob::copyBlocks( Report& report, CopyTargetDevice& target, CopySourceDevice& source )
{
    /** @todo copyBlocks() assumes that source.sectorSize() == target.sectorSize(). */

    if ( source.sectorSize() != target.sectorSize() )
    {
        report.line() << tr( "The logical sector sizes in the source and target for copying are not the same. This is currently unsupported." );
        return false;
    }

    bool rval = true;
    const qint64 blockSize = 16065 * 8; // number of sectors per block to copy
    const qint64 blocksToCopy = source.length() / blockSize;

    qint64 readOffset = source.firstSector();
    qint64 writeOffset = target.firstSector();
    qint32 copyDir = 1;

    if ( target.firstSector() > source.firstSector() )
    {
        readOffset = source.firstSector() + source.length() - blockSize;
        writeOffset = target.firstSector() + source.length() - blockSize;
        copyDir = -1;
    }

    qint64 blocksCopied = 0;

    Q_ASSERT( blockSize > 0 );
    Q_ASSERT( source.sectorSize() > 0 );
    Q_ASSERT( blockSize * source.sectorSize() > 0 );

    void* buffer = malloc( size_t( blockSize * source.sectorSize() ) );
    qint64 percent = 0;

    while ( blocksCopied < blocksToCopy )
    {
        rval = source.readSectors( buffer, readOffset + blockSize * blocksCopied * copyDir, blockSize );
        if ( !rval )
            break;

        rval = target.writeSectors( buffer, writeOffset + blockSize * blocksCopied * copyDir, blockSize );
        if ( !rval )
            break;

        if ( ++blocksCopied * 100 / blocksToCopy != percent )
        {
            percent = blocksCopied * 100 / blocksToCopy;
            progress( percent / 100. );
        }
    }

    const qint64 lastBlock = source.length() % blockSize;

    // copy the remainder
    if ( rval && lastBlock > 0 )
    {
        Q_ASSERT( lastBlock < blockSize );

        const qint64 lastBlockReadOffset = copyDir > 0 ? readOffset + blockSize * blocksCopied : source.firstSector();
        const qint64 lastBlockWriteOffset = copyDir > 0 ? writeOffset + blockSize * blocksCopied : target.firstSector();

        rval = source.readSectors( buffer, lastBlockReadOffset, lastBlock );

        if ( rval )
            rval = target.writeSectors( buffer, lastBlockWriteOffset, lastBlock );

        if ( rval )
            emit progress( 1.0 );
    }

    free( buffer );

    return rval;
}

bool
MoveFileSystemJob::rollbackCopyBlocks( Report& report, CopyTargetDevice& origTarget, CopySourceDevice& origSource )
{
    if ( !origSource.overlaps( origTarget ) )
    {
        report.line() << tr( "Source and target for copying do not overlap: Rollback is not required." );
        return true;
    }

    // default: use values as if we were copying from front to back.
    qint64 undoSourceFirstSector = origTarget.firstSector();
    qint64 undoSourceLastSector = origTarget.firstSector() + origTarget.sectorsWritten() - 1;

    qint64 undoTargetFirstSector = origSource.firstSector();
    qint64 undoTargetLastSector = origSource.firstSector() + origTarget.sectorsWritten() - 1;

    if ( origTarget.firstSector() > origSource.firstSector() )
    {
        // we were copying from back to front
        undoSourceFirstSector = origTarget.firstSector() + origSource.length() - origTarget.sectorsWritten();
        undoSourceLastSector = origTarget.firstSector() + origSource.length() - 1;

        undoTargetFirstSector = origSource.lastSector() - origTarget.sectorsWritten() + 1;
        undoTargetLastSector = origSource.lastSector();
    }

    CopySourceDevice undoSource( origTarget.device(), undoSourceFirstSector, undoSourceLastSector );
    if ( !undoSource.open() )
    {
        report.line() << tr( "Could not open device %1 to rollback copying." )
                      .arg( origTarget.device().deviceNode() );
        return false;
    }

    CopyTargetDevice undoTarget( origSource.device(), undoTargetFirstSector, undoTargetLastSector );
    if ( !undoTarget.open() )
    {
        report.line() << tr( "Could not open device %1 to rollback copying." )
                      .arg( origSource.device().deviceNode() );
        return false;
    }

    return copyBlocks( report, undoTarget, undoSource );
}
