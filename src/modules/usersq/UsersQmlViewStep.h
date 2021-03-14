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

// Config from users module
#include "Config.h"

#include "DllMacro.h"
#include "utils/PluginFactory.h"
#include "viewpages/QmlViewStep.h"

#include <QObject>
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

    Calamares::JobList jobs() const override;

    void onLeave() override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;

    QObject* getConfig() override { return m_config; }

private:
    Config* m_config;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( UsersQmlViewStepFactory )

#endif  // USERSQMLVIEWSTEP_H
