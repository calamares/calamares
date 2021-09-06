/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2020, Camilo Higuita <milo.h@aol.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef SUMMARYQMLVIEWSTEP_H
#define SUMMARYQMLVIEWSTEP_H

#include "Config.h"

#include "DllMacro.h"
#include "utils/PluginFactory.h"
#include "viewpages/QmlViewStep.h"

class PLUGINDLLEXPORT SummaryQmlViewStep : public Calamares::QmlViewStep
{
    Q_OBJECT

public:
    explicit SummaryQmlViewStep( QObject* parent = nullptr );
    virtual ~SummaryQmlViewStep() override;

    QString prettyName() const override;


    bool isNextEnabled() const override;
    bool isBackEnabled() const override;

    bool isAtBeginning() const override;
    bool isAtEnd() const override;

    Calamares::JobList jobs() const override;

    void onActivate() override;

    QObject* getConfig() override { return m_config; }

private:
    Config* m_config;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( SummaryQmlViewStepFactory )

#endif  // SUMMARYQMLVIEWSTEP_H
