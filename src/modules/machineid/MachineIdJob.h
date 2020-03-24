/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019, Adriaan de Groot <groot@kde.org>
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

#ifndef MACHINEIDJOB_H
#define MACHINEIDJOB_H

#include <QObject>
#include <QVariantMap>

#include "CppJob.h"

#include "utils/PluginFactory.h"

#include "DllMacro.h"

class PLUGINDLLEXPORT MachineIdJob : public Calamares::CppJob
{
    Q_OBJECT

public:
    explicit MachineIdJob( QObject* parent = nullptr );
    virtual ~MachineIdJob() override;

    QString prettyName() const override;

    Calamares::JobResult exec() override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;

private:
    bool m_systemd = false;  ///< write systemd's files

    bool m_dbus = false;  ///< write dbus files
    bool m_dbus_symlink = false;  ///< .. or just symlink to systemd

    bool m_entropy = false;  ///< write an entropy file
    bool m_entropy_copy = false;  ///< copy from host system
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( MachineIdJobFactory )

#endif  // MACHINEIDJOB_H
