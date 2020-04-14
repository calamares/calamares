/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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

#ifndef WELCOMEVIEWSTEP_H
#define WELCOMEVIEWSTEP_H


#include "DllMacro.h"
#include "modulesystem/Requirement.h"
#include "utils/PluginFactory.h"
#include "viewpages/ViewStep.h"

#include <QObject>
#include <QVariantMap>

class WelcomePage;
class GeneralRequirements;
class Config;

namespace CalamaresUtils
{
namespace GeoIP
{
class Handler;
}
}  // namespace CalamaresUtils

class PLUGINDLLEXPORT WelcomeViewStep : public Calamares::ViewStep
{
    Q_OBJECT

public:
    explicit WelcomeViewStep( QObject* parent = nullptr );
    virtual ~WelcomeViewStep() override;

    QString prettyName() const override;

    QWidget* widget() override;

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

private:
    WelcomePage* m_widget;
    GeneralRequirements* m_requirementsChecker;
    Config* m_conf;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( WelcomeViewStepFactory )

#endif  // WELCOMEVIEWSTEP_H
