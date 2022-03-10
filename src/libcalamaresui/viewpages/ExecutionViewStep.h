/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef EXECUTIONVIEWSTEP_H
#define EXECUTIONVIEWSTEP_H

#include "ViewStep.h"
#include "modulesystem/InstanceKey.h"
#include "widgets/LogWidget.h"

#include <QStringList>

class QLabel;
class QObject;
class QProgressBar;
class QTabWidget;

namespace Calamares
{

class Slideshow;

class ExecutionViewStep : public ViewStep
{
    Q_OBJECT
public:
    explicit ExecutionViewStep( QObject* parent = nullptr );

    QString prettyName() const override;

    QWidget* widget() override;

    void next() override;
    void back() override;

    bool isNextEnabled() const override;
    bool isBackEnabled() const override;

    bool isAtBeginning() const override;
    bool isAtEnd() const override;

    void onActivate() override;
    void onLeave() override;

    JobList jobs() const override;

    void appendJobModuleInstanceKey( const ModuleSystem::InstanceKey& instanceKey );

private:
    QWidget* m_widget;
    QProgressBar* m_progressBar;
    QLabel* m_label;
    Slideshow* m_slideshow;
    QTabWidget* m_tab_widget;
    LogWidget* m_log_widget;

    QList< ModuleSystem::InstanceKey > m_jobInstanceKeys;

    void updateFromJobQueue( qreal percent, const QString& message );

    void toggleLog();
};

}  // namespace Calamares

#endif /* EXECUTIONVIEWSTEP_H */
