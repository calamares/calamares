/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#ifndef UTILS_RUNNER_H
#define UTILS_RUNNER_H

#include "CalamaresUtilsSystem.h"

#include <QDir>
#include <QObject>
#include <QProcess>
#include <QStringList>

#include <chrono>
#include <memory>
#include <optional>

namespace Calamares
{
namespace Utils
{

using RunLocation = CalamaresUtils::System::RunLocation;
using ProcessResult = CalamaresUtils::ProcessResult;

/** @brief A Runner wraps a process and handles running it and processing output
 *
 * This is basically a QProcess, but handles both running in the
 * host system (natively) or in the target (by calling chroot).
 * It has an output signal that handles output one line at a time
 * (unlike QProcess that lets you do the buffering yourself).
 * This output processing is only enabled if you do so explicitly.
 */
class Runner : public QObject
{
    Q_OBJECT

public:
    /** @brief Create an empty runner
     *
     * This is a runner with no commands, nothing; call set*() methods
     * to configure it.
     */
    Runner();
    /** @brief Create a runner with a specified command
     *
     * Equivalent to Calamares::Utils::Runner::Runner()
     */
    Runner( const QStringList& command );
    virtual ~Runner() override;

    Runner& setCommand( const QStringList& command )
    {
        m_command = command;
        return *this;
    }
    Runner& setLocation( RunLocation r )
    {
        m_location = r;
        return *this;
    }
    Runner& setWorkingDirectory( const QDir& directory )
    {
        m_directory = directory.absolutePath();
        return *this;
    }
    Runner& setWorkingDirectory( const QString& directory )
    {
        m_directory = directory;
        return *this;
    }
    Runner& setTimeout( std::chrono::seconds timeout )
    {
        m_timeout = timeout;
        return *this;
    }
    Runner& setInput( const QString& stdin )
    {
        m_input = stdin;
        return *this;
    }

    Runner& enableOutputProcessing( bool enable = true )
    {
        m_output = enable;
        return *this;
    }

    ProcessResult run();

signals:
    void output( QString line );

private:
    // What to run, and where.
    QStringList m_command;
    QString m_directory;
    RunLocation m_location { RunLocation::RunInHost };

    // Settings for when it actually runs
    QString m_input;
    std::chrono::milliseconds m_timeout { 0 };
    bool m_output = false;

    // Internals for when it really does run
    struct Private;
    std::unique_ptr< Private > d;
};

}  // namespace Utils
}  // namespace Calamares

#endif
