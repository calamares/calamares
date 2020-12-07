/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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
