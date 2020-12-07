/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef CALAMARES_VIEWMODULE_H
#define CALAMARES_VIEWMODULE_H

#include "DllMacro.h"
#include "modulesystem/Module.h"

class QPluginLoader;

namespace Calamares
{

class ViewStep;

class UIDLLEXPORT ViewModule : public Module
{
public:
    Type type() const override;
    Interface interface() const override;

    void loadSelf() override;
    JobList jobs() const override;

    RequirementsList checkRequirements() override;

protected:
    void initFrom( const ModuleSystem::Descriptor& moduleDescriptor ) override;

private:
    explicit ViewModule();
    ~ViewModule() override;

    QPluginLoader* m_loader;
    ViewStep* m_viewStep = nullptr;

    friend Module* Calamares::moduleFromDescriptor( const ModuleSystem::Descriptor& moduleDescriptor,
                                                    const QString& instanceId,
                                                    const QString& configFileName,
                                                    const QString& moduleDirectory );
};

}  // namespace Calamares

#endif  // CALAMARES_VIEWMODULE_H
