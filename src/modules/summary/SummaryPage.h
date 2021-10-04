/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef SUMMARYPAGE_H
#define SUMMARYPAGE_H

#include "viewpages/ViewStep.h"

#include <QWidget>

class Config;
class SummaryViewStep;

class QLabel;
class QScrollArea;
class QVBoxLayout;


/** @brief Provide a summary view with to-be-done action descriptions.
*
* Those steps that occur since the previous execution step (e.g. that
* are queued for execution now; in the normal case where there is
* only one execution step, this means everything that the installer
* is going to do) are added to the summary view. Each view step
* can provide one of the following things to display in the summary
* view:
*
* - A string from ViewStep::prettyStatus(), which is formatted
*   and added as a QLabel to the view. Return an empty string
*   from prettyStatus() to avoid this.
* - A QWidget from ViewStep::createSummaryWidget(). This is for
*   complicated displays not suitable for simple text representation.
*   Return a nullptr to avoid this.
*
* If neither a (non-empty) string nor a widget is returned, the
* step is not named in the summary.
*/
class SummaryPage : public QWidget
{
    Q_OBJECT
public:
    explicit SummaryPage( Config* config, QWidget* parent = nullptr );

    /// @brief Create contents showing all of the summary
    void buildWidgets( Config* config, SummaryViewStep* viewstep );
    /// @brief Clean up the widgets
    void cleanup();

private:
    QVBoxLayout* m_layout = nullptr;
    QWidget* m_contentWidget = nullptr;
    QScrollArea* m_scrollArea = nullptr;
};

#endif  // SUMMARYPAGE_H
