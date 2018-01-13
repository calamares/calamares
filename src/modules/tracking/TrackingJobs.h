/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2017, Adriaan de Groot <groot@kde..org>
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

#ifndef TRACKINGJOBS
#define TRACKINGJOBS

#include "Job.h"

class QNetworkAccessManager;
class QNetworkReply;
class QSemaphore;

class TrackingInstallJob : public Calamares::Job
{
    Q_OBJECT
public:
    TrackingInstallJob( const QString& url );
    ~TrackingInstallJob() override;

    QString prettyName() const override;
    QString prettyDescription() const override;
    QString prettyStatusMessage() const override;
    Calamares::JobResult exec() override;

public slots:
    void dataIsHere( QNetworkReply* );

private:
    const QString m_url;

    QNetworkAccessManager* m_networkManager;
};

class TrackingMachineNeonJob : public Calamares::Job
{
    Q_OBJECT
public:
    QString prettyName() const override;
    QString prettyDescription() const override;
    QString prettyStatusMessage() const override;
    Calamares::JobResult exec() override;
};


#endif
