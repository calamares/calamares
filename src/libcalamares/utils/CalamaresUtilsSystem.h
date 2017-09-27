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
#ifndef CALAMARESUTILSSYSTEM_H
#define CALAMARESUTILSSYSTEM_H

#include "DllMacro.h"

#include <QObject>
#include <QString>

namespace CalamaresUtils
{

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

    /**
      * Runs the specified command in the chroot of the target system.
      * @param args the call with arguments, as a string list.
      * @param workingPath the current working directory for the QProcess
      * call (optional).
      * @param stdInput the input string to send to the running process as
      * standard input (optional).
      * @param timeoutSec the timeout after which the process will be
      * killed (optional, default is 0 i.e. no timeout).
      * @returns the program's exit code, or:
      *             -1 = QProcess crash
      *             -2 = QProcess cannot start
      *             -3 = bad arguments
      *             -4 = QProcess timeout
      */
    DLLEXPORT int targetEnvCall( const QStringList& args,
                              const QString& workingPath = QString(),
                              const QString& stdInput = QString(),
                              int timeoutSec = 0 );

    DLLEXPORT int targetEnvCall( const QString& command,
                              const QString& workingPath = QString(),
                              const QString& stdInput = QString(),
                              int timeoutSec = 0 );

    DLLEXPORT int targetEnvOutput( const QStringList& args,
                                QString& output,
                                const QString& workingPath = QString(),
                                const QString& stdInput = QString(),
                                int timeoutSec = 0 );

    DLLEXPORT int targetEnvOutput( const QString& command,
                                QString& output,
                                const QString& workingPath = QString(),
                                const QString& stdInput = QString(),
                                int timeoutSec = 0 );

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
    DLLEXPORT QPair<quint64, float> getTotalMemoryB();

private:
    static System* s_instance;

    bool m_doChroot;
};

}

#endif // CALAMARESUTILSSYSTEM_H
