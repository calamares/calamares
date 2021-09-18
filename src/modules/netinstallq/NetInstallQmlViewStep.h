/*
 *   SPDX-FileCopyrightText: 2016 Luca Giambonini <almack@chakraos.org>
 *   SPDX-FileCopyrightText: 2016 Lisa Vitolo     <shainer@chakraos.org>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2021 shivanandvp <shivanandvp@rebornos.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef NETINSTALLQMLVIEWSTEP_H
#define NETINSTALLQMLVIEWSTEP_H

#include "Config.h"

#include "DllMacro.h"
#include "locale/TranslatableConfiguration.h"
#include "utils/PluginFactory.h"
#include "viewpages/QmlViewStep.h"

#include <QVariant>
#include <QVariantMap>

class Config;
class NetInstallPage;

class PLUGINDLLEXPORT NetInstallQmlViewStep : public Calamares::QmlViewStep
{
    Q_OBJECT

public:
    explicit NetInstallQmlViewStep( QObject* parent = nullptr );

    void onActivate() override;

    QString prettyName() const override;
    QString prettyStatus() const override;

    bool isNextEnabled() const override;
    bool isBackEnabled() const override;

    bool isAtBeginning() const override;
    bool isAtEnd() const override;

    // Leaving the page; store all selected packages for later installation.
    void onLeave() override;    
  
    Calamares::JobList jobs() const override; 

    void setConfigurationMap( const QVariantMap& configurationMap ) override;

public slots:
    void nextIsReady();

private:
    Config m_config;
    CalamaresUtils::Locale::TranslatedString* m_stepName; 
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( NetInstallQmlViewStepFactory )

#endif  // NETINSTALLQMLVIEWSTEP_H
