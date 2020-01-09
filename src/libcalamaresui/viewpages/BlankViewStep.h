/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2018, Adriaan de Groot <groot@kde.org>
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

#ifndef BLANKVIEWSTEP_H
#define BLANKVIEWSTEP_H

#include "viewpages/ViewStep.h"

namespace Calamares
{

/** @brief A "blank" view step, used for error and status reporting
 *
 * This view step never allows navigation (forward or back); it's a trap.
 * It displays a title and explanation, and optional details.
 */
class BlankViewStep : public Calamares::ViewStep
{
    Q_OBJECT

public:
    explicit BlankViewStep( const QString& title,
                            const QString& description,
                            const QString& details = QString(),
                            QObject* parent = nullptr );
    virtual ~BlankViewStep() override;

    QString prettyName() const override;

    QWidget* widget() override;

    void next() override;
    void back() override;

    bool isNextEnabled() const override;
    bool isBackEnabled() const override;

    bool isAtBeginning() const override;
    bool isAtEnd() const override;

    Calamares::JobList jobs() const override;

private:
    QWidget* m_widget;
};

}  // namespace Calamares
#endif  // BLANKVIEWSTEP_H
