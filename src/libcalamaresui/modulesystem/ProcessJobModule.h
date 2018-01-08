/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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

#ifndef CALAMARES_PROCESSJOBMODULE_H
#define CALAMARES_PROCESSJOBMODULE_H

#include "Module.h"

#include "UiDllMacro.h"

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
    void initFrom( const QVariantMap& moduleDescriptor ) override;

private:
    friend class Module;
    explicit ProcessJobModule();
    virtual ~ProcessJobModule() override;

    QString m_command;
    QString m_workingPath;
    int m_secondsTimeout;
    bool m_runInChroot;
    job_ptr m_job;
};

} // namespace Calamares

#endif // CALAMARES_PROCESSJOBMODULE_H
