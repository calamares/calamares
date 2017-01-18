/*******************************************************************************
 * Copyright (c) 2016-2017, Kyle Robbertze (AIMS, South Africa)
 *
 * This project is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * It is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this project. If not, see <http://www.gnu.org/licenses/>.
 *
 *    Description:  Module for installing select packages in the installed
 *                  system.
 *
 *        Created:  08/12/2016 12:39:47
 *       Compiler:  g++
 *
 *         Author:  Kyle Robbertze (kr), kyle@aims.ac.za
 *******************************************************************************/

#ifndef INSTALLPACKAGEJOB_H
#define INSTALLPACKAGEJOB_H

#include <Job.h>

enum InstallJobProgress
{
    PRE_SCRIPT,
    INSTALL,
    POST_SCRIPT
};

class InstallPackageJob : public Calamares::Job
{
    Q_OBJECT
public:
    InstallPackageJob( const QString& name, const QString& preScript, const QString& postScript );
    QString prettyName() const override;
    QString prettyDescription() const override;
    QString prettyStatusMessage() const override;
    Calamares::JobResult exec() override;
private:
    QString m_name;
    QString m_preScript;
    QString m_postScript;
    InstallJobProgress m_jobProgress;
};
#endif //INSTALLPACKAGEJOB_H
