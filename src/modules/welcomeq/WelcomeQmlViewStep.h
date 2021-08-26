/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019-2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef WELCOME_QMLVIEWSTEP_H
#define WELCOME_QMLVIEWSTEP_H

#include "Config.h"

#include "modulesystem/Requirement.h"
#include "utils/PluginFactory.h"
#include "viewpages/QmlViewStep.h"

#include <DllMacro.h>

#include <QObject>
#include <QVariantMap>

namespace CalamaresUtils
{
namespace GeoIP
{
class Handler;
}
}  // namespace CalamaresUtils


// TODO: refactor and move what makes sense to base class
class PLUGINDLLEXPORT WelcomeQmlViewStep : public Calamares::QmlViewStep
{
    Q_OBJECT

public:
    explicit WelcomeQmlViewStep( QObject* parent = nullptr );

    QString prettyName() const override;

    bool isNextEnabled() const override;
    bool isBackEnabled() const override;

    bool isAtBeginning() const override;
    bool isAtEnd() const override;

    Calamares::JobList jobs() const override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;

    /** @brief Sets the country that Calamares is running in.
     *
     * This (ideally) sets up language and locale settings that are right for
     * the given 2-letter country code. Uses the handler's information (if
     * given) for error reporting.
     */
    void setCountry( const QString&, CalamaresUtils::GeoIP::Handler* handler );

    Calamares::RequirementsList checkRequirements() override;
    QObject* getConfig() override;

private:
    Config* m_config;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( WelcomeQmlViewStepFactory )

#endif  // WELCOME_QMLVIEWSTEP_H
