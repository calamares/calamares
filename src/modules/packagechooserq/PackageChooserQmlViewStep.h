/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2021 Anke Boersma <demm@kaosx.us>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef PACKAGECHOOSERQMLVIEWSTEP_H
#define PACKAGECHOOSERQMLVIEWSTEP_H

// Config from packagechooser module
#include "Config.h"

#include "DllMacro.h"
#include "locale/TranslatableConfiguration.h"
#include "utils/PluginFactory.h"
#include "viewpages/QmlViewStep.h"

#include <QVariantMap>

class Config;
class PackageChooserPage;

class PLUGINDLLEXPORT PackageChooserQmlViewStep : public Calamares::QmlViewStep
{
    Q_OBJECT

public:
    explicit PackageChooserQmlViewStep( QObject* parent = nullptr );

    QString prettyName() const override;
    QString prettyStatus() const override;

    bool isNextEnabled() const override;
    bool isBackEnabled() const override;

    bool isAtBeginning() const override;
    bool isAtEnd() const override;

    //void onActivate() override;
    void onLeave() override;

    Calamares::JobList jobs() const override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;

    QObject* getConfig() override { return m_config; }

private:
    Config* m_config;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( PackageChooserQmlViewStepFactory )

#endif  // PACKAGECHOOSERQMLVIEWSTEP_H
