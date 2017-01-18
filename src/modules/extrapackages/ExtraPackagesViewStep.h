/*******************************************************************************
 * Copyright (c) 2016-2017, Kyle Robbertze (AIMS, South Africa)
 *
 * This project is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * It is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this project. If not, see <http://www.gnu.org/licenses/>.
 *
 *    Description:  Module for installing select packages in the installed
 *                  system
 *
 *        Created:  06/12/2016 06:46:56
 *       Compiler:  g++
 *
 *         Author:  Kyle Robbertze (kr), kyle@aims.ac.za
 *******************************************************************************/

#ifndef EXTRAPACKAGESPLUGIN_H
#define EXTRAPACKAGESPLUGIN_H

#include "PluginDllMacro.h"
#include "utils/PluginFactory.h"
#include "viewpages/ViewStep.h"

#include <QObject>
#include <QVariantMap>

class ExtraPackagesPage;

class PLUGINDLLEXPORT ExtraPackagesViewStep : public Calamares::ViewStep
{
    Q_OBJECT

public:
    explicit ExtraPackagesViewStep( QObject* parent = nullptr );
    virtual ~ExtraPackagesViewStep();

    QString prettyName() const override;
    QString prettyStatus() const override;

    QWidget* widget() override;

    void next() override;
    void back() override;

    bool isNextEnabled() const override;
    bool isBackEnabled() const override;

    bool isAtBeginning() const override;
    bool isAtEnd() const override;

    void onActivate() override;
    void onLeave() override;

    QList<Calamares::job_ptr> jobs() const override;
    void setConfigurationMap( const QVariantMap& configurationMap ) override;

private:
    ExtraPackagesPage* m_widget;
    QList<Calamares::job_ptr> m_jobs;
    QVariantList m_sources;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( ExtraPackagesViewStepFactory );

#endif // EXTRAPACKAGESPLUGIN_H
