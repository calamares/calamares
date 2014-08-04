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
#ifndef PMUTILS_H
#define PMUTILS_H

// CalaPM
#include <fs/filesystem.h>

// Qt
#include <QList>

class Device;
class Partition;
class PartitionNode;
class PartitionRole;

namespace PMUtils
{

bool isPartitionFreeSpace( Partition* );

bool isPartitionNew( Partition* );

Partition* findPartitionByMountPoint( const QList< Device* >& devices, const QString& mountPoint );

Partition* createNewPartition( PartitionNode* parent, const Device& device, const PartitionRole& role, FileSystem::Type fsType, qint64 firstSector, qint64 lastSector );

}

#endif /* PMUTILS_H */
