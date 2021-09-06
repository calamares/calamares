/*
 *   SPDX-FileCopyrightText: 2016 Luca Giambonini <almack@chakraos.org>
 *   SPDX-FileCopyrightText: 2016 Lisa Vitolo     <shainer@chakraos.org>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef NETINSTALLVIEWSTEP_H
#define NETINSTALLVIEWSTEP_H

#include "Config.h"

#include "DllMacro.h"
#include "utils/PluginFactory.h"
#include "viewpages/ViewStep.h"

#include <QVariant>

class NetInstallPage;

class PLUGINDLLEXPORT NetInstallViewStep : public Calamares::ViewStep
{
    Q_OBJECT

public:
    explicit NetInstallViewStep( QObject* parent = nullptr );
    ~NetInstallViewStep() override;

    QString prettyName() const override;

    QWidget* widget() override;

    bool isNextEnabled() const override;
    bool isBackEnabled() const override;

    bool isAtBeginning() const override;
    bool isAtEnd() const override;

    Calamares::JobList jobs() const override;

    void onActivate() override;

    // Leaving the page; store all selected packages for later installation.
    void onLeave() override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;

public slots:
    void nextIsReady();

private:
    Config m_config;

    NetInstallPage* m_widget;
    bool m_nextEnabled = false;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( NetInstallViewStepFactory )

#endif  // NETINSTALLVIEWSTEP_H
