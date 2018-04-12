/* === This file is part of Calamares - <http://github.com/calamares> ===
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

#ifndef PLASMALNFVIEWSTEP_H
#define PLASMALNFVIEWSTEP_H

#include <utils/PluginFactory.h>
#include <viewpages/ViewStep.h>
#include <PluginDllMacro.h>

#include <QObject>
#include <QUrl>
#include <QVariantMap>

class PlasmaLnfPage;

class PLUGINDLLEXPORT PlasmaLnfViewStep : public Calamares::ViewStep
{
    Q_OBJECT

public:
    explicit PlasmaLnfViewStep( QObject* parent = nullptr );
    virtual ~PlasmaLnfViewStep() override;

    QString prettyName() const override;

    QWidget* widget() override;

    void next() override;
    void back() override;

    bool isNextEnabled() const override;
    bool isBackEnabled() const override;

    bool isAtBeginning() const override;
    bool isAtEnd() const override;

    void onLeave() override;

    QList<Calamares::job_ptr> jobs() const override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;

public slots:
    void themeSelected( const QString& id );

private:
    PlasmaLnfPage* m_widget;
    QString m_lnfPath;  // Path to the lnf tool
    QString m_themeId;  // Id of selected theme
    QString m_liveUser; // Name of the live user (for OEM mode)
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( PlasmaLnfViewStepFactory )

#endif // PLASMALNFVIEWSTEP_H
