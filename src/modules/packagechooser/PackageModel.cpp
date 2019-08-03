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

#include "PackageModel.h"

#include "utils/Logger.h"

const NamedEnumTable< PackageChooserMode >&
roleNames()
{
    static const NamedEnumTable< PackageChooserMode > names {
        { "optional", PackageChooserMode::Optional },
        { "required", PackageChooserMode::Required },
        { "optionalmultiple", PackageChooserMode::OptionalMultiple },
        { "requiredmultiple", PackageChooserMode::RequiredMultiple },
        // and a bunch of aliases
        { "zero-or-one", PackageChooserMode::Optional },
        { "radio", PackageChooserMode::Required },
        { "one", PackageChooserMode::Required },
        { "set", PackageChooserMode::OptionalMultiple },
        { "zero-or-more", PackageChooserMode::OptionalMultiple },
        { "multiple", PackageChooserMode::RequiredMultiple },
        { "one-or-more", PackageChooserMode::RequiredMultiple }
    };
    return names;
}

PackageItem
PackageItem::fromAppStream( const QString& filename )
{
    // TODO: implement this
    return PackageItem {};
}

PackageItem::PackageItem() {}

PackageItem::PackageItem( const QString& a_id,
                          const QString& a_package,
                          const QString& a_name,
                          const QString& a_description )
    : id( a_id )
    , package( a_package )
    , name( a_name )
    , description( a_description )
{
}

PackageItem::PackageItem( const QString& a_id,
                          const QString& a_package,
                          const QString& a_name,
                          const QString& a_description,
                          const QString& screenshotPath )
    : id( a_id )
    , package( a_package )
    , name( a_name )
    , description( a_description )
    , screenshot( screenshotPath )
{
}


PackageListModel::PackageListModel( QObject* parent )
    : QAbstractListModel( parent )
{
}

PackageListModel::PackageListModel( PackageList&& items, QObject* parent )
    : QAbstractListModel( parent )
    , m_packages( std::move( items ) )
{
}

PackageListModel::~PackageListModel() {}

void
PackageListModel::addPackage( PackageItem&& p )
{
    int c = m_packages.count();
    beginInsertRows( QModelIndex(), c, c );
    m_packages.append( p );
    endInsertRows();
}

int
PackageListModel::rowCount( const QModelIndex& index ) const
{
    // For lists, valid indexes have zero children; only the root index has them
    return index.isValid() ? 0 : m_packages.count();
}

QVariant
PackageListModel::data( const QModelIndex& index, int role ) const
{
    if ( !index.isValid() )
    {
        return QVariant();
    }
    int row = index.row();
    if ( row >= m_packages.count() || row < 0 )
    {
        return QVariant();
    }

    if ( role == Qt::DisplayRole /* Also PackageNameRole */ )
    {
        return m_packages[ row ].name;
    }
    else if ( role == DescriptionRole )
    {
        return m_packages[ row ].description;
    }
    else if ( role == ScreenshotRole )
    {
        return m_packages[ row ].screenshot;
    }
    else if ( role == IdRole )
    {
        return m_packages[ row ].id;
    }

    return QVariant();
}
