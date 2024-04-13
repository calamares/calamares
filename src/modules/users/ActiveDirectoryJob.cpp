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
#include <QTextStream>
#include <QProcess>

ActiveDirectoryJob::ActiveDirectoryJob(QStringList& activeDirectoryInfo)
    : Calamares::Job()
    , m_activeDirectoryInfo(activeDirectoryInfo)
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
    QString username = m_activeDirectoryInfo.value(0);
    QString password = m_activeDirectoryInfo.value(1);
    QString domain = m_activeDirectoryInfo.value(2);
    QString ip = m_activeDirectoryInfo.value(3);

    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
    QString rootMountPoint = gs ? gs->value("rootMountPoint").toString() : QString();

    if (!ip.isEmpty()) {
        QString hostsFilePath = !rootMountPoint.isEmpty() ? rootMountPoint + "/etc/hosts" : "/etc/hosts";
        QFile hostsFile(hostsFilePath);
        if (hostsFile.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&hostsFile);
            out << ip << " " << domain << "\n";
            hostsFile.close();
        } else {
            return Calamares::JobResult::error("Failed to open /etc/hosts for writing.");
        }
    }

    QString installPath = !rootMountPoint.isEmpty() ? rootMountPoint : "/";
    QStringList args = {"join", domain, "-U", username, "--install=" + installPath, "--verbose"};

    QProcess process;
    process.start("realm", args);
    process.waitForStarted();

    if (!password.isEmpty()) {
        process.write((password + "\n").toUtf8());
        process.closeWriteChannel();
    }

    process.waitForFinished(-1);

    if (process.exitCode() == 0) {
        return Calamares::JobResult::ok();
    } else {
        QString errorOutput = process.readAllStandardError();
        return Calamares::JobResult::error(QString("Failed to join realm: %1").arg(errorOutput));
    }
}
