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

#include "LabelModel.h"

namespace CalamaresUtils::Locale
{

LabelModel::LabelModel( const QStringList& locales, QObject* parent )
    : QAbstractListModel( parent )
{
    Q_ASSERT( locales.count() > 0 );
    m_locales.reserve( locales.count() );

    for ( const auto& l : locales )
        m_locales.push_back( Label( l ) );
}

LabelModel::~LabelModel()
{
}

int
LabelModel::rowCount( const QModelIndex& ) const
{
    return m_locales.count();
}

QVariant
LabelModel::data( const QModelIndex& index, int role ) const
{
    if ( ( role != LabelRole ) && ( role != EnglishLabelRole ) )
        return QVariant();

    if ( !index.isValid() )
        return QVariant();

    const auto& locale = m_locales.at( index.row() );
    switch ( role )
    {
    case LabelRole:
        return locale.label();
    case EnglishLabelRole:
        return locale.englishLabel();
    default:
        return QVariant();
    }
}

const Label&
LabelModel::locale( int row )
{
    if ( ( row < 0 ) || ( row >= m_locales.count() ) )
    {
        for ( const auto& l : m_locales )
            if ( l.isEnglish() )
                return l;
        return m_locales[0];
    }
    return m_locales[row];
}

int
LabelModel::find( std::function<bool ( const Label& )> predicate ) const
{
    for ( int row = 0; row < m_locales.count() ; ++row )
    {
        if ( predicate( m_locales[row] ) )
            return row;
    }
    return -1;
}

int
LabelModel::find( std::function<bool ( const QLocale& )> predicate ) const
{
    return find( [&]( const Label& l )
    {
        return predicate( l.locale() );
    } );
}

int
LabelModel::find( const QLocale& locale ) const
{
    return find( [&]( const Label& l )
    {
        return locale == l.locale();
    } );
}

}  // namespace
