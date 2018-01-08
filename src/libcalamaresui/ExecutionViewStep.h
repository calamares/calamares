/* === This file is part of Calamares - <https://github.com/calamares> ===
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

#ifndef EXECUTIONVIEWSTEP_H
#define EXECUTIONVIEWSTEP_H

#include <viewpages/ViewStep.h>

#include <QStringList>

class QLabel;
class QProgressBar;
class QQuickWidget;

namespace Calamares
{

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

    JobList jobs() const override;

    void appendJobModuleInstanceKey( const QString& instanceKey );

private:
    QWidget* m_widget;
    QProgressBar* m_progressBar;
    QLabel* m_label;
    QQuickWidget* m_slideShow;

    QStringList m_jobInstanceKeys;

    void updateFromJobQueue( qreal percent, const QString& message );
};

}

#endif /* EXECUTIONVIEWSTEP_H */
