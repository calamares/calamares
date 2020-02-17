/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019, Adriaan de Groot <groot@kde.org>
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

#ifndef HOSTINFOJOB_H
#define HOSTINFOJOB_H

#include "CppJob.h"
#include "DllMacro.h"
#include "utils/PluginFactory.h"

#include <QObject>
#include <QVariantMap>

/** @brief the compile-time host OS
 *
 * Returns "FreeBSD" or "Linux" or empty.
 */
QString hostOS();

/** @brief the run-time host OS
 *
 * Returns os-release NAME information, or if that is blank or not available,
 * the same as hostOS().
 */
QString hostOSName();

/** @brief the run-time CPU architecture
 *
 * Returns "Intel" or "AMD" or blank, if Calamares can determine what
 * CPU is currently in use (based on /proc/cpuinfo or hw.model).
 */
QString hostCPU();

class PLUGINDLLEXPORT HostInfoJob : public Calamares::CppJob
{
    Q_OBJECT

public:
    explicit HostInfoJob( QObject* parent = nullptr );
    virtual ~HostInfoJob() override;

    QString prettyName() const override;

    Calamares::JobResult exec() override;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( HostInfoJobFactory )

#endif  // HOSTINFOJOB_H
