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

class DLLEXPORT System : public QObject
{
    Q_OBJECT
public:
    explicit System( bool doChroot, QObject* parent = nullptr );
    virtual ~System();

    static System* instance();

    /**
      * Runs the mount utility with the specified parameters.
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

    DLLEXPORT qint64 getPhysicalMemoryB();  //Better guess, doesn't work in VirualBox

    DLLEXPORT qint64 getTotalMemoryB();     //Always underguessed, but always works on Linux

private:
    static System* s_instance;

    bool m_doChroot;
};

}

#endif // CALAMARESUTILSSYSTEM_H
