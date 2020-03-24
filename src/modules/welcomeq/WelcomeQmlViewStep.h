/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019-2020 Adriaan de Groot <groot@kde.org>
 *
 *   Calamares is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Calamares is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Calamares. If not, see <http://www.gnu.org/licenses/>.
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

class GeneralRequirements;

// TODO: Needs a generic Calamares::QmlViewStep as base class
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
    // TODO: a generic QML viewstep should return a config object from a method
    Config *m_config;
    GeneralRequirements* m_requirementsChecker;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( WelcomeQmlViewStepFactory )

#endif  // WELCOME_QMLVIEWSTEP_H
