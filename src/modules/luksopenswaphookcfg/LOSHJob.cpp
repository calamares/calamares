/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *  SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
 *  SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include "CppJob.h"
#include "DllMacro.h"
#include "utils/Permissions.h"
#include "utils/PluginFactory.h"

#include <QList>
#include <QObject>
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
};

LOSHJob::LOSHJob( QObject* parent )
    : Calamares::CppJob( parent )
{
}

QString
LOSHJob::prettyName() const
{
    return tr( "Configuring encrypted swap." );
}


Calamares::JobResult
LOSHJob::exec()
{
    return Calamares::JobResult::ok();
}

void
LOSHJob::setConfigurationMap( const QVariantMap& configurationMap )
{
}

CALAMARES_PLUGIN_FACTORY_DECLARATION( LOSHJobFactory )
CALAMARES_PLUGIN_FACTORY_DEFINITION( LOSHJobFactory, registerPlugin< LOSHJob >(); )

#include "utils/moc-warnings.h"

#include "LOSHJob.moc"
