/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
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

#ifndef PARTITIONVIEWSTEP_H
#define PARTITIONVIEWSTEP_H

#include "OsproberEntry.h"

#include <utils/PluginFactory.h>
#include <viewpages/ViewStep.h>

#include <PluginDllMacro.h>

#include <QObject>

class ChoicePage;
class EraseDiskPage;
class AlongsidePage;
class PartitionPage;
class ReplacePage;
class PartitionCoreModule;
class QStackedWidget;

/**
 * The starting point of the module. Instantiates PartitionCoreModule and
 * PartitionPage, then connect them.
 */
class PLUGINDLLEXPORT PartitionViewStep : public Calamares::ViewStep
{
    Q_OBJECT

public:
    explicit PartitionViewStep( QObject* parent = 0 );
    virtual ~PartitionViewStep();

    QString prettyName() const override;
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

    QList< Calamares::job_ptr > jobs() const override;

private:
    OsproberEntryList runOsprober();
    bool canBeResized( const QString& partitionPath );

    PartitionCoreModule* m_core;
    QStackedWidget*   m_widget;
    ChoicePage*       m_choicePage;
    EraseDiskPage*    m_erasePage;
    AlongsidePage*    m_alongsidePage;
    PartitionPage*    m_manualPartitionPage;
    ReplacePage*      m_replacePage;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( PartitionViewStepFactory )

#endif // PARTITIONVIEWSTEP_H
