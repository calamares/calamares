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
    case ShownRole:
        return item.show;
    default:
        return QVariant();
    }
    __builtin_unreachable();
}

QHash< int, QByteArray >
ThemesModel::roleNames() const
{
    return { { LabelRole, "label" }, { KeyRole, "key" }, { ShownRole, "show" }, { ImageRole, "image" } };
}

void
ThemesModel::setThemeImage( const QString& id, const QString& imagePath )
{
    auto [ i, theme ] = m_themes.indexById( id );
    if ( theme )
    {
        theme->imagePath = imagePath;
        emit dataChanged( index( i, 0 ), index( i, 0 ), { ImageRole } );
    }
}

void
ThemesModel::setThemeImage( const QMap< QString, QString >& images )
{
    if ( m_themes.isEmpty() )
    {
        return;
    }

    // Don't emit signals from each call, aggregate to one call (below this block)
    {
        QSignalBlocker b( this );
        for ( const auto& k : images )
        {
            setThemeImage( k, images[ k ] );
        }
    }
    emit dataChanged( index( 0, 0 ), index( m_themes.count() - 1 ), { ImageRole } );
}

void
ThemesModel::showTheme( const QString& id, bool show )
{
    auto [ i, theme ] = m_themes.indexById( id );
    if ( theme )
    {
        theme->show = show;
        emit dataChanged( index( i, 0 ), index( i, 0 ), { ShownRole } );
    }
}

void
ThemesModel::showOnlyThemes( const QMap< QString, QString >& onlyThese )
{
    if ( m_themes.isEmpty() )
    {
        return;
    }

    // No signal blocker block needed here because we're not calling showTheme()
    // QSignalBlocker b( this );
    for ( auto& t : m_themes )
    {
        t.show = onlyThese.contains( t.id );
    }
    emit dataChanged( index( 0, 0 ), index( m_themes.count() - 1 ), { ShownRole } );
}


ThemeInfo::ThemeInfo( const KPluginMetaData& data )
    : id( data.pluginId() )
    , name( data.name() )
    , description( data.description() )
{
}
