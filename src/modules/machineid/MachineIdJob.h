/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef MACHINEIDJOB_H
#define MACHINEIDJOB_H

#include "Workers.h"

#include "CppJob.h"
#include "DllMacro.h"
#include "utils/PluginFactory.h"

#include <QObject>
#include <QStringList>
#include <QVariantMap>

/** @brief Write 'random' data: machine id, entropy, UUIDs
 *
 */
class PLUGINDLLEXPORT MachineIdJob : public Calamares::CppJob
{
    Q_OBJECT

public:
    explicit MachineIdJob( QObject* parent = nullptr );
    ~MachineIdJob() override;

    QString prettyName() const override;

    Calamares::JobResult exec() override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;

    /** @brief The list of filenames to write full of entropy.
     *
     * The list may be empty (no entropy files are configure) or
     * contain one or more filenames to be interpreted within the
     * target system.
     */
    QStringList entropyFileNames() const { return m_entropy_files; }

private:
    bool m_systemd = false;  ///< write systemd's files

    MachineId::SystemdMachineIdStyle m_systemd_style = MachineId::SystemdMachineIdStyle::Uuid;

    bool m_dbus = false;  ///< write dbus files
    bool m_dbus_symlink = false;  ///< .. or just symlink to systemd

    bool m_entropy_copy = false;  ///< copy from host system
    QStringList m_entropy_files;  ///< names of files to write
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( MachineIdJobFactory )

#endif  // MACHINEIDJOB_H
