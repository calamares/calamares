/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2017-2018, Adriaan de Groot <groot@kde.org>
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

#ifndef PLASMAQMLLNFVIEWSTEP_H
#define PLASMAQMLLNFVIEWSTEP_H

#include <utils/PluginFactory.h>
#include <viewpages/ViewStep.h>
#include <PluginDllMacro.h>

#include <Config.h>

#include <QObject>
#include <QUrl>
#include <QVariantMap>

class PLUGINDLLEXPORT PlasmaQmlLnfViewStep : public Calamares::ViewStep
{
    Q_OBJECT
    Q_PROPERTY(Config * Config READ config CONSTANT FINAL)

public:
    explicit PlasmaQmlLnfViewStep( QObject* parent = nullptr );

    QString prettyName() const override;

    QWidget* widget() override;

    bool isNextEnabled() const override;
    bool isBackEnabled() const override;

    bool isAtBeginning() const override;
    bool isAtEnd() const override;

    void onLeave() override;

    Calamares::JobList jobs() const override;
    Config* config() const;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;

public slots:
    void themeSelected( const QString& id );

private:
    QWidget* m_widget;
    Config * m_config;
    QString m_lnfPath;  // Path to the lnf tool
    QString m_themeId;  // Id of selected theme
    QString m_liveUser; // Name of the live user (for OEM mode)
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( PlasmaQmlLnfViewStepFactory )

#endif // PLASMAQMLLNFVIEWSTEP_H
