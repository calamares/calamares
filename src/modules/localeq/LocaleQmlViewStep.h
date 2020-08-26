/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019-2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef LOCALE_QMLVIEWSTEP_H
#define LOCALE_QMLVIEWSTEP_H

#include "Config.h"

#include "DllMacro.h"
#include "utils/PluginFactory.h"
#include "viewpages/QmlViewStep.h"

#include <memory>

class PLUGINDLLEXPORT LocaleQmlViewStep : public Calamares::QmlViewStep
{
    Q_OBJECT

public:
    explicit LocaleQmlViewStep( QObject* parent = nullptr );

    QString prettyName() const override;
    QString prettyStatus() const override;

    bool isNextEnabled() const override;
    bool isBackEnabled() const override;

    bool isAtBeginning() const override;
    bool isAtEnd() const override;

    virtual void onActivate() override;
    virtual void onLeave() override;

    Calamares::JobList jobs() const override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;
    QObject* getConfig() override;

private:
    std::unique_ptr< Config > m_config;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( LocaleQmlViewStepFactory )

#endif
