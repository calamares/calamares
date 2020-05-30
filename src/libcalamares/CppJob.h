/* === This file is part of Calamares - <https://github.com/calamares> ===
 * 
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2016 Kevin Kofler <kevin.kofler@chello.at>
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
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
 *
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *   License-Filename: LICENSE
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
    virtual ~CppJob();

    void setModuleInstanceKey( const Calamares::ModuleSystem::InstanceKey& instanceKey );
    Calamares::ModuleSystem::InstanceKey moduleInstanceKey() const { return m_instanceKey; }

    virtual void setConfigurationMap( const QVariantMap& configurationMap );

protected:
    Calamares::ModuleSystem::InstanceKey m_instanceKey;
};

}  // namespace Calamares

#endif  // CALAMARES_CPPJOB_H
