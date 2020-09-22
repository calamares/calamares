/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2016 Kevin Kofler <kevin.kofler@chello.at>
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef CALAMARES_CPPJOB_H
#define CALAMARES_CPPJOB_H

#include "DllMacro.h"
#include "Job.h"

#include "modulesystem/InstanceKey.h"

#include <QObject>
#include <QVariant>

namespace Calamares
{

class DLLEXPORT CppJob : public Job
{
    Q_OBJECT
public:
    explicit CppJob( QObject* parent = nullptr );
    ~CppJob() override;

    void setModuleInstanceKey( const Calamares::ModuleSystem::InstanceKey& instanceKey );
    Calamares::ModuleSystem::InstanceKey moduleInstanceKey() const { return m_instanceKey; }

    virtual void setConfigurationMap( const QVariantMap& configurationMap );

protected:
    Calamares::ModuleSystem::InstanceKey m_instanceKey;
};

}  // namespace Calamares

#endif  // CALAMARES_CPPJOB_H
