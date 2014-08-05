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
// Manager. Original copyright follow:

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

#include <MoveFileSystemJob.h>

// CalaPM
#include <core/copysourcedevice.h>
#include <core/copytargetdevice.h>
#include <core/device.h>
#include <core/partition.h>
#include <fs/filesystem.h>
#include <util/report.h>

static bool
copyBlocks( Report& report, CopyTargetDevice& target, CopySourceDevice& source )
{
    return false;
}

static bool
rollbackCopyBlocks( Report& report, CopyTargetDevice& target, CopySourceDevice& source )
{
    return false;
}

MoveFileSystemJob::MoveFileSystemJob( Device* device, Partition* partition, qint64 firstSector )
    : PartitionJob( partition )
    , m_device( device )
    , m_firstSector( firstSector )
{}

QString
MoveFileSystemJob::prettyName() const
{
    return tr( "Moving file system of partition %1." ).arg( partition()->partitionPath() );
}

Calamares::JobResult
MoveFileSystemJob::exec()
{
    Report report( nullptr );
    QString partitionPath = partition()->partitionPath();
    FileSystem& fs = partition()->fileSystem();
    CopySourceDevice moveSource( *m_device, fs.firstSector(), fs.lastSector() );
    CopyTargetDevice moveTarget( *m_device, m_firstSector, m_firstSector + fs.length() );

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

    const qint64 savedLength = fs.length();
    fs.setFirstSector( m_firstSector );
    fs.setLastSector( m_firstSector + savedLength - 1 );

    if ( !fs.updateBootSector( report, partitionPath ) )
        return Calamares::JobResult::error(
            QString(),
            tr( "Updating boot sector after the moving of partition %1 failed." ).arg( partitionPath )
            + '\n' + report.toText()
            );

    return Calamares::JobResult::ok();
}
