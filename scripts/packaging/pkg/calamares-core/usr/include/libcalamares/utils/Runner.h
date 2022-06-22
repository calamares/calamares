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
 * host system (through env(1)) or in the target (by calling chroot(8)).
 * It has an output signal that handles output one line at a time
 * (unlike QProcess that lets you do the buffering yourself).
 * This output processing is only enabled if you do so explicitly.
 *
 * Use the set*() methods to configure the runner.
 *
 * If you call enableOutputProcessing(), then you can connect to
 * the output() signal to receive each line (including trailing newline!).
 *
 * Processes are always run with LC_ALL and LANG set to "C".
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
     * Equivalent to Calamares::Utils::Runner::Runner() followed by
     * calling setCommand().
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
    Runner& setInput( const QString& input )
    {
        m_input = input;
        return *this;
    }
    Runner& setOutputProcessing( bool enable )
    {
        m_output = enable;
        return *this;
    }

    Runner& enableOutputProcessing()
    {
        m_output = true;
        return *this;
    }

    ProcessResult run();
    /** @brief The executable (argv[0]) that this runner will run
     *
     * This is the first element of the command; it does not include
     * env(1) or chroot(8) which are injected when actually running
     * the command.
     */
    QString executable() const { return m_command.isEmpty() ? QString() : m_command.first(); }

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
};

}  // namespace Utils
}  // namespace Calamares

#endif
