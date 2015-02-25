/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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

#include "ViewStepItem.h"

#include "ProgressTreeModel.h"
#include "ViewManager.h"
#include "viewpages/ViewStep.h"


ViewStepItem::ViewStepItem( const QString& prettyName,
                            std::function< const Calamares::ViewStep*() > accessor,
                            ProgressTreeItem* parent )
    : ProgressTreeItem( parent )
    , m_step( 0 )
    , m_prettyName( prettyName )
{
    m_accessor = accessor;
}


ViewStepItem::ViewStepItem( const Calamares::ViewStep* step,
                            ProgressTreeItem* parent )
    : ProgressTreeItem( parent )
{
    m_step = step;
}

void
ViewStepItem::appendChild( ProgressTreeItem* item )
{
    Q_ASSERT( false );
}


QVariant
ViewStepItem::data( int role ) const
{
    if ( role == ProgressTreeModel::ProgressTreeItemRole )
        return this;
    if ( role == Qt::DisplayRole )
        return m_step ? m_step->prettyName() : m_prettyName;
    if ( role == ProgressTreeModel::ProgressTreeItemCurrentRole )
        return m_step ?
               ( Calamares::ViewManager::instance()->currentStep() == m_step ) :
               ( Calamares::ViewManager::instance()->currentStep() == m_accessor() );
    return QVariant();
}
