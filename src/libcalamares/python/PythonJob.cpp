/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2023 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */
#include "python/PythonJob.h"

namespace Calamares
{
namespace Python
{

struct Job::Private
{
};

Job::Job( const QString& scriptFile,
          const QString& workingPath,
          const QVariantMap& moduleConfiguration,
          QObject* parent )
{
}

Job::~Job() {}

QString
Job::prettyName() const
{
    return QStringLiteral( "Python Pretty" );
}

QString
Job::prettyStatusMessage() const
{
    return QStringLiteral( "Python Status" );
}

JobResult
Job::exec()
{
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
