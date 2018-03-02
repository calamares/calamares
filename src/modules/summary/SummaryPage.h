/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
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

#ifndef SUMMARYPAGE_H
#define SUMMARYPAGE_H

#include "Typedefs.h"

#include <QWidget>

class QLabel;
class QScrollArea;
class QVBoxLayout;
class SummaryViewStep;

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
    explicit SummaryPage( const SummaryViewStep* thisViewStep, QWidget* parent = nullptr );

    void onActivate();
    void createContentWidget();

private:
    Calamares::ViewStepList stepsForSummary( const Calamares::ViewStepList& allSteps ) const;

    const SummaryViewStep* m_thisViewStep;

    QVBoxLayout* m_layout = nullptr;
    QWidget* m_contentWidget = nullptr;

    QLabel* createTitleLabel( const QString& text ) const;
    QLabel* createBodyLabel( const QString& text ) const;

    QScrollArea* m_scrollArea;
};

#endif // SUMMARYPAGE_H
