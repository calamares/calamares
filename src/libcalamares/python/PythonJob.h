/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2023 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef CALAMARES_PYTHON_PYTHONJOB_H
#define CALAMARES_PYTHON_PYTHONJOB_H

// This file is called PythonJob.h because it would otherwise
// clashwith the Job.h in libcalamares proper.
#include "DllMacro.h"
#include "Job.h"

#include <QVariantMap>

#include <memory>

#if WITH_PYBIND11
#else
#error Source only for pybind11
#endif

namespace Calamares
{
namespace Python
{
class Job : public ::Calamares::Job
{
    Q_OBJECT
public:
    explicit DLLEXPORT Job( const QString& scriptFile,
                            const QString& workingPath,
                            const QVariantMap& moduleConfiguration = QVariantMap(),
                            QObject* parent = nullptr );
    ~Job() override;

    QString prettyName() const override;
    QString prettyStatusMessage() const override;
    ::Calamares::JobResult exec() override;

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
    static DLLEXPORT void setInjectedPreScript( const char* script );

    /** @brief Accessors for JobProxy */
    QString workingPath() const;
    QVariantMap configuration() const;
    /** @brief Proxy functions */
    void emitProgress( double progressValue );

private:
    struct Private;
    std::unique_ptr< Private > m_d;
};

}  // namespace Python
}  // namespace Calamares
#endif
