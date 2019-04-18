/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019, Adriaan de Groot <groot@kde.org>
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

#include "LocaleModel.h"

LocaleModel::LocaleModel(const QStringList& locales, QObject* parent)
    : QAbstractTableModel( parent )
{
    m_locales.reserve( locales.count() );

    for ( const auto& l : locales )
        m_locales.emplace_back( l );
}

LocaleModel::~LocaleModel()
{
}

int
LocaleModel::columnCount( const QModelIndex& ) const
{
    return 2;
}

int
LocaleModel::rowCount( const QModelIndex& ) const
{
    return m_locales.size();
}

QVariant
LocaleModel::data( const QModelIndex& index, int role ) const
{
    if ( role != Qt::DisplayRole )
        return QVariant();

    if ( !index.isValid() )
        return QVariant();

    const auto& locale = m_locales.at( index.row() );
    switch ( index.column() )
    {
        case 0:
            return locale.label();
        case 1:
            return locale.englishLabel();
        default:
            return QVariant();
    }
}
