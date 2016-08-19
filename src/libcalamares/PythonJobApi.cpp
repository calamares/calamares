/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2016, Teo Mrnjavac <teo@kde.org>
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

#include "PythonJobApi.h"

#include "PythonHelper.h"
#include "utils/Logger.h"
#include "utils/CalamaresUtilsSystem.h"
#include "utils/CalamaresUtils.h"

#include <QDir>

#undef slots
#include <boost/python.hpp>

namespace bp = boost::python;

namespace CalamaresPython
{

int
mount( const std::string& device_path,
       const std::string& mount_point,
       const std::string& filesystem_name,
       const std::string& options )
{
    return CalamaresUtils::System::instance()->
            mount( QString::fromStdString( device_path ),
                   QString::fromStdString( mount_point ),
                   QString::fromStdString( filesystem_name ),
                   QString::fromStdString( options ) );
}


int
target_env_call( const std::string& command,
             const std::string& stdin,
             int timeout )
{
    return CalamaresUtils::System::instance()->
            targetEnvCall( QString::fromStdString( command ),
                           QString(),
                           QString::fromStdString( stdin ),
                           timeout );
}


int
target_env_call( const bp::list& args,
             const std::string& stdin,
             int timeout )
{
    QStringList list;
    for ( int i = 0; i < bp::len( args ); ++i )
    {
        list.append( QString::fromStdString(
            bp::extract< std::string >( args[ i ] ) ) );
    }

    return CalamaresUtils::System::instance()->
            targetEnvCall( list,
                           QString(),
                           QString::fromStdString( stdin ),
                           timeout );
}


int
check_target_env_call( const std::string& command,
                   const std::string& stdin,
                   int timeout )
{
    int ec = target_env_call( command, stdin, timeout );
    return _handle_check_target_env_call_error( ec, QString::fromStdString( command ) );
}


int
check_target_env_call( const bp::list& args,
                   const std::string& stdin,
                   int timeout )
{
    int ec = target_env_call( args, stdin, timeout );
    if ( !ec )
        return ec;

    QStringList failedCmdList;
    for ( int i = 0; i < bp::len( args ); ++i )
    {
        failedCmdList.append( QString::fromStdString(
            bp::extract< std::string >( args[ i ] ) ) );
    }

    return _handle_check_target_env_call_error( ec, failedCmdList.join( ' ' ) );
}


std::string
check_target_env_output( const std::string& command,
                     const std::string& stdin,
                     int timeout )
{
    QString output;
    int ec = CalamaresUtils::System::instance()->
             targetEnvOutput( QString::fromStdString( command ),
                              output,
                              QString(),
                              QString::fromStdString( stdin ),
                              timeout );
    _handle_check_target_env_call_error( ec, QString::fromStdString( command ) );
    return output.toStdString();
}


std::string
check_target_env_output( const bp::list& args,
                     const std::string& stdin,
                     int timeout )
{
    QString output;
    QStringList list;
    for ( int i = 0; i < bp::len( args ); ++i )
    {
        list.append( QString::fromStdString(
            bp::extract< std::string >( args[ i ] ) ) );
    }

    int ec = CalamaresUtils::System::instance()->
             targetEnvOutput( list,
                              output,
                              QString(),
                              QString::fromStdString( stdin ),
                              timeout );
    _handle_check_target_env_call_error( ec, list.join( ' ' ) );
    return output.toStdString();
}


int
_handle_check_target_env_call_error( int ec, const QString& cmd )
{
    if ( !ec )
        return ec;

    QString raise = QString( "import subprocess\n"
                             "raise subprocess.CalledProcessError(%1,\"%2\")" )
                        .arg( ec )
                        .arg( cmd );
    bp::exec( raise.toStdString().c_str() );
    bp::throw_error_already_set();
    return ec;
}


void
debug( const std::string& s )
{
    cDebug() << "[PYTHON JOB]: " << QString::fromStdString( s );
}


PythonJobInterface::PythonJobInterface( Calamares::PythonJob* parent )
    : m_parent( parent )
{
    moduleName = QDir( m_parent->m_workingPath ).dirName().toStdString();
    prettyName = m_parent->prettyName().toStdString();
    workingPath = m_parent->m_workingPath.toStdString();
    configuration = CalamaresPython::variantMapToPyDict( m_parent->m_configurationMap );
}


void
PythonJobInterface::setprogress( qreal progress )
{
    if ( progress >= 0 && progress <= 1 )
        m_parent->emitProgress( progress );
}


std::string
obscure( const std::string& string )
{
    return CalamaresUtils::obscure( QString::fromStdString( string ) ).toStdString();
}

}
