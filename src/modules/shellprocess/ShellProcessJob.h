/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2018, Adriaan de Groot <groot@kde.org>
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

#ifndef SHELLPROCESSJOB_H
#define SHELLPROCESSJOB_H

#include "CppJob.h"
#include "PluginDllMacro.h"

#include "utils/CommandList.h"
#include "utils/PluginFactory.h"

#include <QObject>
#include <QVariantMap>

#include <memory>

class PLUGINDLLEXPORT ShellProcessJob : public Calamares::CppJob
{
    Q_OBJECT

public:
    explicit ShellProcessJob( QObject* parent = nullptr );
    virtual ~ShellProcessJob() override;

    QString prettyName() const override;

    Calamares::JobResult exec() override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;

private:
    std::unique_ptr< CalamaresUtils::CommandList > m_commands;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( ShellProcessJobFactory )

#endif  // SHELLPROCESSJOB_H
