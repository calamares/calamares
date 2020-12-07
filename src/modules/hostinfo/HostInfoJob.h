/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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
    ~HostInfoJob() override;

    QString prettyName() const override;

    Calamares::JobResult exec() override;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( HostInfoJobFactory )

#endif  // HOSTINFOJOB_H
