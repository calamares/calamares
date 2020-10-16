/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2017, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
 *   Copyright 2017, Gabriel Craciunescu <crazy@frugalware.org>
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

/* Based on code extracted from RequirementsChecker.cpp */

#ifndef CHECKERCONTAINER_H
#define CHECKERCONTAINER_H

#include "Config.h"
#include <QWidget>

class ResultsListWidget;
class WaitingWidget;

/**
 * A widget that collects requirements results; until the results are
 * all in, displays a spinner / waiting widget. Then it switches to
 * a (list) diplay of the results, plus some explanation of the
 * overall state of the entire list of results.
 */

class CheckerContainer : public QWidget
{
    Q_OBJECT
public:
    explicit CheckerContainer( const Calamares::RequirementsModel& model, QWidget* parent = nullptr );
    virtual ~CheckerContainer();

    bool verdict() const;

public slots:
    /** @brief All the requirements are complete, switch to list view */
    void requirementsComplete( bool );

    void requirementsProgress( const QString& message );

protected:
    WaitingWidget* m_waitingWidget;
    ResultsListWidget* m_checkerWidget;

    bool m_verdict;

private:
    const Calamares::RequirementsModel& m_model;
};

#endif
