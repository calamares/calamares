/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017-2018, Adriaan de Groot <groot@kde.org>
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
#ifndef CALAMARESUTILSSYSTEM_H
#define CALAMARESUTILSSYSTEM_H

#include "DllMacro.h"

#include "Job.h"

#include <QObject>
#include <QPair>
#include <QString>

namespace CalamaresUtils
{
class ProcessResult : public QPair< int, QString >
{
public:
    /** @brief Implicit one-argument constructor has no output, only a return code */
    ProcessResult( int r ) : QPair< int, QString >( r, QString() ) {}
    ProcessResult( int r, QString s ) : QPair< int, QString >( r, s ) {}

    int getExitCode() const { return first; }
    QString getOutput() const { return second; }

    /** @brief Explain a typical external process failure.
     *
     * @param errorCode Return code from runCommand() or similar
     *                  (negative values get special explanation). The member
     *                  function uses the exit code stored in the ProcessResult
     * @param output    (error) output from the command, used when there is
     *                  an error to report (exit code > 0). The member
     *                  function uses the output stored in the ProcessResult.
     * @param command   String or split-up string of the command
     *                  that was invoked.
     * @param timeout   Timeout passed to the process runner, for explaining
     *                  error code -4 (timeout).
     */
    static Calamares::JobResult explainProcess( int errorCode, const QString& command, const QString& output, int timeout );

    /// @brief Convenience wrapper for explainProcess()
    inline Calamares::JobResult explainProcess( const QString& command, int timeout ) const
    {
        return explainProcess( getExitCode(), command, getOutput(), timeout );
    }

    /// @brief Convenience wrapper for explainProcess()
    inline Calamares::JobResult explainProcess( const QStringList& command, int timeout ) const
    {
        return explainProcess( getExitCode(), command.join( ' ' ), getOutput(), timeout );
    }
} ;

/**
 * @brief The System class is a singleton with utility functions that perform
 * system-specific operations.
 */
class DLLEXPORT System : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief System the constructor. Only call this once in a Calamares instance.
     * @param doChroot set to true if all external commands should run in the
     * target system chroot, otherwise false to run everything on the current system.
     * @param parent the QObject parent.
     */
    explicit System( bool doChroot, QObject* parent = nullptr );
    virtual ~System();

    static System* instance();

    /**
      * Runs the mount utility with the specified parameters.
      * @param devicePath the path of the partition to mount.
      * @param mountPoint the full path of the target mount point.
      * @param filesystemName the name of the filesystem (optional).
      * @param options any additional options as passed to mount -o (optional).
      * @returns the program's exit code, or:
      *             -1 = QProcess crash
      *             -2 = QProcess cannot start
      *             -3 = bad arguments
      */
    DLLEXPORT int mount( const QString& devicePath,
                         const QString& mountPoint,
                         const QString& filesystemName = QString(),
                         const QString& options = QString() );


    /** (Typed) Boolean describing where a particular command should be run,
     *  whether in the host (live) system or in the (chroot) target system.
     */
    enum class RunLocation { RunInHost, RunInTarget };

    /**
      * Runs the specified command in the chroot of the target system.
      * @param args the command with arguments, as a string list.
      * @param workingPath the current working directory for the QProcess
      *        call (optional).
      * @param stdInput the input string to send to the running process as
      *        standard input (optional).
      * @param timeoutSec the timeout after which the process will be
      *        killed (optional, default is 0 i.e. no timeout).
      *
      * @returns the program's exit code and its output (if any). Special
      *     exit codes (which will never have any output) are:
      *             -1 = QProcess crash
      *             -2 = QProcess cannot start
      *             -3 = bad arguments
      *             -4 = QProcess timeout
      */
    static DLLEXPORT ProcessResult runCommand(
        RunLocation location,
        const QStringList &args,
        const QString& workingPath = QString(),
        const QString& stdInput = QString(),
        int timeoutSec = 0 );

    /** @brief Convenience wrapper for runCommand().
     *  Runs the command in the location specified through the boolean
     *  doChroot(), which is what you usually want for running commands
     *  during installation.
      */
    inline ProcessResult targetEnvCommand(
        const QStringList &args,
        const QString& workingPath = QString(),
        const QString& stdInput = QString(),
        int timeoutSec = 0 )
    {
        return runCommand(
            m_doChroot ? RunLocation::RunInTarget : RunLocation::RunInHost,
            args,
            workingPath,
            stdInput,
            timeoutSec );
    }

    /** @brief Convenience wrapper for targetEnvCommand() which returns only the exit code */
    inline int targetEnvCall( const QStringList& args,
                              const QString& workingPath = QString(),
                              const QString& stdInput = QString(),
                              int timeoutSec = 0 )
    {
        return targetEnvCommand( args, workingPath, stdInput, timeoutSec ).first;
    }

    /** @brief Convenience wrapper for targetEnvCommand() which returns only the exit code */
    inline int targetEnvCall( const QString& command,
                              const QString& workingPath = QString(),
                              const QString& stdInput = QString(),
                              int timeoutSec = 0 )
    {
        return targetEnvCall( QStringList{ command }, workingPath, stdInput, timeoutSec );
    }

    /** @brief Convenience wrapper for targetEnvCommand() which returns only the exit code
     *
     * Places the called program's output in the @p output string.
     */
    int targetEnvOutput( const QStringList& args,
                                QString& output,
                                const QString& workingPath = QString(),
                                const QString& stdInput = QString(),
                                int timeoutSec = 0 )
    {
        auto r = targetEnvCommand( args, workingPath, stdInput, timeoutSec );
        output = r.second;
        return r.first;
    }

    /** @brief Convenience wrapper for targetEnvCommand() which returns only the exit code
     *
     * Places the called program's output in the @p output string.
     */
    inline int targetEnvOutput( const QString& command,
                                QString& output,
                                const QString& workingPath = QString(),
                                const QString& stdInput = QString(),
                                int timeoutSec = 0 )
    {
        return targetEnvOutput( QStringList{ command }, output, workingPath, stdInput, timeoutSec );
    }

    /**
     * @brief getTotalMemoryB returns the total main memory, in bytes.
     *
     * Since it is difficult to get the RAM memory size exactly -- either
     * by reading information from the DIMMs, which may fail on virtual hosts
     * or from asking the kernel, which doesn't report some memory areas --
     * this returns a pair of guessed-size (in bytes) and a "guesstimate factor"
     * which says how good the guess is. Generally, assume the *real* memory
     * available is size * guesstimate.
     *
     * If nothing can be found, returns a 0 size and 0 guesstimate.
     *
     * @return size, guesstimate-factor
     */
    DLLEXPORT QPair<quint64, float> getTotalMemoryB() const;

    /**
     * @brief getCpuDescription returns a string describing the CPU.
     *
     * Returns the value of the "model name" line in /proc/cpuinfo.
     */
    DLLEXPORT QString getCpuDescription() const;

    /**
     * @brief getTotalDiskB returns the total disk attached, in bytes.
     *
     * If nothing can be found, returns a 0.
     */
    DLLEXPORT quint64 getTotalDiskB() const;

    DLLEXPORT bool doChroot() const;

private:
    static System* s_instance;

    bool m_doChroot;
};

}

#endif // CALAMARESUTILSSYSTEM_H
