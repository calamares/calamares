/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef KEYBOARDQMLVIEWSTEP_H
#define KEYBOARDQMLVIEWSTEP_H

#include "Config.h"

#include "DllMacro.h"
#include "utils/PluginFactory.h"
#include "viewpages/QmlViewStep.h"

#include <QObject>

class PLUGINDLLEXPORT KeyboardQmlViewStep : public Calamares::QmlViewStep
{
    Q_OBJECT

public:
    explicit KeyboardQmlViewStep( QObject* parent = nullptr );

    QString prettyName() const override;
    QString prettyStatus() const override;

    bool isNextEnabled() const override;
    bool isBackEnabled() const override;

    bool isAtBeginning() const override;
    bool isAtEnd() const override;

    Calamares::JobList jobs() const override;

    void onActivate() override;
    void onLeave() override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;
    QObject* getConfig() override;

private:
    Config* m_config;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( KeyboardQmlViewStepFactory )

#endif  // KEYBOARDQMLVIEWSTEP_H
