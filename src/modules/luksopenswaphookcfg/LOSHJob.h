/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *  SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
 *  SPDX-License-Identifier: GPL-3.0-or-later
 *
 */
#ifndef LUKSOPENSWAPHOOKCFG_LOSHJOB_H
#define LUKSOPENSWAPHOOKCFG_LOSHJOB_H

#include "CppJob.h"
#include "DllMacro.h"
#include "utils/PluginFactory.h"

#include <QString>
#include <QVariantMap>

class PLUGINDLLEXPORT LOSHJob : public Calamares::CppJob
{
    Q_OBJECT

public:
    explicit LOSHJob( QObject* parent = nullptr );
    ~LOSHJob() override;

    QString prettyName() const override;

    Calamares::JobResult exec() override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;

private:
    QString m_configFilePath;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( LOSHJobFactory )

#endif
