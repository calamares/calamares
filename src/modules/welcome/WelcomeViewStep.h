/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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
    ~WelcomeViewStep() override;

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
    Config* m_conf;
    WelcomePage* m_widget;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( WelcomeViewStepFactory )

#endif  // WELCOMEVIEWSTEP_H
