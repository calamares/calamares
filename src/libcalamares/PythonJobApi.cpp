/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2016, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
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

#include "GlobalStorage.h"
#include "JobQueue.h"

#include <QCoreApplication>
#include <QDir>
#include <QStandardPaths>

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
    auto moduleDir = QDir( m_parent->m_workingPath );
    moduleName = moduleDir.dirName().toStdString();
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

static QStringList
_gettext_languages()
{
    QStringList languages;

    // There are two ways that Python jobs can be initialised:
    //  - through JobQueue, in which case that has an instance which holds
    //    a GlobalStorage object, or
    //  - through the Python test-script, which initialises its
    //    own GlobalStoragePythonWrapper, which then holds a
    //    GlobalStorage object for all of Python.
    Calamares::JobQueue* jq = Calamares::JobQueue::instance();
    Calamares::GlobalStorage* gs = jq ? jq->globalStorage() : CalamaresPython::GlobalStoragePythonWrapper::globalStorageInstance();

    QVariant localeConf_ = gs->value( "localeConf" );
    if ( localeConf_.canConvert< QVariantMap >() )
    {
        QVariant lang_ = localeConf_.value< QVariantMap >()[ "LANG" ];
        if ( lang_.canConvert< QString >() )
        {
            QString lang = lang_.value< QString >();
            languages.append( lang );
            if ( lang.indexOf( '.' ) > 0 )
            {
                lang.truncate( lang.indexOf( '.' ) );
                languages.append( lang );
            }
            if ( lang.indexOf( '_' ) > 0 )
            {
                lang.truncate( lang.indexOf( '_' ) );
                languages.append( lang );
            }
        }
    }
    return languages;
}

bp::list
gettext_languages()
{
    bp::list pyList;
    for ( auto lang : _gettext_languages() )
        pyList.append( lang.toStdString() );
    return pyList;
}

static void
_add_localedirs( QStringList& pathList, const QString& candidate )
{
    if ( !candidate.isEmpty() && !pathList.contains( candidate ) )
    {
        pathList.prepend( candidate );
        if ( QDir( candidate ).cd( "lang" ) )
            pathList.prepend( candidate + "/lang" );
    }
}

bp::object
gettext_path()
{
    // TODO: distinguish between -d runs and normal runs
    // TODO: can we detect DESTDIR-installs?
    QStringList candidatePaths = QStandardPaths::locateAll( QStandardPaths::GenericDataLocation, "locale", QStandardPaths::LocateDirectory );
    QString extra = QCoreApplication::applicationDirPath();
    _add_localedirs( candidatePaths, extra ); // Often /usr/local/bin
    if ( !extra.isEmpty() )
    {
        QDir d( extra );
        if ( d.cd( "../share/locale" ) ) // Often /usr/local/bin/../share/locale -> /usr/local/share/locale
            _add_localedirs( candidatePaths, d.canonicalPath() );
    }
    _add_localedirs( candidatePaths, QDir().canonicalPath() ); // .

    cDebug() << "Standard paths" << candidatePaths;

    for ( auto lang : _gettext_languages() )
        for ( auto localedir : candidatePaths )
        {
            QDir ldir( localedir );
            cDebug() << "Checking" << lang << "in" <<ldir.canonicalPath();
            if ( ldir.cd( lang ) )
                return bp::object( localedir.toStdString() );
        }
    return bp::object();  // None
}


}
