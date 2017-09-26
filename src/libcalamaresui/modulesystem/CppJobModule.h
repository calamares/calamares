/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2016, Kevin Kofler <kevin.kofler@chello.at>
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
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

#ifndef CALAMARES_CPPJOBMODULE_H
#define CALAMARES_CPPJOBMODULE_H

#include "UiDllMacro.h"
#include "Module.h"

class QPluginLoader;

namespace Calamares
{

class UIDLLEXPORT CppJobModule : public Module
{
public:
    Type type() const override;
    Interface interface() const override;

    void loadSelf() override;
    QList< job_ptr > jobs() const override;

protected:
    void initFrom( const QVariantMap& moduleDescriptor ) override;

private:
    friend class Module; //so only the superclass can instantiate
    explicit CppJobModule();
    virtual ~CppJobModule() override;

    QPluginLoader* m_loader;
    job_ptr m_job;
};

} // namespace Calamares

#endif // CALAMARES_CPPJOBMODULE_H
