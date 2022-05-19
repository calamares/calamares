/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2022 Aditya Mehra <Aix.m@outlook.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef PARTITIONQMLVIEWSTEP_H
#define PARTITIONQMLVIEWSTEP_H

#include "Config.h"

#include "DllMacro.h"
#include "utils/PluginFactory.h"
#include "viewpages/QmlViewStep.h"

#include "core/PartitionCoreModule.h"
#include "ChoicePageQml.h"

#include <QObject>
template < typename T >
class QFutureWatcher;

class PLUGINDLLEXPORT PartitionQmlViewStep : public Calamares::QmlViewStep
{
    Q_OBJECT

public:
    explicit PartitionQmlViewStep( QObject* parent = nullptr );

    QString prettyName() const override;

    bool isNextEnabled() const override;
    bool isBackEnabled() const override;

    bool isAtBeginning() const override;
    bool isAtEnd() const override;

    Calamares::JobList jobs() const override;

    void onActivate() override;
    void onLeave() override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;
    QObject* getConfig() override;
    QObject* getCore();

private:
    void initPartitionCoreModule();
    Config* m_config;
    PartitionCoreModule* m_core;
    QFutureWatcher< void >* m_future;
    ChoicePageQml* m_choicePage;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( PartitionQmlViewStepFactory )

#endif  // PARTITIONQMLVIEWSTEP_H
