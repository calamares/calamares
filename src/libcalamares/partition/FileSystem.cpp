/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2015-2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018-2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
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
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wswitch-enum"
#endif
    // 13 enumeration values not handled
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
#ifdef __clang__
#pragma clang diagnostic pop
#endif
}

QString
untranslatedFS( FileSystem::Type t )
{
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wswitch-enum"
#endif
    // 34 enumeration values not handled
    switch ( t )
    {
    case FileSystem::Type::ReiserFS:
        return QStringLiteral( "reiserfs" );
    default:
        return FileSystem::nameForType( t, { QStringLiteral( "C" ) } );
    }
#ifdef __clang__
#pragma clang diagnostic pop
#endif
}

}  // namespace Partition
}  // namespace CalamaresUtils
