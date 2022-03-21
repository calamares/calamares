/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017-2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#include "Mount.h"

#include "partition/Sync.h"
#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"
#include "utils/String.h"

#include <QDir>
#include <QTemporaryDir>

namespace CalamaresUtils
{
namespace Partition
{

int
mount( const QString& devicePath, const QString& mountPoint, const QString& filesystemName, const QString& options )
{
    if ( devicePath.isEmpty() || mountPoint.isEmpty() )
    {
        if ( devicePath.isEmpty() )
        {
            cWarning() << "Can't mount an empty device.";
        }
        if ( mountPoint.isEmpty() )
        {
            cWarning() << "Can't mount on an empty mountpoint.";
        }

        return static_cast< int >( ProcessResult::Code::NoWorkingDirectory );
    }

    QDir mountPointDir( mountPoint );
    if ( !mountPointDir.exists() )
    {
        bool ok = mountPointDir.mkpath( mountPoint );
        if ( !ok )
        {
            cWarning() << "Could not create mountpoint" << mountPoint;
            return static_cast< int >( ProcessResult::Code::NoWorkingDirectory );
        }
    }

    QStringList args = { "mount" };

    if ( !filesystemName.isEmpty() )
    {
        args << "-t" << filesystemName;
    }
    if ( !options.isEmpty() )
    {
        if ( options.startsWith( '-' ) )
        {
            args << options;
        }
        else
        {
            args << "-o" << options;
        }
    }
    args << devicePath << mountPoint;

    auto r = CalamaresUtils::System::runCommand( args, std::chrono::seconds( 10 ) );
    sync();
    return r.getExitCode();
}

int
unmount( const QString& path, const QStringList& options )
{
    auto r
        = CalamaresUtils::System::runCommand( QStringList { "umount" } << options << path, std::chrono::seconds( 10 ) );
    sync();
    return r.getExitCode();
}

struct TemporaryMount::Private
{
    QString m_devicePath;
    QTemporaryDir m_mountDir;
};


TemporaryMount::TemporaryMount( const QString& devicePath, const QString& filesystemName, const QString& options )
    : m_d( std::make_unique< Private >() )
{
    m_d->m_devicePath = devicePath;
    m_d->m_mountDir.setAutoRemove( false );
    int r = mount( devicePath, m_d->m_mountDir.path(), filesystemName, options );
    if ( r )
    {
        cWarning() << "Mount of" << devicePath << "on" << m_d->m_mountDir.path() << "failed, code" << r;
        m_d.reset();
    }
}

TemporaryMount::~TemporaryMount()
{
    if ( m_d )
    {
        int r = unmount( m_d->m_mountDir.path(), { "-R" } );
        if ( r )
        {
            cWarning() << "UnMount of temporary" << m_d->m_devicePath << "on" << m_d->m_mountDir.path()
                       << "failed, code" << r;
        }
    }
}

QString
TemporaryMount::path() const
{
    return m_d ? m_d->m_mountDir.path() : QString();
}

QList< MtabInfo >
MtabInfo::fromMtabFilteredByPrefix( const QString& mountPrefix, const QString& mtabPath )
{
    QFile f( mtabPath.isEmpty() ? "/etc/mtab" : mtabPath );
    if ( !f.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        return {};
    }

    QList< MtabInfo > l;
    // After opening, atEnd() is already true (!?) so try reading at least once
    do
    {
        QString line = f.readLine();
        if ( line.isEmpty() || line.startsWith( '#' ) )
        {
            continue;
        }

        QStringList parts = line.split( ' ', SplitSkipEmptyParts );
        if ( parts.length() >= 3 && !parts[ 0 ].startsWith( '#' ) )
        {
            // Lines have format: <device> <mountpoint> <fstype> <options>..., so check
            // the mountpoint field. Everything starts with an empty string.
            if ( parts[ 1 ].startsWith( mountPrefix ) )
            {
                l.append( { parts[ 0 ], parts[ 1 ] } );
            }
        }
    } while ( !f.atEnd() );
    return l;
}

}  // namespace Partition
}  // namespace CalamaresUtils
