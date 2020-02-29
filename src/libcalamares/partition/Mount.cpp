/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017-2019, Adriaan de Groot <groot@kde.org>
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

#include "Mount.h"

#include "partition/Sync.h"
#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"

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
    : m_d( new Private )
{
    m_d->m_devicePath = devicePath;
    m_d->m_mountDir.setAutoRemove( false );
    int r = mount( devicePath, m_d->m_mountDir.path(), filesystemName, options );
    if ( r )
    {
        cWarning() << "Mount of" << devicePath << "on" << m_d->m_mountDir.path() << "failed, code" << r;
        delete m_d;
        m_d = nullptr;
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
        delete m_d;
        m_d = nullptr;
    }
}

QString
TemporaryMount::path() const
{
    return m_d ? m_d->m_mountDir.path() : QString();
}

}  // namespace Partition
}  // namespace CalamaresUtils
