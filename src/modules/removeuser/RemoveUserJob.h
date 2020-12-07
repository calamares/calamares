/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef REMOVEUSERJOB_H
#define REMOVEUSERJOB_H

#include "CppJob.h"
#include "DllMacro.h"
#include "utils/PluginFactory.h"

#include <QObject>
#include <QVariantMap>

class PLUGINDLLEXPORT RemoveUserJob : public Calamares::CppJob
{
    Q_OBJECT

public:
    explicit RemoveUserJob( QObject* parent = nullptr );
    ~RemoveUserJob() override;

    QString prettyName() const override;

    Calamares::JobResult exec() override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;

private:
    QString m_username;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( RemoveUserJobFactory )

#endif  // REMOVEUSERJOB_H
