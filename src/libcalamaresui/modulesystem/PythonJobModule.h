/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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

#ifndef CALAMARES_PYTHONJOBMODULE_H
#define CALAMARES_PYTHONJOBMODULE_H

#include "Module.h"

#include "UiDllMacro.h"

namespace Calamares {

class UIDLLEXPORT PythonJobModule : public Module
{
public:
    Type type() const override;
    Interface interface() const override;

    void loadSelf() override;
    QList< job_ptr > jobs() const override;

protected:
    void initFrom( const QVariantMap& moduleDescriptor ) override;

private:
    friend class Module;
    explicit PythonJobModule();
    virtual ~PythonJobModule() override;

    QString m_scriptFileName;
    QString m_workingPath;
    job_ptr m_job;
};

} // namespace Calamares

#endif // CALAMARES_PYTHONJOBMODULE_H
