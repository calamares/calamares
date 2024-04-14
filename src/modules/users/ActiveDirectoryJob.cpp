/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2024 Simon Quigley <tsimonq2@ubuntu.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "ActiveDirectoryJob.h"

#include "Config.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/Logger.h"
#include "utils/Permissions.h"
#include "utils/System.h"

#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QProcess>
#include <QTextStream>

ActiveDirectoryJob::ActiveDirectoryJob( const QString& adminLogin,
                                        const QString& adminPassword,
                                        const QString& domain,
                                        const QString& ip )
    : Calamares::Job()
    , m_adminLogin( adminLogin )
    , m_adminPassword( adminPassword )
    , m_domain( domain )
    , m_ip( ip )
{
}

QString
ActiveDirectoryJob::prettyName() const
{
    return tr( "Enroll system in Active Directory", "@label" );
}

QString
ActiveDirectoryJob::prettyStatusMessage() const
{
    return tr( "Enrolling system in Active Directory…", "@status" );
}

Calamares::JobResult
ActiveDirectoryJob::exec()
{
    if ( !m_ip.isEmpty() )
    {
        const QString hostsFilePath = Calamares::System::instance()->targetPath( QStringLiteral( "/etc/hosts" ) );
        ;
        QFile hostsFile( hostsFilePath );
        if ( hostsFile.open( QIODevice::Append | QIODevice::Text ) )
        {
            QTextStream out( &hostsFile );
            out << m_ip << " " << m_domain << "\n";
            hostsFile.close();
        }
        else
        {
            return Calamares::JobResult::error( "Failed to open /etc/hosts for writing." );
        }
    }

    const QString installPath = Calamares::System::instance()->targetPath( QStringLiteral( "/" ) );
    QStringList args = { "join", m_domain, "-U", m_adminLogin, "--install=" + installPath, "--verbose" };

    QProcess process;
    process.start( "realm", args );
    process.waitForStarted();

    if ( !m_adminPassword.isEmpty() )
    {
        process.write( ( m_adminPassword + "\n" ).toUtf8() );
        process.closeWriteChannel();
    }

    process.waitForFinished( -1 );

    if ( process.exitCode() == 0 )
    {
        return Calamares::JobResult::ok();
    }
    else
    {
        QString errorOutput = process.readAllStandardError();
        return Calamares::JobResult::error( QString( "Failed to join realm: %1" ).arg( errorOutput ) );
    }
}
