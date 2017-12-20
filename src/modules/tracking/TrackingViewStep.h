/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2017, Adriaan de Groot <groot@kde..org>
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

#ifndef TRACKINGVIEWSTEP_H
#define TRACKINGVIEWSTEP_H

#include "TrackingType.h"

#include <utils/PluginFactory.h>
#include <viewpages/ViewStep.h>
#include <PluginDllMacro.h>

#include <QObject>
#include <QUrl>
#include <QVariantMap>

class TrackingPage;

class PLUGINDLLEXPORT TrackingViewStep : public Calamares::ViewStep
{
    Q_OBJECT

public:
    explicit TrackingViewStep( QObject* parent = nullptr );
    virtual ~TrackingViewStep() override;

    QString prettyName() const override;

    QWidget* widget() override;

    void next() override;
    void back() override;

    bool isNextEnabled() const override;
    bool isBackEnabled() const override;

    bool isAtBeginning() const override;
    bool isAtEnd() const override;

    void onLeave() override;

    Calamares::JobList jobs() const override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;

private:
    QVariantMap setTrackingOption( const QVariantMap& configurationMap, const QString& key, TrackingType t );

    TrackingPage* m_widget;
    QString m_installTrackingUrl;
    QString m_machineTrackingStyle;

    struct TrackingEnabled
    {
        bool settingEnabled;  // Enabled in config file
        bool userEnabled;     // User checked "yes"

        TrackingEnabled()
            : settingEnabled( false )
            , userEnabled( false )
        {}

        bool enabled() const { return settingEnabled && userEnabled; }
    };
    TrackingEnabled m_installTracking, m_machineTracking, m_userTracking;

    inline TrackingEnabled& tracking( TrackingType t )
    {
        if (t == TrackingType::UserTracking)
            return m_userTracking;
        else if (t == TrackingType::MachineTracking)
            return m_machineTracking;
        else
            return m_installTracking;
    }
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( TrackingViewStepFactory )

#endif // TRACKINGVIEWSTEP_H
