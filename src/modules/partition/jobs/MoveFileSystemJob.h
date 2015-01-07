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
#ifndef MOVEFILESYSTEMJOB_H
#define MOVEFILESYSTEMJOB_H

#include <jobs/PartitionJob.h>

class CopySourceDevice;
class CopyTargetDevice;
class Device;
class Partition;
class Report;

/**
 * This job moves the data of a filesystem from one position on the disk to
 * another.
 *
 * It is used by the ResizePartitionJob.
 */
class MoveFileSystemJob : public PartitionJob
{
    Q_OBJECT
public:
    MoveFileSystemJob( Device* device, Partition* partition, qint64 oldFirstSector, qint64 newFirstSector, qint64 length );

    QString prettyName() const override;

    Calamares::JobResult exec() override;

private:
    Device* m_device;
    qint64 m_oldFirstSector;
    qint64 m_newFirstSector;
    qint64 m_length;
    bool copyBlocks( Report& report, CopyTargetDevice& target, CopySourceDevice& source );
    bool rollbackCopyBlocks( Report& report, CopyTargetDevice& origTarget, CopySourceDevice& origSource );
};

#endif /* MOVEFILESYSTEMJOB_H */
