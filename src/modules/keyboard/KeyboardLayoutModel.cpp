/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2016, Teo Mrnjavac <teo@kde.org>
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

#include "KeyboardLayoutModel.h"

#include <algorithm>


KeyboardLayoutModel::KeyboardLayoutModel( QObject* parent )
    : QAbstractListModel( parent )
{
    init();
}


int
KeyboardLayoutModel::rowCount( const QModelIndex& parent ) const
{
    Q_UNUSED( parent );
    return m_layouts.count();
}


QVariant
KeyboardLayoutModel::data( const QModelIndex& index, int role ) const
{
    if ( !index.isValid() )
        return QVariant();

    switch ( role )
    {
    case Qt::DisplayRole:
        return m_layouts.at( index.row() ).second.description;
    case KeyboardVariantsRole:
        return QVariant::fromValue( m_layouts.at( index.row() ).second.variants );
    case KeyboardLayoutKeyRole:
        return m_layouts.at( index.row() ).first;
    }

    return QVariant();
}


void
KeyboardLayoutModel::init()
{
    KeyboardGlobal::LayoutsMap layouts =
        KeyboardGlobal::getKeyboardLayouts();
    for ( KeyboardGlobal::LayoutsMap::const_iterator it = layouts.constBegin();
            it != layouts.constEnd(); ++it )
        m_layouts.append( qMakePair( it.key(), it.value() ) );

    std::stable_sort( m_layouts.begin(), m_layouts.end(), []( const QPair< QString, KeyboardGlobal::KeyboardInfo >& a,
                      const QPair< QString, KeyboardGlobal::KeyboardInfo >& b )
    {
        return a.second.description < b.second.description;
    } );
}
