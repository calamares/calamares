/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Kevin Kofler <kevin.kofler@chello.at>
 *   Copyright 2016, Philip Müller <philm@manjaro.org>
 *   Copyright 2017, Alf Gaida <agaida@siduction.org>
 *   Copyright 2019, Adriaan de Groot <groot@kde.org>
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

#include "MachineIdJob.h"

#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"
#include "utils/Variant.h"

#include "GlobalStorage.h"
#include "JobQueue.h"

#include <QFile>

MachineIdJob::MachineIdJob( QObject* parent )
    : Calamares::CppJob( parent )
{
}


MachineIdJob::~MachineIdJob() {}


QString
MachineIdJob::prettyName() const
{
    return tr( "Generate machine-id." );
}

// might need to use a helper to remove the file
static void
removeFile( const QString& rootMountPoint, const QString& fileName )
{
    QFile::remove( rootMountPoint + fileName );
}

/// @brief Copy @p fileName from host into target system at @p rootMountPoint
static Calamares::JobResult
copyFile( const QString& rootMountPoint, const QString& fileName )
{
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

/// @brief How to generate entropy (bool-like)
enum class EntropyGeneration
{
    New,
    CopyFromHost
};

/// @brief How to create the DBus machine-id (bool-like)
enum class DBusGeneration
{
    New,
    SymlinkFromSystemD
};

static int
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
            bool ok = false;
            poolSize = v.toInt( &ok );
            if ( !ok )
            {
                poolSize = minimumPoolSize;
            }
        }
    }
    return poolSize >= minimumPoolSize ? poolSize : minimumPoolSize;
}

static Calamares::JobResult
createNewEntropy( int poolSize, const QString& rootMountPoint, const QString& fileName )
{
    QFile urandom( "/dev/urandom" );
    if ( urandom.exists() && urandom.open( QIODevice::ReadOnly ) )
    {
        QByteArray data = urandom.read( poolSize );
        urandom.close();

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
    }
    return Calamares::JobResult::error(
        QObject::tr( "File not found" ),
        QObject::tr( "Could not read random file <pre>%1</pre>." ).arg( QStringLiteral( "/dev/urandom" ) ) );
}


static Calamares::JobResult
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
createSystemdMachineId( const QString& rootMountPoint, const QString& fileName )
{
    return Calamares::JobResult::internalError( QObject::tr( "Internal Error" ), QObject::tr( "Not implemented" ), 0 );
}

static Calamares::JobResult
createDBusMachineId( DBusGeneration kind, const QString& rootMountPoint, const QString& fileName )
{
    return Calamares::JobResult::internalError( QObject::tr( "Internal Error" ), QObject::tr( "Not implemented" ), 0 );
}

Calamares::JobResult
MachineIdJob::exec()
{
    QString root;

    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
    if ( gs && gs->contains( "rootMountPoint" ) )
    {
        root = gs->value( "rootMountPoint" ).toString();
    }
    else
    {
        cWarning() << "No *rootMountPoint* defined.";
        return Calamares::JobResult::internalError( tr( "Configuration Error" ),
                                                    tr( "No root mount point is set for MachineId." ),
                                                    Calamares::JobResult::InvalidConfiguration );
    }

    QString target_systemd_machineid_file = QStringLiteral( "/etc/machine-id" );
    QString target_dbus_machineid_file = QStringLiteral( "/var/lib/dbus/machine-id" );
    QString target_entropy_file = QStringLiteral( "/var/lib/urandom/random-seed" );

    // Clear existing files
    if ( m_entropy )
    {
        removeFile( root, target_entropy_file );
    }
    if ( m_dbus )
    {
        removeFile( root, target_dbus_machineid_file );
    }
    if ( m_systemd )
    {
        removeFile( root, target_systemd_machineid_file );
    }

    //Create new files
    if ( m_entropy )
    {
        auto r = createEntropy(
            m_entropy_copy ? EntropyGeneration::CopyFromHost : EntropyGeneration::New, root, target_entropy_file );
        if ( !r )
        {
            return r;
        }
    }
    if ( m_systemd )
    {
        auto r = createSystemdMachineId( root, target_systemd_machineid_file );
        if ( !r )
        {
            return r;
        }
    }
    if ( m_dbus )
    {
        auto r = createDBusMachineId( m_dbus_symlink ? DBusGeneration::SymlinkFromSystemD : DBusGeneration::New,
                                      root,
                                      target_dbus_machineid_file );
        if ( !r )
        {
            return r;
        }
    }

    return Calamares::JobResult::ok();
}


void
MachineIdJob::setConfigurationMap( const QVariantMap& map )
{
    m_systemd = CalamaresUtils::getBool( map, "systemd", false );

    m_dbus = CalamaresUtils::getBool( map, "dbus", false );
    if ( map.contains( "dbus-symlink" ) )
    {
        m_dbus_symlink = CalamaresUtils::getBool( map, "dbus-symlink", false );
    }
    else if ( map.contains( "symlink" ) )
    {
        m_dbus_symlink = CalamaresUtils::getBool( map, "symlink", false );
        cWarning() << "MachineId: configuration setting *symlink* is deprecated, use *dbus-symlink*.";
    }
    // else it's still false from the constructor

    // ignore it, though, if dbus is false
    m_dbus_symlink = m_dbus && m_dbus_symlink;

    m_entropy = CalamaresUtils::getBool( map, "entropy", false );
    m_entropy_copy = CalamaresUtils::getBool( map, "entropy-copy", false );
}

CALAMARES_PLUGIN_FACTORY_DEFINITION( MachineIdJobFactory, registerPlugin< MachineIdJob >(); )
