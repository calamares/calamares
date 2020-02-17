/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2016, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2018, Adriaan de Groot <groot@kde.org>
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

#ifndef LOCALEVIEWSTEP_H
#define LOCALEVIEWSTEP_H

#include "geoip/Handler.h"
#include "geoip/Interface.h"
#include "utils/PluginFactory.h"
#include "viewpages/ViewStep.h"

#include "DllMacro.h"

#include <QFutureWatcher>
#include <QObject>

#include <memory>

class LocalePage;

class PLUGINDLLEXPORT LocaleViewStep : public Calamares::ViewStep
{
    Q_OBJECT

public:
    explicit LocaleViewStep( QObject* parent = nullptr );
    virtual ~LocaleViewStep() override;

    QString prettyName() const override;
    QString prettyStatus() const override;

    QWidget* widget() override;

    bool isNextEnabled() const override;
    bool isBackEnabled() const override;

    bool isAtBeginning() const override;
    bool isAtEnd() const override;

    Calamares::JobList jobs() const override;

    void onActivate() override;
    void onLeave() override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;

    /// @brief Do setup (returns empty list) asynchronously
    virtual Calamares::RequirementsList checkRequirements() override;

private slots:
    void setUpPage();

private:
    void fetchGeoIpTimezone();
    QWidget* m_widget;

    LocalePage* m_actualWidget;
    bool m_nextEnabled;
    QString m_prettyStatus;

    CalamaresUtils::GeoIP::RegionZonePair m_startingTimezone;
    QString m_localeGenPath;

    Calamares::JobList m_jobs;
    std::unique_ptr< CalamaresUtils::GeoIP::Handler > m_geoip;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( LocaleViewStepFactory )

#endif  // LOCALEVIEWSTEP_H
