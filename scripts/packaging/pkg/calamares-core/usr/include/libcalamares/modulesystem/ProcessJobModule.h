/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef CALAMARES_PROCESSJOBMODULE_H
#define CALAMARES_PROCESSJOBMODULE_H

#include "DllMacro.h"
#include "modulesystem/Module.h"

#include <chrono>

namespace Calamares
{

class UIDLLEXPORT ProcessJobModule : public Module
{
public:
    Type type() const override;
    Interface interface() const override;

    void loadSelf() override;
    JobList jobs() const override;

protected:
    void initFrom( const ModuleSystem::Descriptor& moduleDescriptor ) override;

private:
    explicit ProcessJobModule();
    ~ProcessJobModule() override;

    QString m_command;
    QString m_workingPath;
    std::chrono::seconds m_secondsTimeout;
    bool m_runInChroot;
    job_ptr m_job;

    friend Module* Calamares::moduleFromDescriptor( const ModuleSystem::Descriptor& moduleDescriptor,
                                                    const QString& instanceId,
                                                    const QString& configFileName,
                                                    const QString& moduleDirectory );
};

}  // namespace Calamares

#endif  // CALAMARES_PROCESSJOBMODULE_H
