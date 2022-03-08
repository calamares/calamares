/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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
    ~BlankViewStep() override;

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
