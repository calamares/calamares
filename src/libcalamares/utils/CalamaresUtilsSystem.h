/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017-2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */
#ifndef UTILS_CALAMARESUTILSSYSTEM_H
#define UTILS_CALAMARESUTILSSYSTEM_H

#include "DllMacro.h"

#include "Job.h"

#include <QObject>
#include <QPair>
#include <QString>

#include <chrono>

namespace CalamaresUtils
{
class ProcessResult : public QPair< int, QString >
{
public:
    enum class Code : int
    {
        Crashed = -1,  // Must match special return values from QProcess
        FailedToStart = -2,  // Must match special return values from QProcess
        NoWorkingDirectory = -3,
        TimedOut = -4
    };

    /** @brief Implicit one-argument constructor has no output, only a return code */
    ProcessResult( Code r )
        : QPair< int, QString >( static_cast< int >( r ), QString() )
    {
    }
    ProcessResult( int r, QString s )
        : QPair< int, QString >( r, s )
    {
    }

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
    static Calamares::JobResult
    explainProcess( int errorCode, const QString& command, const QString& output, std::chrono::seconds timeout );

    /// @brief Convenience wrapper for explainProcess()
    inline Calamares::JobResult explainProcess( const QString& command, std::chrono::seconds timeout ) const
    {
        return explainProcess( getExitCode(), command, getOutput(), timeout );
    }

    /// @brief Convenience wrapper for explainProcess()
    inline Calamares::JobResult explainProcess( const QStringList& command, std::chrono::seconds timeout ) const
    {
        return explainProcess( getExitCode(), command.join( ' ' ), getOutput(), timeout );
    }
};

/** @brief The result of a create*() action, for status
 *
 * A CreationResult has a status field, can be converted to bool
 * (true only on success) and can report the full pathname of
 * the thing created if it was successful.
 */
class CreationResult : public QPair< int, QString >
{
public:
    enum class Code : int
    {
        // These are "not failed", but only OK is a success
        OK = 0,
        AlreadyExists = 1,
        // These are "failed"
        Invalid = -1,
        Failed = -2
    };

    CreationResult( Code r )
        : QPair< int, QString >( static_cast< int >( r ), QString() )
    {
    }
    explicit CreationResult( const QString& path )
        : QPair< int, QString >( 0, path )
    {
    }

    Code code() const { return static_cast< Code >( first ); }
    QString path() const { return second; }

    bool failed() const { return first < 0; }
    operator bool() const { return first == 0; }
};

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
    ~System() override;

    static System* instance();

    /** (Typed) Boolean describing where a particular command should be run,
     *  whether in the host (live) system or in the (chroot) target system.
     */
    enum class RunLocation
    {
        RunInHost,
        RunInTarget
    };

    /** @brief Runs a command in the host or the target (select explicitly)
     *
     * @param location whether to run in the host or the target
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
     *             Crashed = QProcess crash
     *             FailedToStart = QProcess cannot start
     *             NoWorkingDirectory = bad arguments
     *             TimedOut = QProcess timeout
     */
    static DLLEXPORT ProcessResult runCommand( RunLocation location,
                                               const QStringList& args,
                                               const QString& workingPath = QString(),
                                               const QString& stdInput = QString(),
                                               std::chrono::seconds timeoutSec = std::chrono::seconds( 0 ) );

    /** @brief Convenience wrapper for runCommand() in the host
     *
     * Runs the given command-line @p args in the **host** in the current direcory
     * with no input, and the given @p timeoutSec for completion.
     */
    static inline ProcessResult runCommand( const QStringList& args, std::chrono::seconds timeoutSec )
    {
        return runCommand( RunLocation::RunInHost, args, QString(), QString(), timeoutSec );
    }

    /** @brief Convenience wrapper for runCommand().
     *
     * Runs the command in the location specified through the boolean
     * doChroot(), which is what you usually want for running commands
     * during installation.
     */
    inline ProcessResult targetEnvCommand( const QStringList& args,
                                           const QString& workingPath = QString(),
                                           const QString& stdInput = QString(),
                                           std::chrono::seconds timeoutSec = std::chrono::seconds( 0 ) )
    {
        return runCommand(
            m_doChroot ? RunLocation::RunInTarget : RunLocation::RunInHost, args, workingPath, stdInput, timeoutSec );
    }

    /** @brief Convenience wrapper for targetEnvCommand() which returns only the exit code */
    inline int targetEnvCall( const QStringList& args,
                              const QString& workingPath = QString(),
                              const QString& stdInput = QString(),
                              std::chrono::seconds timeoutSec = std::chrono::seconds( 0 ) )
    {
        return targetEnvCommand( args, workingPath, stdInput, timeoutSec ).first;
    }

    /** @brief Convenience wrapper for targetEnvCommand() which returns only the exit code */
    inline int targetEnvCall( const QString& command,
                              const QString& workingPath = QString(),
                              const QString& stdInput = QString(),
                              std::chrono::seconds timeoutSec = std::chrono::seconds( 0 ) )
    {
        return targetEnvCall( QStringList { command }, workingPath, stdInput, timeoutSec );
    }

    /** @brief Convenience wrapper for targetEnvCommand() which returns only the exit code
     *
     * Places the called program's output in the @p output string.
     */
    int targetEnvOutput( const QStringList& args,
                         QString& output,
                         const QString& workingPath = QString(),
                         const QString& stdInput = QString(),
                         std::chrono::seconds timeoutSec = std::chrono::seconds( 0 ) )
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
                                std::chrono::seconds timeoutSec = std::chrono::seconds( 0 ) )
    {
        return targetEnvOutput( QStringList { command }, output, workingPath, stdInput, timeoutSec );
    }


    /** @brief Gets a path to a file in the target system, from the host.
     *
     * @param path Path to the file; this is interpreted
     *      from the root of the target system (whatever that may be,
     *      but / in the chroot, or / in OEM modes).
     *
     * @return The complete path to the target file, from
     *      the root of the host system, or empty on failure.
     *
     * For instance, during installation where the target root is
     * mounted on /tmp/calamares-something, asking for targetPath("/etc/passwd")
     * will give you /tmp/calamares-something/etc/passwd.
     *
     * No attempt is made to canonicalize anything, since paths might not exist.
     */
    DLLEXPORT QString targetPath( const QString& path ) const;

    enum class WriteMode
    {
        KeepExisting,
        Overwrite
    };

    /** @brief Create a (small-ish) file in the target system.
     *
     * @param path Path to the file; this is interpreted
     *      from the root of the target system (whatever that may be,
     *      but / in the chroot, or / in OEM modes).
     * @param contents Actual content of the file.
     *
     * If the target already exists:
     *  - returns AlreadyExists as a result (and does not overwrite),
     *  - **unless** @p mode is set to Overwrite, then it tries writing as
     *    usual and will not return AlreadyExists.
     *
     * @return The complete canonical path to the target file from the
     *      root of the host system, or empty on failure. (Here, it is
     *      possible to be canonical because the file exists).
     */
    DLLEXPORT CreationResult createTargetFile( const QString& path,
                                               const QByteArray& contents,
                                               WriteMode mode = WriteMode::KeepExisting ) const;

    /** @brief Remove a file from the target system.
     *
     * @param path Path to the file; this is interpreted from the root
     *      of the target system (@see targetPath()).
     *
     * Does no error checking to see if the target file was really removed.
     */
    DLLEXPORT void removeTargetFile( const QString& path ) const;

    /** @brief Reads a file from the target system.
     *
     * @param path Path to the file; this is interpreted from the root of
     *      the target system (@see targetPath()).
     *
     * Does no error checking, and returns an empty list if the file does
     * not exist.
     *
     * NOTE: This function is now basically the same as QFile::readAll(),
     *       splitting into lines, but Calamares may need to change
     *       permissions or raise privileges to actually read the file,
     *       which is why there is an API.
     *
     * NOTE: Since this buffers the whole file in memory, reading big files
     *       is not recommended.
     */
    DLLEXPORT QStringList readTargetFile( const QString& path ) const;

    /** @brief Ensure that the directory @p path exists
     *
     * @param path a full pathname to a desired directory.
     *
     * All the directory components including the last path component are
     * created, as needed. Returns true on success.
     *
     * @see QDir::mkpath
     */
    DLLEXPORT bool createTargetDirs( const QString& path ) const;

    /** @brief Convenience to create parent directories of a file path.
     *
     * Creates all the parent directories until the last
     * component of @p filePath . @see createTargetDirs()
     */
    DLLEXPORT bool createTargetParentDirs( const QString& filePath ) const;

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
    DLLEXPORT QPair< quint64, qreal > getTotalMemoryB() const;

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

}  // namespace CalamaresUtils

#endif
