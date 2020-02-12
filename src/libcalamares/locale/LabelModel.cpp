/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019-2020 Adriaan de Groot <groot@kde.org>
 *   Copyright 2019, Camilo Higuita <milo.h@aol.com>
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

#include "Lookup.h"

#include "CalamaresVersion.h"  // For the list of translations

namespace CalamaresUtils
{
namespace Locale
{

LabelModel::LabelModel( const QStringList& locales, QObject* parent )
    : QAbstractListModel( parent )
    , m_localeIds( locales )
{
    Q_ASSERT( locales.count() > 0 );
    m_locales.reserve( locales.count() );

    for ( const auto& l : locales )
    {
        m_locales.push_back( new Label( l, Label::LabelFormat::IfNeededWithCountry, this ) );
    }
}

LabelModel::~LabelModel() {}

int
LabelModel::rowCount( const QModelIndex& ) const
{
    return m_locales.count();
}

QVariant
LabelModel::data( const QModelIndex& index, int role ) const
{
    if ( ( role != LabelRole ) && ( role != EnglishLabelRole ) )
    {
        return QVariant();
    }

    if ( !index.isValid() )
    {
        return QVariant();
    }

    const auto& locale = m_locales.at( index.row() );
    switch ( role )
    {
    case LabelRole:
        return locale->label();
    case EnglishLabelRole:
        return locale->englishLabel();
    default:
        return QVariant();
    }
}

QHash< int, QByteArray >
LabelModel::roleNames() const
{
    return { { LabelRole, "label" }, { EnglishLabelRole, "englishLabel" } };
}

const Label&
LabelModel::locale( int row ) const
{
    if ( ( row < 0 ) || ( row >= m_locales.count() ) )
    {
        for ( const auto& l : m_locales )
            if ( l->isEnglish() )
            {
                return *l;
            }
        return *m_locales[ 0 ];
    }
    return *m_locales[ row ];
}

int
LabelModel::find( std::function< bool( const Label& ) > predicate ) const
{
    for ( int row = 0; row < m_locales.count(); ++row )
    {
        if ( predicate( *m_locales[ row ] ) )
        {
            return row;
        }
    }
    return -1;
}

int
LabelModel::find( std::function< bool( const QLocale& ) > predicate ) const
{
    return find( [&]( const Label& l ) { return predicate( l.locale() ); } );
}

int
LabelModel::find( const QLocale& locale ) const
{
    return find( [&]( const Label& l ) { return locale == l.locale(); } );
}

int
LabelModel::find( const QString& countryCode ) const
{
    if ( countryCode.length() != 2 )
    {
        return -1;
    }

    auto c_l = countryData( countryCode );
    int r = find( [&]( const Label& l ) { return ( l.language() == c_l.second ) && ( l.country() == c_l.first ); } );
    if ( r >= 0 )
    {
        return r;
    }
    return find( [&]( const Label& l ) { return l.language() == c_l.second; } );
}

LabelModel*
availableTranslations()
{
    static LabelModel* model = new LabelModel( QStringLiteral( CALAMARES_TRANSLATION_LANGUAGES ).split( ';' ) );
    return model;
}

}  // namespace Locale
}  // namespace CalamaresUtils
