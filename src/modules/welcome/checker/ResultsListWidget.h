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

class QLabel;
class ResultsListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ResultsListWidget( const Calamares::RequirementsModel& model, QWidget* parent );

private:
    /// @brief A link in the explanatory text has been clicked
    void linkClicked( const QString& link );
    void retranslate();

    QLabel* m_explanation = nullptr;  ///< Explanatory text above the list, with link
    const Calamares::RequirementsModel& m_model;
    QList< ResultWidget* > m_resultWidgets;  ///< One widget for each unsatisfied entry
};

#endif  // CHECKER_RESULTSLISTWIDGET_H
