/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef CALAMARES_PYTHONQTVIEWMODULE_H
#define CALAMARES_PYTHONQTVIEWMODULE_H

#include "DllMacro.h"
#include "Module.h"

namespace Calamares
{

class ViewStep;

class UIDLLEXPORT PythonQtViewModule : public Module
{
public:
    Type type() const override;
    Interface interface() const override;

    void loadSelf() override;
    JobList jobs() const override;

protected:
    void initFrom( const QVariantMap& moduleDescriptor ) override;

private:
    explicit PythonQtViewModule();
    virtual ~PythonQtViewModule();

    ViewStep* m_viewStep = nullptr;

    QString m_scriptFileName;
    QString m_workingPath;

    friend Module* Calamares::moduleFromDescriptor( const ModuleSystem::Descriptor& moduleDescriptor,
                                                    const QString& instanceId,
                                                    const QString& configFileName,
                                                    const QString& moduleDirectory );
};

}  // namespace Calamares

#endif  // CALAMARES_PYTHONQTVIEWMODULE_H
