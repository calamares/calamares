/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2020 Camilo Higuita <milo.h@aol.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef USERSQMLVIEWSTEP_H
#define USERSQMLVIEWSTEP_H

#include <QObject>

#include <utils/PluginFactory.h>
#include <viewpages/QmlViewStep.h>

#include <DllMacro.h>

#include "Config.h"
#include <QVariant>

class PLUGINDLLEXPORT UsersQmlViewStep : public Calamares::QmlViewStep
{
    Q_OBJECT

public:
    explicit UsersQmlViewStep( QObject* parent = nullptr );

    QString prettyName() const override;

    bool isNextEnabled() const override;
    bool isBackEnabled() const override;

    bool isAtBeginning() const override;
    bool isAtEnd() const override;

    QList< Calamares::job_ptr > jobs() const override;

    void onActivate() override;
    void onLeave() override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;

    QObject* getConfig() override { return m_config; }

private:
    Config* m_config;
    Calamares::JobList m_jobs;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( UsersQmlViewStepFactory )

#endif  // USERSQMLVIEWSTEP_H
