/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "PackageModel.h"

#include "Branding.h"
#include "utils/Logger.h"
#include "utils/Variant.h"

#include <QFileInfo>

/** @brief A wrapper for CalamaresUtils::getSubMap that excludes the success param
 */
static QVariantMap
getSubMap( const QVariantMap& map, const QString& key )
{
    bool success;

    return CalamaresUtils::getSubMap( map, key, success );
}

static QPixmap
loadScreenshot( const QString& path )
{
    if ( QFileInfo::exists( path ) )
    {
        return QPixmap( path );
    }

    const auto* branding = Calamares::Branding::instance();
    if ( !branding )
    {
        return QPixmap();
    }
    return QPixmap( branding->componentDirectory() + QStringLiteral( "/" ) + path );
}

PackageItem::PackageItem() {}

PackageItem::PackageItem( const QString& a_id, const QString& a_name, const QString& a_description )
    : id( a_id )
    , name( a_name )
    , description( a_description )
{
}

PackageItem::PackageItem( const QString& a_id,
                          const QString& a_name,
                          const QString& a_description,
                          const QString& screenshotPath )
    : id( a_id )
    , name( a_name )
    , description( a_description )
    , screenshot( screenshotPath )
{
}

PackageItem::PackageItem( const QVariantMap& item_map )
    : id( CalamaresUtils::getString( item_map, "id" ) )
    , name( CalamaresUtils::Locale::TranslatedString( item_map, "name" ) )
    , description( CalamaresUtils::Locale::TranslatedString( item_map, "description" ) )
    , screenshot( loadScreenshot( CalamaresUtils::getString( item_map, "screenshot" ) ) )
    , packageNames( CalamaresUtils::getStringList( item_map, "packages" ) )
    , netinstallData( getSubMap( item_map, "netinstall" ) )
{
    if ( name.isEmpty() && id.isEmpty() )
    {
        name = QObject::tr( "No product" );
    }
    else if ( name.isEmpty() )
    {
        cWarning() << "PackageChooser item" << id << "has an empty name.";
    }
    if ( description.isEmpty() )
    {
        description = QObject::tr( "No description provided." );
    }
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
    // Only add valid packages
    if ( p.isValid() )
    {
        int c = m_packages.count();
        beginInsertRows( QModelIndex(), c, c );
        m_packages.append( p );
        endInsertRows();
    }
}

QStringList
PackageListModel::getInstallPackagesForName( const QString& id ) const
{
    for ( const auto& p : qAsConst( m_packages ) )
    {
        if ( p.id == id )
        {
            return p.packageNames;
        }
    }
    return QStringList();
}

QStringList
PackageListModel::getInstallPackagesForNames( const QStringList& ids ) const
{
    QStringList l;
    for ( const auto& p : qAsConst( m_packages ) )
    {
        if ( ids.contains( p.id ) )
        {
            l.append( p.packageNames );
        }
    }
    return l;
}

QVariantList
PackageListModel::getNetinstallDataForNames( const QStringList& ids ) const
{
    QVariantList l;
    for ( auto& p : m_packages )
    {
        if ( ids.contains( p.id ) )
        {
            if ( !p.netinstallData.isEmpty() )
            {
                QVariantMap newData = p.netinstallData;
                newData[ "source" ] = QStringLiteral( "packageChooser" );
                l.append( newData );
            }
        }
    }
    return l;
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
        return m_packages[ row ].name.get();
    }
    else if ( role == DescriptionRole )
    {
        return m_packages[ row ].description.get();
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
