/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef INITRAMFSJOB_H
#define INITRAMFSJOB_H

#include "CppJob.h"
#include "DllMacro.h"
#include "utils/PluginFactory.h"

#include <QObject>
#include <QVariantMap>

class PLUGINDLLEXPORT InitramfsJob : public Calamares::CppJob
{
    Q_OBJECT

public:
    explicit InitramfsJob( QObject* parent = nullptr );
    ~InitramfsJob() override;

    QString prettyName() const override;

    Calamares::JobResult exec() override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;

private:
    QString m_kernel;
    bool m_unsafe = false;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( InitramfsJobFactory )

#endif  // INITRAMFSJOB_H
