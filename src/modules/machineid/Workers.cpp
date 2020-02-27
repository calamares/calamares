/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Kevin Kofler <kevin.kofler@chello.at>
 *   Copyright 2016, Philip Müller <philm@manjaro.org>
 *   Copyright 2017, Alf Gaida <agaida@siduction.org>
 *   Copyright 2019-2020, Adriaan de Groot <groot@kde.org>
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

#include "Workers.h"

#include "utils/CalamaresUtilsSystem.h"
#include "utils/Entropy.h"
#include "utils/Logger.h"

#include <QFile>

namespace MachineId
{

static inline bool
isAbsolutePath( const QString& fileName )
{
    return fileName.startsWith( '/' );
}

// might need to use a helper to remove the file
void
removeFile( const QString& rootMountPoint, const QString& fileName )
{
    if ( isAbsolutePath( fileName ) )
    {
        QFile::remove( rootMountPoint + fileName );
    }
    // Otherwise, do nothing
}

Calamares::JobResult
copyFile( const QString& rootMountPoint, const QString& fileName )
{
    if ( !isAbsolutePath( fileName ) )
    {
        return Calamares::JobResult::internalError(
            QObject::tr( "File not found" ),
            QObject::tr( "Path <pre>%1</pre> must be an absolute path." ).arg( fileName ),
            0 );
    }

    QFile f( fileName );
    if ( !f.exists() )
    {
        return Calamares::JobResult::error( QObject::tr( "File not found" ), fileName );
    }
    if ( !f.copy( rootMountPoint + fileName ) )
    {
        return Calamares::JobResult::error( QObject::tr( "File not found" ), rootMountPoint + fileName );
    }
    return Calamares::JobResult::ok();
}

int
getUrandomPoolSize()
{
    QFile f( "/proc/sys/kernel/random/poolsize" );
    constexpr const int minimumPoolSize = 512;
    int poolSize = minimumPoolSize;

    if ( f.exists() && f.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        QByteArray v = f.read( 16 );
        if ( v.length() > 2 )
        {
            if ( v.endsWith( '\n' ) )
            {
                v.chop( 1 );
            }
            bool ok = false;
            poolSize = v.toInt( &ok );
            if ( !ok )
            {
                poolSize = minimumPoolSize;
            }
        }
    }
    return ( poolSize >= minimumPoolSize ) ? poolSize : minimumPoolSize;
}

Calamares::JobResult
createNewEntropy( int poolSize, const QString& rootMountPoint, const QString& fileName )
{
    QFile entropyFile( rootMountPoint + fileName );
    if ( entropyFile.exists() )
    {
        cWarning() << "Entropy file" << ( rootMountPoint + fileName ) << "already exists.";
        return Calamares::JobResult::ok();  // .. anyway
    }
    if ( !entropyFile.open( QIODevice::WriteOnly ) )
    {
        return Calamares::JobResult::error(
            QObject::tr( "File not found" ),
            QObject::tr( "Could not create new random file <pre>%1</pre>." ).arg( fileName ) );
    }

    QByteArray data;
    CalamaresUtils::EntropySource source = CalamaresUtils::getEntropy( poolSize, data );
    entropyFile.write( data );
    entropyFile.close();
    if ( entropyFile.size() < data.length() )
    {
        cWarning() << "Entropy file is" << entropyFile.size() << "bytes, random data was" << data.length();
    }
    if ( data.length() < poolSize )
    {
        cWarning() << "Entropy data is" << data.length() << "bytes, rather than poolSize" << poolSize;
    }
    if ( source != CalamaresUtils::EntropySource::URandom )
    {
        cWarning() << "Entropy data for pool is low-quality.";
    }
    return Calamares::JobResult::ok();
}


Calamares::JobResult
createEntropy( const EntropyGeneration kind, const QString& rootMountPoint, const QString& fileName )
{
    if ( kind == EntropyGeneration::CopyFromHost )
    {
        if ( QFile::exists( fileName ) )
        {
            auto r = copyFile( rootMountPoint, fileName );
            if ( r )
            {
                return r;
            }
            else
            {
                cWarning() << "Could not copy" << fileName << "for entropy, generating new.";
            }
        }
        else
        {
            cWarning() << "Host system entropy does not exist at" << fileName;
        }
    }

    int poolSize = getUrandomPoolSize();
    return createNewEntropy( poolSize, rootMountPoint, fileName );
}

static Calamares::JobResult
runCmd( const QStringList& cmd )
{
    auto r = CalamaresUtils::System::instance()->targetEnvCommand( cmd );
    if ( r.getExitCode() )
    {
        return r.explainProcess( cmd, std::chrono::seconds( 0 ) );
    }

    return Calamares::JobResult::ok();
}

Calamares::JobResult
createSystemdMachineId( const QString& rootMountPoint, const QString& fileName )
{
    Q_UNUSED( rootMountPoint )
    Q_UNUSED( fileName )
    return runCmd( QStringList { QStringLiteral( "systemd-machine-id-setup" ) } );
}

Calamares::JobResult
createDBusMachineId( const QString& rootMountPoint, const QString& fileName )
{
    Q_UNUSED( rootMountPoint )
    Q_UNUSED( fileName )
    return runCmd( QStringList { QStringLiteral( "dbus-uuidgen" ), QStringLiteral( "--ensure" ) } );
}

Calamares::JobResult
createDBusLink( const QString& rootMountPoint, const QString& fileName, const QString& systemdFileName )
{
    Q_UNUSED( rootMountPoint )
    return runCmd( QStringList { QStringLiteral( "ln" ), QStringLiteral( "-s" ), systemdFileName, fileName } );
}

}  // namespace MachineId
