/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2016, Teo Mrnjavac <teo@kde.org>
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

#include "PythonQtUtilsWrapper.h"

#include "utils/CalamaresUtilsSystem.h"
#include "utils/CalamaresUtils.h"
#include "utils/Logger.h"

#include <PythonQt.h>


Utils::Utils(QObject* parent)
    : QObject( parent )
    , m_exceptionCxt( PythonQt::self()->createUniqueModule() )
{
    PythonQt::self()->evalScript( m_exceptionCxt, "import subprocess" );
}


void
Utils::debug(const QString& s) const
{
    cDebug() << "PythonQt DBG>" << s;
}


int
Utils::mount( const QString& device_path,
              const QString& mount_point,
              const QString& filesystem_name,
              const QString& options ) const
{
    return CalamaresUtils::System::instance()->
            mount( device_path, mount_point, filesystem_name, options );
}


int
Utils::target_env_call( const QString& command,
                        const QString& stdin,
                        int timeout ) const
{
    return CalamaresUtils::System::instance()->
            targetEnvCall( command, QString(), stdin, timeout );
}


int
Utils::target_env_call( const QStringList& args,
                        const QString& stdin,
                        int timeout ) const
{
    return CalamaresUtils::System::instance()->
            targetEnvCall( args, QString(), stdin, timeout );
}


int
Utils::check_target_env_call( const QString& command,
                              const QString& stdin,
                              int timeout ) const
{
    int ec = target_env_call( command, stdin, timeout );
    return _handle_check_target_env_call_error( ec, command );
}


int
Utils::check_target_env_call( const QStringList& args,
                              const QString& stdin,
                              int timeout) const
{
    int ec = target_env_call( args, stdin, timeout );
    return _handle_check_target_env_call_error( ec, args.join( ' ' ) );
}


QString
Utils::check_target_env_output( const QString& command,
                                const QString& stdin,
                                int timeout ) const
{
    QString output;
    int ec = CalamaresUtils::System::instance()->
             targetEnvOutput( command,
                              output,
                              QString(),
                              stdin,
                              timeout );
    _handle_check_target_env_call_error( ec, command );
    return output;
}


QString
Utils::check_target_env_output( const QStringList& args,
                                const QString& stdin,
                                int timeout ) const
{
    QString output;
    int ec = CalamaresUtils::System::instance()->
             targetEnvOutput( args,
                              output,
                              QString(),
                              stdin,
                              timeout );
    _handle_check_target_env_call_error( ec, args.join( ' ' ) );
    return output;
}


QString
Utils::obscure( const QString& string ) const
{
    return CalamaresUtils::obscure( string );
}


int
Utils::_handle_check_target_env_call_error( int ec, const QString& cmd) const
{
    if ( ec )
    {
        QString raise = QString( "raise subprocess.CalledProcessError(%1,\"%2\")" )
                        .arg( ec )
                        .arg( cmd );
        PythonQt::self()->evalScript( m_exceptionCxt, raise );
    }
    return ec;
}
