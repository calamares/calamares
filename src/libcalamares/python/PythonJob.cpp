/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2023 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */
#include "python/PythonJob.h"

#include <QDir>
#include <QFileInfo>
#include <QString>

#undef slots
#include <pybind11/embed.h>
#include <pybind11/eval.h>

namespace py = pybind11;

namespace Calamares
{
namespace Python
{

struct Job::Private
{
    Private( const QString& script, const QString& path, const QVariantMap& configuration )
        : scriptFile( script )
        , workingPath( path )
        , configurationMap( configuration )
    {
    }
    QString scriptFile;
    QString workingPath;
    QVariantMap configurationMap;
};

Job::Job( const QString& scriptFile,
          const QString& workingPath,
          const QVariantMap& moduleConfiguration,
          QObject* parent )
    : m_d( std::make_unique< Job::Private >( scriptFile, workingPath, moduleConfiguration ) )
{
}

Job::~Job() {}

QString
Job::prettyName() const
{
    return QDir( m_d->workingPath ).dirName();
}

QString
Job::prettyStatusMessage() const
{
    return QStringLiteral( "Python Status" );
}

JobResult
Job::exec()
{
    // We assume m_scriptFile to be relative to m_workingPath.
    QDir workingDir( m_d->workingPath );
    if ( !workingDir.exists() || !workingDir.isReadable() )
    {
        return JobResult::error( tr( "Bad working directory path" ),
                                 tr( "Working directory %1 for python job %2 is not readable." )
                                     .arg( m_d->workingPath )
                                     .arg( prettyName() ) );
    }

    QFileInfo scriptFI( workingDir.absoluteFilePath( m_d->scriptFile ) );
    if ( !scriptFI.exists() || !scriptFI.isFile() || !scriptFI.isReadable() )
    {
        return JobResult::error( tr( "Bad main script file" ),
                                 tr( "Main script file %1 for python job %2 is not readable." )
                                     .arg( scriptFI.absoluteFilePath() )
                                     .arg( prettyName() ) );
    }

    py::scoped_interpreter guard {};
    auto scope = py::module_::import( "__main__" ).attr( "__dict__" );
    py::eval_file( scriptFI.absoluteFilePath().toUtf8().constData(), scope );

    return JobResult::ok();
}

/** @brief Sets the pre-run Python code for all PythonJobs
 *
 * A PythonJob runs the code from the scriptFile parameter to
 * the constructor; the pre-run code is **also** run, before
 * even the scriptFile code. Use this in testing mode
 * to modify Python internals.
 *
 * No ownership of @p script is taken: pass in a pointer to
 * a character literal or something that lives longer than the
 * job. Pass in @c nullptr to switch off pre-run code.
 */
void
Job::setInjectedPreScript( const char* script )
{
}

}  // namespace Python
}  // namespace Calamares
