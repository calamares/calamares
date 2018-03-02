/* === This file is part of Calamares - <https://github.com/calamares> ===
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

#include "PythonJob.h"

#include "PythonHelper.h"
#include "utils/Logger.h"
#include "GlobalStorage.h"
#include "JobQueue.h"

#include <QDir>

#undef slots
#include <boost/python.hpp>
#include <boost/python/args.hpp>

#include "PythonJobApi.h"


namespace bp = boost::python;

BOOST_PYTHON_FUNCTION_OVERLOADS( mount_overloads,
                                 CalamaresPython::mount,
                                 2, 4 );
BOOST_PYTHON_FUNCTION_OVERLOADS( target_env_call_str_overloads,
                                 CalamaresPython::target_env_call,
                                 1, 3 );
BOOST_PYTHON_FUNCTION_OVERLOADS( target_env_call_list_overloads,
                                 CalamaresPython::target_env_call,
                                 1, 3 );
BOOST_PYTHON_FUNCTION_OVERLOADS( check_target_env_call_str_overloads,
                                 CalamaresPython::check_target_env_call,
                                 1, 3 );
BOOST_PYTHON_FUNCTION_OVERLOADS( check_target_env_call_list_overloads,
                                 CalamaresPython::check_target_env_call,
                                 1, 3 );
BOOST_PYTHON_FUNCTION_OVERLOADS( check_target_env_output_str_overloads,
                                 CalamaresPython::check_target_env_output,
                                 1, 3 );
BOOST_PYTHON_FUNCTION_OVERLOADS( check_target_env_output_list_overloads,
                                 CalamaresPython::check_target_env_output,
                                 1, 3 );
BOOST_PYTHON_MODULE( libcalamares )
{
    bp::object package = bp::scope();
    package.attr( "__path__" ) = "libcalamares";

    bp::scope().attr( "ORGANIZATION_NAME" ) = CALAMARES_ORGANIZATION_NAME;
    bp::scope().attr( "ORGANIZATION_DOMAIN" ) = CALAMARES_ORGANIZATION_DOMAIN;
    bp::scope().attr( "APPLICATION_NAME" ) = CALAMARES_APPLICATION_NAME;
    bp::scope().attr( "VERSION" ) = CALAMARES_VERSION;
    bp::scope().attr( "VERSION_SHORT" ) = CALAMARES_VERSION_SHORT;

    bp::class_< CalamaresPython::PythonJobInterface >( "Job", bp::init< Calamares::PythonJob* >() )
        .def_readonly( "module_name",   &CalamaresPython::PythonJobInterface::moduleName )
        .def_readonly( "pretty_name",   &CalamaresPython::PythonJobInterface::prettyName )
        .def_readonly( "working_path",  &CalamaresPython::PythonJobInterface::workingPath )
        .def_readonly( "configuration", &CalamaresPython::PythonJobInterface::configuration )
        .def(
            "setprogress",
            &CalamaresPython::PythonJobInterface::setprogress,
            bp::args( "progress" ),
            "Reports the progress status of this job to Calamares, "
            "as a real number between 0 and 1."
        );

    bp::class_< CalamaresPython::GlobalStoragePythonWrapper >( "GlobalStorage", bp::init< Calamares::GlobalStorage* >() )
        .def( "contains",   &CalamaresPython::GlobalStoragePythonWrapper::contains )
        .def( "count",      &CalamaresPython::GlobalStoragePythonWrapper::count )
        .def( "insert",     &CalamaresPython::GlobalStoragePythonWrapper::insert )
        .def( "keys",       &CalamaresPython::GlobalStoragePythonWrapper::keys )
        .def( "remove",     &CalamaresPython::GlobalStoragePythonWrapper::remove )
        .def( "value",      &CalamaresPython::GlobalStoragePythonWrapper::value );

    // libcalamares.utils submodule starts here
    bp::object utilsModule( bp::handle<>( bp::borrowed( PyImport_AddModule( "libcalamares.utils" ) ) ) );
    bp::scope().attr( "utils" ) = utilsModule;
    bp::scope utilsScope = utilsModule;
    Q_UNUSED( utilsScope );

    bp::def(
        "debug",
        &CalamaresPython::debug,
        bp::args( "s" ),
        "Writes the given string to the Calamares debug stream."
    );
    bp::def(
        "warning",
        &CalamaresPython::warning,
        bp::args( "s" ),
        "Writes the given string to the Calamares warning stream."
    );

    bp::def(
        "mount",
        &CalamaresPython::mount,
        mount_overloads(
            bp::args( "device_path",
                      "mount_point",
                      "filesystem_name",
                      "options" ),
            "Runs the mount utility with the specified parameters.\n"
            "Returns the program's exit code, or:\n"
            "-1 = QProcess crash\n"
            "-2 = QProcess cannot start\n"
            "-3 = bad arguments"
        )
    );
    bp::def(
        "target_env_call",
        static_cast< int (*)( const std::string&,
                              const std::string&,
                              int ) >( &CalamaresPython::target_env_call ),
        target_env_call_str_overloads(
            bp::args( "command",
                      "stdin",
                      "timeout" ),
            "Runs the specified command in the chroot of the target system.\n"
            "Returns the program's exit code, or:\n"
            "-1 = QProcess crash\n"
            "-2 = QProcess cannot start\n"
            "-3 = bad arguments\n"
            "-4 = QProcess timeout"
        )
    );
    bp::def(
        "target_env_call",
        static_cast< int (*)( const bp::list&,
                              const std::string&,
                              int ) >( &CalamaresPython::target_env_call ),
        target_env_call_list_overloads(
            bp::args( "args",
                      "stdin",
                      "timeout" ),
            "Runs the specified command in the chroot of the target system.\n"
            "Returns the program's exit code, or:\n"
            "-1 = QProcess crash\n"
            "-2 = QProcess cannot start\n"
            "-3 = bad arguments\n"
            "-4 = QProcess timeout"
        )
    );

    bp::def(
        "check_target_env_call",
        static_cast< int (*)( const std::string&,
                              const std::string&,
                              int ) >( &CalamaresPython::check_target_env_call ),
        check_target_env_call_str_overloads(
            bp::args( "command",
                      "stdin",
                      "timeout" ),
            "Runs the specified command in the chroot of the target system.\n"
            "Returns 0, which is program's exit code if the program exited "
            "successfully, or raises a subprocess.CalledProcessError."
        )
    );
    bp::def(
        "check_target_env_call",
        static_cast< int (*)( const bp::list&,
                              const std::string&,
                              int ) >( &CalamaresPython::check_target_env_call ),
        check_target_env_call_list_overloads(
            bp::args( "args",
                      "stdin",
                      "timeout" ),
            "Runs the specified command in the chroot of the target system.\n"
            "Returns 0, which is program's exit code if the program exited "
            "successfully, or raises a subprocess.CalledProcessError."
        )
    );

    bp::def(
        "check_target_env_output",
        static_cast< std::string (*)( const std::string&,
                                      const std::string&,
                                      int ) >( &CalamaresPython::check_target_env_output ),
        check_target_env_output_str_overloads(
            bp::args( "command",
                      "stdin",
                      "timeout" ),
            "Runs the specified command in the chroot of the target system.\n"
            "Returns the program's standard output, and raises a "
            "subprocess.CalledProcessError if something went wrong."
        )
    );
    bp::def(
        "check_target_env_output",
        static_cast< std::string (*)( const bp::list&,
                                      const std::string&,
                                      int ) >( &CalamaresPython::check_target_env_output ),
        check_target_env_output_list_overloads(
            bp::args( "args",
                      "stdin",
                      "timeout" ),
            "Runs the specified command in the chroot of the target system.\n"
            "Returns the program's standard output, and raises a "
            "subprocess.CalledProcessError if something went wrong."
        )
    );
    bp::def(
        "obscure",
        &CalamaresPython::obscure,
        bp::args( "s" ),
        "Simple string obfuscation function based on KStringHandler::obscure.\n"
        "Returns a string, generated using a simple symmetric encryption.\n"
        "Applying the function to a string obscured by this function will result "
        "in the original string."
    );


    bp::def(
        "gettext_languages",
        &CalamaresPython::gettext_languages,
        "Returns list of languages (most to least-specific) for gettext."
    );

    bp::def(
        "gettext_path",
        &CalamaresPython::gettext_path,
        "Returns path for gettext search."
    );
}


namespace Calamares {


PythonJob::PythonJob( const QString& scriptFile,
                      const QString& workingPath,
                      const QVariantMap& moduleConfiguration,
                      QObject* parent )
    : Job( parent )
    , m_scriptFile( scriptFile )
    , m_workingPath( workingPath )
    , m_description()
    , m_configurationMap( moduleConfiguration )
{
}


PythonJob::~PythonJob()
{}


QString
PythonJob::prettyName() const
{
    return QDir( m_workingPath ).dirName();
}


QString
PythonJob::prettyStatusMessage() const
{
    if ( m_description.isEmpty() )
        return tr( "Running %1 operation." )
                .arg( QDir( m_workingPath ).dirName() );
    else
        return m_description;
}


JobResult
PythonJob::exec()
{
    // We assume m_scriptFile to be relative to m_workingPath.
    QDir workingDir( m_workingPath );
    if ( !workingDir.exists() ||
         !workingDir.isReadable() )
    {
        return JobResult::error( tr( "Bad working directory path" ),
                                 tr( "Working directory %1 for python job %2 is not readable." )
                                    .arg( m_workingPath )
                                    .arg( prettyName() ) );
    }

    QFileInfo scriptFI( workingDir.absoluteFilePath( m_scriptFile ) );
    if ( !scriptFI.exists() ||
         !scriptFI.isFile() ||
         !scriptFI.isReadable() )
    {
        return JobResult::error( tr( "Bad main script file" ),
                                 tr( "Main script file %1 for python job %2 is not readable." )
                                    .arg( scriptFI.absoluteFilePath() )
                                    .arg( prettyName() ) );
    }

    try
    {
        bp::dict scriptNamespace = helper()->createCleanNamespace();

        bp::object calamaresModule = bp::import( "libcalamares" );
        bp::dict calamaresNamespace = bp::extract< bp::dict >( calamaresModule.attr( "__dict__" ) );

        calamaresNamespace[ "job" ] = CalamaresPython::PythonJobInterface( this );
        calamaresNamespace[ "globalstorage" ] = CalamaresPython::GlobalStoragePythonWrapper(
                                                JobQueue::instance()->globalStorage() );

        bp::object execResult = bp::exec_file( scriptFI.absoluteFilePath().toLocal8Bit().data(),
                                           scriptNamespace,
                                           scriptNamespace );

        bp::object entryPoint = scriptNamespace[ "run" ];
        bp::object prettyNameFunc = scriptNamespace.get("pretty_name", bp::object());

        cDebug() << "Job file" << scriptFI.absoluteFilePath();
        if ( !prettyNameFunc.is_none() )
        {
            bp::extract< std::string > prettyNameResult( prettyNameFunc() );
            if ( prettyNameResult.check() )
            {
                m_description = QString::fromStdString( prettyNameResult() ).trimmed();
            }
            if ( !m_description.isEmpty() )
            {
                cDebug() << "Job description from pretty_name" << prettyName() << "=" << m_description;
                emit progress( 0 );
            }
        }

        if ( m_description.isEmpty() )
        {
            bp::extract< std::string > entryPoint_doc_attr(entryPoint.attr( "__doc__" ) );

            if ( entryPoint_doc_attr.check() )
            {
                m_description = QString::fromStdString( entryPoint_doc_attr() ).trimmed();
                auto i_newline = m_description.indexOf('\n');
                if ( i_newline > 0 )
                    m_description.truncate( i_newline );
                cDebug() << "Job description from __doc__" << prettyName() << "=" << m_description;
                emit progress( 0 );
            }
        }

        bp::object runResult = entryPoint();

        if ( runResult.is_none() )
        {
            return JobResult::ok();
        }
        else // Something happened in the Python job
        {
            bp::tuple resultTuple = bp::extract< bp::tuple >( runResult );
            QString message = QString::fromStdString( bp::extract< std::string >( resultTuple[ 0 ] ) );
            QString description = QString::fromStdString( bp::extract< std::string >( resultTuple[ 1 ] ) );
            return JobResult::error( message, description );
        }
    }
    catch ( bp::error_already_set )
    {
        QString msg;
        if ( PyErr_Occurred() )
        {
            msg = helper()->handleLastError();
        }
        bp::handle_exception();
        PyErr_Clear();
        return JobResult::error( tr( "Boost.Python error in job \"%1\"." ).arg( prettyName() ),
                                 msg );
    }
}


void
PythonJob::emitProgress( qreal progressValue )
{
    emit progress( progressValue );
}


CalamaresPython::Helper*
PythonJob::helper()
{
    auto ptr = CalamaresPython::Helper::s_instance;
    if (!ptr)
        ptr = new CalamaresPython::Helper;
    return ptr;
}


} // namespace Calamares
