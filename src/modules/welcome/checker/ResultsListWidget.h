/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2019-2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef CHECKER_RESULTSLISTWIDGET_H
#define CHECKER_RESULTSLISTWIDGET_H

#include "Config.h"

#include <QWidget>

class CountdownWaitingWidget;

class QBoxLayout;
class QLabel;

class ResultsListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ResultsListWidget( Config* config, QWidget* parent );

    /// @brief The model of requirements has finished a round of checking
    void requirementsComplete();

private:
    Config* m_config = nullptr;

    // UI parts, which need updating when the model changes
    QLabel* m_explanation = nullptr;
    CountdownWaitingWidget* m_countdown = nullptr;
    // There is a central widget, which can be:
    // - a list widget showing failed requirements
    // - nullptr (when displaying a pretty label for language / splash purposes)
    // it is placed in the central layout.
    QWidget* m_centralWidget = nullptr;
    QBoxLayout* m_centralLayout = nullptr;
};

#endif  // CHECKER_RESULTSLISTWIDGET_H
