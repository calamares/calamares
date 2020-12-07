/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2016 Kevin Kofler <kevin.kofler@chello.at>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef DUMMYCPPJOB_H
#define DUMMYCPPJOB_H

#include <QObject>
#include <QVariantMap>

#include "CppJob.h"

#include "utils/PluginFactory.h"

#include "DllMacro.h"

class PLUGINDLLEXPORT DummyCppJob : public Calamares::CppJob
{
    Q_OBJECT

public:
    explicit DummyCppJob( QObject* parent = nullptr );
    ~DummyCppJob() override;

    QString prettyName() const override;

    Calamares::JobResult exec() override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;

private:
    QVariantMap m_configurationMap;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( DummyCppJobFactory )

#endif  // DUMMYCPPJOB_H
