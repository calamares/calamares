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

#ifndef VIEWSTEPITEM_H
#define VIEWSTEPITEM_H

#include "ProgressTreeItem.h"

#include <functional>

namespace Calamares
{
class ViewStep;
}

class ViewStepItem : public ProgressTreeItem
{
public:
    // We take a std::function< QString() > instead of a QString because the view asks for
    // new strings on LanguageChange, and tr needs to be called again in that case.
    explicit ViewStepItem( std::function< QString() > prettyName,
                           std::function< const Calamares::ViewStep*() > accessor,
                           ProgressTreeItem* parent = nullptr );

    explicit ViewStepItem( const Calamares::ViewStep* step,
                           ProgressTreeItem* parent = nullptr );

    void appendChild( ProgressTreeItem* item ) override;

    QVariant data( int role ) const override;

private:
    std::function< const Calamares::ViewStep*() > m_accessor;
    std::function< QString() > m_prettyName;
    const Calamares::ViewStep* m_step;
};


#endif // VIEWSTEPITEM_H
