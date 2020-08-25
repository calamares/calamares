/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "PythonQtUtilsWrapper.h"

#include "partition/Mount.h"
#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"
#include "utils/String.h"

#include <PythonQt.h>


Utils::Utils( QObject* parent )
    : QObject( parent )
    , m_exceptionCxt( PythonQt::self()->createUniqueModule() )
{
    PythonQt::self()->evalScript( m_exceptionCxt, "import subprocess" );
}


void
Utils::debug( const QString& s ) const
{
    cDebug() << "PythonQt DBG>" << s;
}


int
Utils::mount( const QString& device_path,
              const QString& mount_point,
              const QString& filesystem_name,
              const QString& options ) const
{
    return CalamaresUtils::Partition::mount( device_path, mount_point, filesystem_name, options );
}


int
Utils::target_env_call( const QString& command, const QString& stdin, int timeout ) const
{
    return CalamaresUtils::System::instance()->targetEnvCall(
        command, QString(), stdin, std::chrono::seconds( timeout > 0 ? timeout : 0 ) );
}


int
Utils::target_env_call( const QStringList& args, const QString& stdin, int timeout ) const
{
    return CalamaresUtils::System::instance()->targetEnvCall(
        args, QString(), stdin, std::chrono::seconds( timeout > 0 ? timeout : 0 ) );
}


int
Utils::check_target_env_call( const QString& command, const QString& stdin, int timeout ) const
{
    int ec = target_env_call( command, stdin, timeout );
    return _handle_check_target_env_call_error( ec, command );
}


int
Utils::check_target_env_call( const QStringList& args, const QString& stdin, int timeout ) const
{
    int ec = target_env_call( args, stdin, timeout );
    return _handle_check_target_env_call_error( ec, args.join( ' ' ) );
}


QString
Utils::check_target_env_output( const QString& command, const QString& stdin, int timeout ) const
{
    QString output;
    int ec = CalamaresUtils::System::instance()->targetEnvOutput(
        command, output, QString(), stdin, std::chrono::seconds( timeout > 0 ? timeout : 0 ) );
    _handle_check_target_env_call_error( ec, command );
    return output;
}


QString
Utils::check_target_env_output( const QStringList& args, const QString& stdin, int timeout ) const
{
    QString output;
    int ec = CalamaresUtils::System::instance()->targetEnvOutput(
        args, output, QString(), stdin, std::chrono::seconds( timeout > 0 ? timeout : 0 ) );
    _handle_check_target_env_call_error( ec, args.join( ' ' ) );
    return output;
}


QString
Utils::obscure( const QString& string ) const
{
    return CalamaresUtils::obscure( string );
}


int
Utils::_handle_check_target_env_call_error( int ec, const QString& cmd ) const
{
    if ( ec )
    {
        QString raise = QString( "raise subprocess.CalledProcessError(%1,\"%2\")" ).arg( ec ).arg( cmd );
        PythonQt::self()->evalScript( m_exceptionCxt, raise );
    }
    return ec;
}
