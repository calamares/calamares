/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017-2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "PythonJobApi.h"

#include "PythonHelper.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "locale/Global.h"
#include "python/Api.h"
#include "python/Variant.h"
#include "utils/Logger.h"
#include "utils/RAII.h"
#include "utils/Runner.h"
#include "utils/String.h"
#include "utils/System.h"
#include "utils/Yaml.h"

#include <QCoreApplication>
#include <QDir>
#include <QStandardPaths>

namespace bp = boost::python;

static int
handle_check_target_env_call_error( const Calamares::ProcessResult& ec, const QString& cmd )
{
    if ( !ec.first )
    {
        return ec.first;
    }

    QString raise = QString( "import subprocess\n"
                             "e = subprocess.CalledProcessError(%1,\"%2\")\n" )
                        .arg( ec.first )
                        .arg( cmd );
    if ( !ec.second.isEmpty() )
    {
        raise.append( QStringLiteral( "e.output = \"\"\"%1\"\"\"\n" ).arg( ec.second ) );
    }
    raise.append( "raise e" );
    bp::exec( raise.toStdString().c_str() );
    bp::throw_error_already_set();
    return ec.first;
}

static inline QStringList
bp_list_to_qstringlist( const bp::list& args )
{
    QStringList list;
    for ( int i = 0; i < bp::len( args ); ++i )
    {
        list.append( QString::fromStdString( bp::extract< std::string >( args[ i ] ) ) );
    }
    return list;
}

static inline Calamares::ProcessResult
target_env_command( const QStringList& args, const std::string& input, int timeout )
{
    // Since Python doesn't give us the type system for distinguishing
    // seconds from other integral types, massage to seconds here.
    return Calamares::System::instance()->targetEnvCommand(
        args, QString(), QString::fromStdString( input ), std::chrono::seconds( timeout ) );
}

namespace CalamaresPython
{

int
target_env_call( const std::string& command, const std::string& input, int timeout )
{
    return target_env_command( QStringList { QString::fromStdString( command ) }, input, timeout ).first;
}

int
target_env_call( const bp::list& args, const std::string& input, int timeout )
{
    return target_env_command( bp_list_to_qstringlist( args ), input, timeout ).first;
}

int
check_target_env_call( const std::string& command, const std::string& input, int timeout )
{
    auto ec = target_env_command( QStringList { QString::fromStdString( command ) }, input, timeout );
    return handle_check_target_env_call_error( ec, QString::fromStdString( command ) );
}

int
check_target_env_call( const bp::list& args, const std::string& input, int timeout )
{
    auto ec = target_env_command( bp_list_to_qstringlist( args ), input, timeout );
    if ( !ec.first )
    {
        return ec.first;
    }

    QStringList failedCmdList = bp_list_to_qstringlist( args );
    return handle_check_target_env_call_error( ec, failedCmdList.join( ' ' ) );
}

std::string
check_target_env_output( const std::string& command, const std::string& input, int timeout )
{
    auto ec = target_env_command( QStringList { QString::fromStdString( command ) }, input, timeout );
    handle_check_target_env_call_error( ec, QString::fromStdString( command ) );
    return ec.second.toStdString();
}

std::string
check_target_env_output( const bp::list& args, const std::string& input, int timeout )
{
    QStringList list = bp_list_to_qstringlist( args );
    auto ec = target_env_command( list, input, timeout );
    handle_check_target_env_call_error( ec, list.join( ' ' ) );
    return ec.second.toStdString();
}

PythonJobInterface::PythonJobInterface( Calamares::PythonJob* parent )
    : m_parent( parent )
{
    auto moduleDir = QDir( m_parent->m_workingPath );
    moduleName = moduleDir.dirName().toStdString();
    prettyName = m_parent->prettyName().toStdString();
    workingPath = m_parent->m_workingPath.toStdString();
    configuration = Calamares::Python::variantMapToPyDict( m_parent->m_configurationMap );
}

void
PythonJobInterface::setprogress( qreal progress )
{
    if ( progress >= 0.0 && progress <= 1.0 )
    {
        m_parent->emitProgress( progress );
    }
}

static inline int
_process_output( Calamares::Utils::RunLocation location,
                 const boost::python::list& args,
                 const boost::python::object& callback,
                 const std::string& input,
                 int timeout )
{
    Calamares::Utils::Runner r( bp_list_to_qstringlist( args ) );
    r.setLocation( location );
    if ( !callback.is_none() )
    {
        bp::extract< bp::list > x( callback );
        if ( x.check() )
        {
            QObject::connect( &r,
                              &decltype( r )::output,
                              [ cb = callback.attr( "append" ) ]( const QString& s ) { cb( s.toStdString() ); } );
        }
        else
        {
            QObject::connect(
                &r, &decltype( r )::output, [ &callback ]( const QString& s ) { callback( s.toStdString() ); } );
        }
        r.enableOutputProcessing();
    }
    if ( !input.empty() )
    {
        r.setInput( QString::fromStdString( input ) );
    }
    if ( timeout > 0 )
    {
        r.setTimeout( std::chrono::seconds( timeout ) );
    }

    auto result = r.run();

    if ( result.getExitCode() )
    {
        return handle_check_target_env_call_error( result, r.executable() );
    }
    return 0;
}

int
target_env_process_output( const boost::python::list& args,
                           const boost::python::object& callback,
                           const std::string& input,
                           int timeout )
{
    return _process_output( Calamares::Utils::RunLocation::RunInTarget, args, callback, input, timeout );
}

int
host_env_process_output( const boost::python::list& args,
                         const boost::python::object& callback,
                         const std::string& input,
                         int timeout )
{
    return _process_output( Calamares::Utils::RunLocation::RunInHost, args, callback, input, timeout );
}

}  // namespace CalamaresPython
