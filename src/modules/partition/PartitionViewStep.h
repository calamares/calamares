/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2014-2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef PARTITIONVIEWSTEP_H
#define PARTITIONVIEWSTEP_H

#include "utils/PluginFactory.h"
#include "viewpages/ViewStep.h"

#include "DllMacro.h"

#include <QObject>
#include <QSet>

class ChoicePage;
class Config;
class PartitionPage;
class PartitionCoreModule;
class QStackedWidget;
class WaitingWidget;

template < typename T >
class QFutureWatcher;

/**
 * The starting point of the module. Instantiates PartitionCoreModule,
 * ChoicePage and PartitionPage, then connects them.
 */
class PLUGINDLLEXPORT PartitionViewStep : public Calamares::ViewStep
{
    Q_OBJECT

public:
    explicit PartitionViewStep( QObject* parent = nullptr );
    ~PartitionViewStep() override;

    QString prettyName() const override;
    QString prettyStatus() const override;
    QWidget* createSummaryWidget() const override;

    QWidget* widget() override;

    void next() override;
    void back() override;

    bool isNextEnabled() const override;
    bool isBackEnabled() const override;

    bool isAtBeginning() const override;
    bool isAtEnd() const override;

    void onActivate() override;
    void onLeave() override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;

    Calamares::JobList jobs() const override;

    Calamares::RequirementsList checkRequirements() override;

private:
    void initPartitionCoreModule();
    void continueLoading();

    /// "slot" for changes to next-status from the KPMCore and ChoicePage
    void nextPossiblyChanged( bool );

    Config* m_config;

    PartitionCoreModule* m_core;
    QStackedWidget* m_widget;
    ChoicePage* m_choicePage;
    PartitionPage* m_manualPartitionPage;

    WaitingWidget* m_waitingWidget;
    QFutureWatcher< void >* m_future;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( PartitionViewStepFactory )

#endif  // PARTITIONVIEWSTEP_H
