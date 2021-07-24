/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2017 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2017 Gabriel Craciunescu <crazy@frugalware.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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
    explicit CheckerContainer( Config* config, QWidget* parent = nullptr );
    ~CheckerContainer() override;

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
    Config* m_config = nullptr;
};

#endif
