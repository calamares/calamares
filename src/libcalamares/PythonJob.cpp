/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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
BOOST_PYTHON_FUNCTION_OVERLOADS( chroot_call_str_overloads,
                                 CalamaresPython::chroot_call,
                                 1, 3 );
BOOST_PYTHON_FUNCTION_OVERLOADS( chroot_call_list_overloads,
                                 CalamaresPython::chroot_call,
                                 1, 3 );
BOOST_PYTHON_FUNCTION_OVERLOADS( check_chroot_call_str_overloads,
                                 CalamaresPython::check_chroot_call,
                                 1, 3 );
BOOST_PYTHON_FUNCTION_OVERLOADS( check_chroot_call_list_overloads,
                                 CalamaresPython::check_chroot_call,
                                 1, 3 );
BOOST_PYTHON_FUNCTION_OVERLOADS( check_chroot_output_str_overloads,
                                 CalamaresPython::check_chroot_output,
                                 1, 3 );
BOOST_PYTHON_FUNCTION_OVERLOADS( check_chroot_output_list_overloads,
                                 CalamaresPython::check_chroot_output,
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

    bp::class_< Calamares::GlobalStorage >( "GlobalStorage", bp::init<>() )
        .def( "contains",   &Calamares::GlobalStorage::python_contains )
        .def( "count",      &Calamares::GlobalStorage::count )
        .def( "insert",     &Calamares::GlobalStorage::python_insert )
        .def( "keys",       &Calamares::GlobalStorage::python_keys )
        .def( "remove",     &Calamares::GlobalStorage::python_remove )
        .def( "value",      &Calamares::GlobalStorage::python_value );

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
        "chroot_call",
        static_cast< int (*)( const std::string&,
                              const std::string&,
                              int ) >( &CalamaresPython::chroot_call ),
        chroot_call_str_overloads(
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
        "chroot_call",
        static_cast< int (*)( const bp::list&,
                              const std::string&,
                              int ) >( &CalamaresPython::chroot_call ),
        chroot_call_list_overloads(
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
        "check_chroot_call",
        static_cast< int (*)( const std::string&,
                              const std::string&,
                              int ) >( &CalamaresPython::check_chroot_call ),
        check_chroot_call_str_overloads(
            bp::args( "command",
                      "stdin",
                      "timeout" ),
            "Runs the specified command in the chroot of the target system.\n"
            "Returns 0, which is program's exit code if the program exited "
            "successfully, or raises a subprocess.CalledProcessError."
        )
    );
    bp::def(
        "check_chroot_call",
        static_cast< int (*)( const bp::list&,
                              const std::string&,
                              int ) >( &CalamaresPython::check_chroot_call ),
        check_chroot_call_list_overloads(
            bp::args( "args",
                      "stdin",
                      "timeout" ),
            "Runs the specified command in the chroot of the target system.\n"
            "Returns 0, which is program's exit code if the program exited "
            "successfully, or raises a subprocess.CalledProcessError."
        )
    );

    bp::def(
        "check_chroot_output",
        static_cast< std::string (*)( const std::string&,
                                      const std::string&,
                                      int ) >( &CalamaresPython::check_chroot_output ),
        check_chroot_output_str_overloads(
            bp::args( "command",
                      "stdin",
                      "timeout" ),
            "Runs the specified command in the chroot of the target system.\n"
            "Returns the program's standard output, and raises a "
            "subprocess.CalledProcessError if something went wrong."
        )
    );
    bp::def(
        "check_chroot_output",
        static_cast< std::string (*)( const bp::list&,
                                      const std::string&,
                                      int ) >( &CalamaresPython::check_chroot_output ),
        check_chroot_output_list_overloads(
            bp::args( "args",
                      "stdin",
                      "timeout" ),
            "Runs the specified command in the chroot of the target system.\n"
            "Returns the program's standard output, and raises a "
            "subprocess.CalledProcessError if something went wrong."
        )
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
    , m_configurationMap( moduleConfiguration )
{
}


PythonJob::~PythonJob()
{}


QString
PythonJob::prettyName() const
{
    return tr( "Run script %1" )
                .arg( QDir( m_workingPath ).dirName() +
                      QDir::separator() +
                      m_scriptFile );
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
        bp::object scriptNamespace = helper()->createCleanNamespace();

        bp::object calamaresModule = bp::import( "libcalamares" );
        bp::dict calamaresNamespace = bp::extract< bp::dict >( calamaresModule.attr( "__dict__" ) );

        calamaresNamespace[ "job" ] = CalamaresPython::PythonJobInterface( this );
        calamaresNamespace[ "globalstorage" ] = bp::ptr( JobQueue::instance()->globalStorage() );

        bp::object execResult = bp::exec_file( scriptFI.absoluteFilePath().toLocal8Bit().data(),
                                           scriptNamespace,
                                           scriptNamespace );

        bp::object entryPoint = scriptNamespace[ "run" ];

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

    return JobResult::ok();
}


void
PythonJob::emitProgress( qreal progressValue )
{
    emit progress( progressValue );
}


CalamaresPython::Helper*
PythonJob::helper()
{
    return CalamaresPython::Helper::s_instance;

}


} // namespace Calamares
