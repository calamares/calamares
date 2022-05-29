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

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "PythonHelper.h"
#include "partition/Mount.h"
#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"
#include "utils/RAII.h"
#include "utils/Runner.h"
#include "utils/String.h"
#include "utils/Yaml.h"

#include <QCoreApplication>
#include <QDir>
#include <QStandardPaths>

namespace bp = boost::python;

static int
handle_check_target_env_call_error( const CalamaresUtils::ProcessResult& ec, const QString& cmd )
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

static inline CalamaresUtils::ProcessResult
target_env_command( const QStringList& args, const std::string& input, int timeout )
{
    // Since Python doesn't give us the type system for distinguishing
    // seconds from other integral types, massage to seconds here.
    return CalamaresUtils::System::instance()->targetEnvCommand(
        args, QString(), QString::fromStdString( input ), std::chrono::seconds( timeout ) );
}

namespace CalamaresPython
{

int
mount( const std::string& device_path,
       const std::string& mount_point,
       const std::string& filesystem_name,
       const std::string& options )
{
    return CalamaresUtils::Partition::mount( QString::fromStdString( device_path ),
                                             QString::fromStdString( mount_point ),
                                             QString::fromStdString( filesystem_name ),
                                             QString::fromStdString( options ) );
}

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

static const char output_prefix[] = "[PYTHON JOB]:";
static inline void
log_action( unsigned int level, const std::string& s )
{
    Logger::CDebug( level ) << output_prefix << QString::fromStdString( s );
}

void
debug( const std::string& s )
{
    log_action( Logger::LOGDEBUG, s );
}

void
warning( const std::string& s )
{
    log_action( Logger::LOGWARNING, s );
}

void
error( const std::string& s )
{
    log_action( Logger::LOGERROR, s );
}

boost::python::dict
load_yaml( const std::string& path )
{
    const QString filePath = QString::fromStdString( path );
    bool ok = false;
    auto map = CalamaresUtils::loadYaml( filePath, &ok );
    if ( !ok )
    {
        cWarning() << "Loading YAML from" << filePath << "failed.";
    }
    return variantMapToPyDict( map );
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


std::string
obscure( const std::string& string )
{
    return Calamares::String::obscure( QString::fromStdString( string ) ).toStdString();
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
    Calamares::GlobalStorage* gs
        = jq ? jq->globalStorage() : CalamaresPython::GlobalStoragePythonWrapper::globalStorageInstance();

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
    {
        pyList.append( lang.toStdString() );
    }
    return pyList;
}

static void
_add_localedirs( QStringList& pathList, const QString& candidate )
{
    if ( !candidate.isEmpty() && !pathList.contains( candidate ) )
    {
        pathList.prepend( candidate );
        if ( QDir( candidate ).cd( "lang" ) )
        {
            pathList.prepend( candidate + "/lang" );
        }
    }
}

bp::object
gettext_path()
{
    // Going to log informatively just once
    static bool first_time = true;
    cScopedAssignment( &first_time, false );

    // TODO: distinguish between -d runs and normal runs
    // TODO: can we detect DESTDIR-installs?
    QStringList candidatePaths
        = QStandardPaths::locateAll( QStandardPaths::GenericDataLocation, "locale", QStandardPaths::LocateDirectory );
    QString extra = QCoreApplication::applicationDirPath();
    _add_localedirs( candidatePaths, extra );  // Often /usr/local/bin
    if ( !extra.isEmpty() )
    {
        QDir d( extra );
        if ( d.cd( "../share/locale" ) )  // Often /usr/local/bin/../share/locale -> /usr/local/share/locale
        {
            _add_localedirs( candidatePaths, d.canonicalPath() );
        }
    }
    _add_localedirs( candidatePaths, QDir().canonicalPath() );  // .

    if ( first_time )
    {
        cDebug() << "Determining gettext path from" << candidatePaths;
    }

    QStringList candidateLanguages = _gettext_languages();
    for ( const auto& lang : candidateLanguages )
    {
        for ( auto localedir : candidatePaths )
        {
            QDir ldir( localedir );
            if ( ldir.cd( lang ) )
            {
                Logger::CDebug( Logger::LOGDEBUG )
                    << output_prefix << "Found gettext" << lang << "in" << ldir.canonicalPath();
                return bp::object( localedir.toStdString() );
            }
        }
    }
    cWarning() << "No translation found for languages" << candidateLanguages;
    return bp::object();  // None
}


}  // namespace CalamaresPython
