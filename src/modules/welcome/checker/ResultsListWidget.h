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

#include "ResultWidget.h"

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

private:
    /// @brief A link in the explanatory text has been clicked
    void linkClicked( const QString& link );
    /// @brief The model of requirements changed
    void requirementsChanged();

    void retranslate();

    /** @brief The model can be reset and re-filled, is it full yet?
     *
     * We count how many requirements we have seen; since the model
     * does not shrink, we can avoid reacting to model-is-cleared
     * events because the size of the model is then (briefly) smaller
     * than what we expect.
     *
     * Returns true if the model contains at least m_requirementsSeen
     * elements, and updates m_requirementsSeen. (Which is why the
     * method is not const)
     */
    bool isModelFilled();

    /** @brief A list of widgets, one per entry in the requirements model
     *
     * Unsatisfied entries have a non-null widget pointer, while requirements
     * entries that **are** satisfied have no widget.
     */
    QList< ResultWidget* > m_resultWidgets;
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

    int m_requirementsSeen = 0;
};

#endif  // CHECKER_RESULTSLISTWIDGET_H
