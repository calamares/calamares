/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef INITCPIOJOB_H
#define INITCPIOJOB_H

#include "CppJob.h"
#include "DllMacro.h"
#include "utils/PluginFactory.h"

#include <QObject>
#include <QVariantMap>

class PLUGINDLLEXPORT InitcpioJob : public Calamares::CppJob
{
    Q_OBJECT

public:
    explicit InitcpioJob( QObject* parent = nullptr );
    ~InitcpioJob() override;

    QString prettyName() const override;

    Calamares::JobResult exec() override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;

private:
    QString m_kernel;
    bool m_unsafe = false;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( InitcpioJobFactory )

#endif  // INITCPIOJOB_H
