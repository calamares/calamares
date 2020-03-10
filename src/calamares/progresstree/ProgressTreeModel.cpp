/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
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

#include "ProgressTreeModel.h"

#include "Settings.h"
#include "ViewManager.h"

ProgressTreeModel::ProgressTreeModel( QObject* parent )
    : QAbstractListModel( parent )
{
}

ProgressTreeModel::~ProgressTreeModel() {}

QVariant
ProgressTreeModel::data( const QModelIndex& index, int role ) const
{
    if ( !index.isValid() )
    {
        return QVariant();
    }

    const Calamares::ViewManager* vm = Calamares::ViewManager::instance();
    if ( !vm )
    {
        return QVariant();
    }

    const auto steps = vm->viewSteps();
    if ( ( index.row() < 0 ) || ( index.row() >= steps.length() ) )
    {
        return QVariant();
    }

    const auto* step = steps.at( index.row() );

    if ( role == Qt::DisplayRole )
    {
        return step->prettyName();
    }
    if ( Calamares::Settings::instance()->debugMode() && role == Qt::ToolTipRole )
    {
        QString toolTip( "<b>Debug information</b>" );
        if ( step )
        {
            toolTip.append( "<br/>Type:\tViewStep" );
            toolTip.append( QString( "<br/>Pretty:\t%1" ).arg( step->prettyName() ) );
            toolTip.append( QString( "<br/>Status:\t%1" ).arg( step->prettyStatus() ) );
            toolTip.append( QString( "<br/>Source:\t%1" )
                                .arg( step->moduleInstanceKey().isValid() ? step->moduleInstanceKey().toString()
                                                                          : QStringLiteral( "built-in" ) ) );
        }
        else
        {
            toolTip.append( "<br/>Type:\tDelegate" );
        }
        return toolTip;
    }
    if ( role == ProgressTreeModel::ProgressTreeItemCurrentRole )
    {
        return step && ( Calamares::ViewManager::instance()->currentStep() == step );
    }
    return QVariant();
}


int
ProgressTreeModel::rowCount( const QModelIndex& parent ) const
{
    if ( parent.column() > 0 )
    {
        return 0;
    }
    const Calamares::ViewManager* vm = Calamares::ViewManager::instance();
    return vm ? vm->viewSteps().length() : 0;
}
