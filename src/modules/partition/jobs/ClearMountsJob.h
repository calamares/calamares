/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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

#ifndef CLEARMOUNTSJOB_H
#define CLEARMOUNTSJOB_H

#include <Job.h>

class Device;

/**
 * This job tries to free all mounts for the given device, so partitioning
 * operations can proceed.
 */
class ClearMountsJob : public Calamares::Job
{
    Q_OBJECT
public:
    explicit ClearMountsJob( Device* device );
    QString prettyName() const override;
    QString prettyStatusMessage() const override;
    Calamares::JobResult exec() override;
private:
    QString tryUmount( const QString& partPath );
    QString tryClearSwap( const QString& partPath );
    QString tryCryptoClose( const QString& mapperPath );
    QStringList getCryptoDevices() const;
    Device* m_device;
};

#endif // CLEARMOUNTSJOB_H
