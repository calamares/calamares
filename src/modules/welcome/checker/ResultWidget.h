/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017, 2019, Adriaan de Groot <groot@kde.org>
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

#ifndef CHECKER_RESULTWIDGET_H
#define CHECKER_RESULTWIDGET_H

#include <QLabel>

/**
 * @brief Displays the results of a single check.
 *
 * Widget to insert into a ResultListWidget to display an iconic status
 * (warning or failure when the check is not satisfied) along with
 * descriptive test.
 */
class ResultWidget : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Create widget with results of a check.
     *
     * Use setText() to set up the text of the widget.
     */
    explicit ResultWidget( bool satisfied, bool required, QWidget* parent = nullptr );

    /// @brief Set the displayed description of the check.
    void setText( const QString& text );

private:
    QLabel* m_textLabel;
    QLabel* m_iconLabel;
};

#endif  // CHECKER_RESULTWIDGET_H
