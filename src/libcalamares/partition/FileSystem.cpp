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

namespace Calamares
{
namespace Partition
{

QString
prettyNameForFileSystemType( FileSystem::Type t )
{
    QT_WARNING_PUSH
    QT_WARNING_DISABLE_CLANG( "-Wswitch-enum" )
    // 13 enumeration values not handled
    switch ( t )
    {
    case FileSystem::Unknown:
        return QObject::tr( "unknown", "@partition info" );
    case FileSystem::Extended:
        return QObject::tr( "extended", "@partition info" );
    case FileSystem::Unformatted:
        return QObject::tr( "unformatted", "@partition info" );
    case FileSystem::LinuxSwap:
        return QObject::tr( "swap", "@partition info" );
    case FileSystem::Fat16:
    case FileSystem::Fat32:
    case FileSystem::Ntfs:
    case FileSystem::Xfs:
    case FileSystem::Jfs:
    case FileSystem::Hfs:
    case FileSystem::Ufs:
    case FileSystem::Hpfs:
    case FileSystem::Luks:
    case FileSystem::Luks2:
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
    QT_WARNING_POP
}

QString
untranslatedFS( FileSystem::Type t )
{
    QT_WARNING_PUSH
    QT_WARNING_DISABLE_CLANG( "-Wswitch-enum" )
    // 34 enumeration values not handled
    switch ( t )
    {
    case FileSystem::Type::ReiserFS:
        return QStringLiteral( "reiserfs" );
    default:
        return FileSystem::nameForType( t, { QStringLiteral( "C" ) } );
    }
    QT_WARNING_POP
}

}  // namespace Partition
}  // namespace Calamares
