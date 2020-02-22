/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014,      Aurélien Gâteau <agateau@kde.org>
 *   Copyright 2015-2016, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2018-2019 Adriaan de Groot <groot@kde.org>
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

#include "FileSystem.h"

#include <QObject>

namespace CalamaresUtils
{
namespace Partition
{

QString
prettyNameForFileSystemType( FileSystem::Type t )
{
    switch ( t )
    {
    case FileSystem::Unknown:
        return QObject::tr( "unknown" );
    case FileSystem::Extended:
        return QObject::tr( "extended" );
    case FileSystem::Unformatted:
        return QObject::tr( "unformatted" );
    case FileSystem::LinuxSwap:
        return QObject::tr( "swap" );
    case FileSystem::Fat16:
    case FileSystem::Fat32:
    case FileSystem::Ntfs:
    case FileSystem::Xfs:
    case FileSystem::Jfs:
    case FileSystem::Hfs:
    case FileSystem::Ufs:
    case FileSystem::Hpfs:
    case FileSystem::Luks:
    case FileSystem::Ocfs2:
    case FileSystem::Zfs:
    case FileSystem::Nilfs2:
        return FileSystem::nameForType( t ).toUpper();
    case FileSystem::ReiserFS:
        return "ReiserFS";
    case FileSystem::Reiser4:
        return "Reiser4";
    case FileSystem::HfsPlus:
        return "HFS+";
    case FileSystem::Btrfs:
        return "Btrfs";
    case FileSystem::Exfat:
        return "exFAT";
    case FileSystem::Lvm2_PV:
        return "LVM PV";
    default:
        return FileSystem::nameForType( t );
    }
}

}  // namespace Partition
}  // namespace CalamaresUtils
