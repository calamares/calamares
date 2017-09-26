/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2015, Anke Boersma <demm@kaosx.us>
 *   Copyright 2015, Teo Mrnjavac <teo@kde.org>
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

#ifndef LICENSEPAGEPLUGIN_H
#define LICENSEPAGEPLUGIN_H

#include <utils/PluginFactory.h>
#include <viewpages/ViewStep.h>
#include <PluginDllMacro.h>

#include <QObject>
#include <QUrl>
#include <QVariantMap>

class LicensePage;

class PLUGINDLLEXPORT LicenseViewStep : public Calamares::ViewStep
{
    Q_OBJECT

public:
    explicit LicenseViewStep( QObject* parent = nullptr );
    virtual ~LicenseViewStep() override;

    QString prettyName() const override;

    QWidget* widget() override;

    void next() override;
    void back() override;

    bool isNextEnabled() const override;
    bool isBackEnabled() const override;

    bool isAtBeginning() const override;
    bool isAtEnd() const override;

    QList< Calamares::job_ptr > jobs() const override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;

private:
    LicensePage* m_widget;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( LicenseViewStepFactory )

#endif // LICENSEPAGEPLUGIN_H
