/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
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

#include <QObject>

#include "viewpages/ViewStep.h"
#include "PluginDllMacro.h"

class ChoicePage;
class EraseDiskPage;
class AlongsidePage;
class PartitionPage;
class PartitionCoreModule;
class QStackedWidget;

/**
 * The starting point of the module. Instantiates PartitionCoreModule and
 * PartitionPage, then connect them.
 */
class PLUGINDLLEXPORT PartitionViewStep : public Calamares::ViewStep
{
    Q_OBJECT
    Q_PLUGIN_METADATA( IID "calamares.ViewModule/1.0" )
    Q_INTERFACES( Calamares::ViewStep )

public:
    explicit PartitionViewStep( QObject* parent = 0 );
    virtual ~PartitionViewStep();

    QString prettyName() const override;
    QWidget* createSummaryWidget() const override;

    QWidget* widget() override;

    void next() override;
    void back() override;

    bool isNextEnabled() const override;

    bool isAtBeginning() const override;
    bool isAtEnd() const override;

    QList< Calamares::job_ptr > jobs() const override;

private:
    bool canBeResized( const QString& partitionPath );

    PartitionCoreModule* m_core;
    QStackedWidget*   m_widget;
    ChoicePage*       m_choicePage;
    EraseDiskPage*    m_erasePage;
    AlongsidePage*    m_alongsidePage;
    PartitionPage*    m_manualPartitionPage;
};

#endif // PARTITIONVIEWSTEP_H
