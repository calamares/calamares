/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef SUMMARYPAGEPLUGIN_H
#define SUMMARYPAGEPLUGIN_H

#include "Config.h"

#include "DllMacro.h"
#include "utils/PluginFactory.h"
#include "viewpages/ViewStep.h"

class SummaryPage;

class PLUGINDLLEXPORT SummaryViewStep : public Calamares::ViewStep
{
    Q_OBJECT

public:
    explicit SummaryViewStep( QObject* parent = nullptr );
    ~SummaryViewStep() override;

    QString prettyName() const override;

    QWidget* widget() override;

    bool isNextEnabled() const override;
    bool isBackEnabled() const override;

    bool isAtBeginning() const override;
    bool isAtEnd() const override;

    Calamares::JobList jobs() const override;

    void onActivate() override;
    void onLeave() override;

private:
    Config* m_config = nullptr;
    SummaryPage* m_widget = nullptr;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( SummaryViewStepFactory )

#endif  // SUMMARYPAGEPLUGIN_H
