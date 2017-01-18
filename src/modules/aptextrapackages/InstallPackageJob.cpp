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
 *                  system
 *
 *        Created:  08/12/2016 13:30:17
 *       Compiler:  g++
 *
 *         Author:  Kyle Robbertze (kr), kyle@aims.ac.za
 *******************************************************************************/

#include "InstallPackageJob.h"

#include "utils/CalamaresUtilsSystem.h"

InstallPackageJob::InstallPackageJob( const QString& name, const QString& preScript, const QString& postScript ) :
    Calamares::Job(),
    m_name( name ),
    m_preScript( preScript ),
    m_postScript( postScript ),
    m_jobProgress( InstallJobProgress::PRE_SCRIPT )
{ }

QString
InstallPackageJob::prettyName() const
{
    return tr( "Install package %1" ).arg( m_name );
}

QString
InstallPackageJob::prettyDescription() const
{
    return tr( "Install package <strong>%1</strong>" ).arg( m_name );
}

QString
InstallPackageJob::prettyStatusMessage() const
{
    switch ( m_jobProgress )
    {
    case InstallJobProgress::PRE_SCRIPT:
        return tr( "Running pre-script %1" ).arg( m_preScript );
    case InstallJobProgress::POST_SCRIPT:
        return tr( "Running post-script %1" ).arg( m_postScript );
    default:
        return tr( "Installing package %1" ).arg( m_name );
    }
}

Calamares::JobResult
InstallPackageJob::exec()
{
    if ( m_preScript != "" )
    {
        m_jobProgress = InstallJobProgress::PRE_SCRIPT;
        int result = CalamaresUtils::System::instance()->
                     targetEnvCall( m_preScript.split( " ", QString::SkipEmptyParts ) );
        if ( result )
            return Calamares::JobResult::error( tr( "Pre-script %1 failed." ).arg( m_preScript ),
                                                tr( "Script terminated with error code %1." ).arg( result ) );
    }
    m_jobProgress = InstallJobProgress::INSTALL;
    int result = CalamaresUtils::System::instance()->
                 targetEnvCall( {"apt",
                                 "--allow-insecure-repositories", // File deb source on the installer is not signed
                                 "install",
                                 "-y",
                                 m_name
                                } );
    if ( result )
        return Calamares::JobResult::error( tr( "Unable to install package %1." ).arg( m_name ),
                                            tr( "apt terminated with error code %1." ).arg( result ) );
    if ( m_postScript != "" )
    {
        m_jobProgress = InstallJobProgress::POST_SCRIPT;
        result = CalamaresUtils::System::instance()->
                 targetEnvCall( m_postScript.split( " ", QString::SkipEmptyParts ) );
        if ( result )
            return Calamares::JobResult::error( tr( "Post-script %1 failed." ).arg( m_postScript ),
                                                tr( "Script terminated with error code %1." ).arg( result ) );
    }
    return Calamares::JobResult::ok();
}
