/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2019-2020, Adriaan de Groot <groot@kde.org>
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
    explicit ResultsListWidget(const Calamares::RequirementsModel  &model,  QWidget* parent);

private:
    /// @brief A link in the explanatory text has been clicked
    void linkClicked( const QString& link );
    void retranslate();

    QLabel* m_explanation = nullptr;  ///< Explanatory text above the list, with link
    const Calamares::RequirementsModel &m_model;
    QList< ResultWidget* > m_resultWidgets;  ///< One widget for each unsatisfied entry
};

#endif  // CHECKER_RESULTSLISTWIDGET_H
