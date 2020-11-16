/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */
#include "ThemeInfo.h"

#include <KPackage/Package>
#include <KPackage/PackageLoader>

ThemesModel::ThemesModel( QObject* parent )
    : QAbstractListModel( parent )
{
    auto packages = KPackage::PackageLoader::self()->listPackages( "Plasma/LookAndFeel" );
    m_themes.reserve( packages.length() );

    for ( const auto& p : packages )
    {
        m_themes.append( ThemeInfo { p } );
    }
}

int
ThemesModel::rowCount( const QModelIndex& ) const
{
    return m_themes.count();
}

QVariant
ThemesModel::data( const QModelIndex& index, int role ) const
{
    if ( !index.isValid() )
    {
        return QVariant();
    }
    if ( index.row() < 0 || index.row() >= m_themes.count() )
    {
        return QVariant();
    }

    const auto& item = m_themes.at( index.row() );
    switch ( role )
    {
    case LabelRole:
        return item.name;
    case KeyRole:
        return item.id;
    default:
        return QVariant();
    }
    __builtin_unreachable();
}

QHash< int, QByteArray >
ThemesModel::roleNames() const
{
    return { { LabelRole, "label" }, { KeyRole, "key" } };
}

void
ThemesModel::setThemeImage( const QString& id, const QString& imagePath )
{
    auto* theme = m_themes.findById( id );
    if ( theme )
    {
        theme->imagePath = imagePath;
    }
}

void
ThemesModel::setThemeImage( const QMap< QString, QString >& images )
{
    for ( const auto& k : images )
    {
        setThemeImage( k, images[ k ] );
    }
}

void
ThemesModel::showTheme( const QString& id, bool show )
{
    auto* theme = m_themes.findById( id );
    if ( theme )
    {
        theme->show = show;
    }
}

void
ThemesModel::showOnlyThemes( const QMap< QString, QString >& onlyThese )
{
    for ( auto& t : m_themes )
    {
        t.show = onlyThese.contains( t.id );
    }
}


ThemeInfo::ThemeInfo( const KPluginMetaData& data )
    : id( data.pluginId() )
    , name( data.name() )
    , description( data.description() )
    , widget( nullptr )
{
}
