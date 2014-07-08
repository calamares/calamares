/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
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

#ifndef INSTALLATIONVIEWSTEP_H
#define INSTALLATIONVIEWSTEP_H

#include <viewpages/ViewStep.h>

namespace Calamares
{

class InstallationViewStep : public ViewStep
{
public:
    explicit InstallationViewStep( QObject* parent = nullptr );

    QString prettyName() const override;

    QWidget* widget() override;

    void next() override;
    void back() override;

    bool isNextEnabled() const override;

    bool isAtBeginning() const override;
    bool isAtEnd() const override;

private:
    QWidget* m_widget;
};

}

#endif /* INSTALLATIONVIEWSTEP_H */
