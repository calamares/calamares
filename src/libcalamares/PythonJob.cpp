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

#include "PythonJobHelper.h"
#include "utils/Logger.h"

#include <QDir>

#undef slots
#include <boost/python.hpp>


namespace bp = boost::python;
namespace Calamares {


PythonJob::PythonJob( const QString& scriptFile,
                      const QString& workingPath,
                      QObject* parent )
    : Job( parent )
    , m_scriptFile( scriptFile )
    , m_workingPath( workingPath )
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

        bp::object result = bp::exec_file( scriptFI.absoluteFilePath().toLocal8Bit().data(),
                                           scriptNamespace,
                                           scriptNamespace );

        bp::object entryPoint = scriptNamespace[ "calamares_main" ];

        QString message = QString::fromStdString( bp::extract< std::string >( entryPoint() ) );

        cDebug() << "Python job" << prettyName() << "finished with message" << message;
    }
    catch ( bp::error_already_set e )
    {
        return JobResult::error( tr( "Boost.Python error" ) );
    }

    return JobResult::ok();
}


PythonJobHelper*
PythonJob::helper()
{
    return PythonJobHelper::s_instance;
}


} // namespace Calamares
