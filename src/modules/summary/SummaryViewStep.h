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

#ifndef SUMMARYPAGEPLUGIN_H
#define SUMMARYPAGEPLUGIN_H

#include <QObject>

#include "utils/PluginFactory.h"
#include "viewpages/ViewStep.h"

#include "DllMacro.h"

class SummaryPage;

class PLUGINDLLEXPORT SummaryViewStep : public Calamares::ViewStep
{
    Q_OBJECT

public:
    explicit SummaryViewStep( QObject* parent = nullptr );
    virtual ~SummaryViewStep() override;

    QString prettyName() const override;

    QWidget* widget() override;

    bool isNextEnabled() const override;
    bool isBackEnabled() const override;

    bool isAtBeginning() const override;
    bool isAtEnd() const override;

    QList< Calamares::job_ptr > jobs() const override;

    void onActivate() override;
    void onLeave() override;

private:
    SummaryPage* m_widget;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( SummaryViewStepFactory )

#endif // SUMMARYPAGEPLUGIN_H
