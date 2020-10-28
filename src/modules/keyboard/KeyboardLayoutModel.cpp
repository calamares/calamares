/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "KeyboardLayoutModel.h"

#include "utils/Logger.h"

#include <algorithm>

XKBListModel::XKBListModel( QObject* parent )
    : QAbstractListModel( parent )
{
}

int
XKBListModel::rowCount( const QModelIndex& ) const
{
    return m_list.count();
}

QVariant
XKBListModel::data( const QModelIndex& index, int role ) const
{
    if ( !index.isValid() )
    {
        return QVariant();
    }
    if ( index.row() < 0 || index.row() >= m_list.count() )
    {
        return QVariant();
    }

    const auto item = m_list.at( index.row() );
    switch ( role )
    {
    case LabelRole:
        return item.label;
    case KeyRole:
        return item.key;
    default:
        return QVariant();
    }
    __builtin_unreachable();
}

QString
XKBListModel::key( int index ) const
{
    if ( index < 0 || index >= m_list.count() )
    {
        return QString();
    }
    return m_list[ index ].key;
}

QString
XKBListModel::label( int index ) const
{
    if ( index < 0 || index >= m_list.count() )
    {
        return QString();
    }
    return m_list[ index ].label;
}

QHash< int, QByteArray >
XKBListModel::roleNames() const
{
    return { { Qt::DisplayRole, "label" }, { Qt::UserRole, "key" } };
}

void
XKBListModel::setCurrentIndex( int index )
{
    if ( index >= m_list.count() || index < 0 )
    {
        return;
    }
    if ( m_currentIndex != index )
    {
        m_currentIndex = index;
        emit currentIndexChanged( m_currentIndex );
    }
}

KeyboardModelsModel::KeyboardModelsModel( QObject* parent )
    : XKBListModel( parent )
{
    // The models map is from human-readable names (!) to xkb identifier
    const auto models = KeyboardGlobal::getKeyboardModels();
    m_list.reserve( models.count() );
    int index = 0;
    for ( const auto& key : models.keys() )
    {
        // So here *key* is the key in the map, which is the human-readable thing,
        //   while the struct fields are xkb-id, and human-readable
        m_list << ModelInfo { models[ key ], key };
        if ( models[ key ] == "pc105" )
        {
            m_defaultPC105 = index;
        }
        index++;
    }

    cDebug() << "Loaded" << m_list.count() << "keyboard models";
}


KeyboardLayoutModel::KeyboardLayoutModel( QObject* parent )
    : QAbstractListModel( parent )
{
    init();
}

int
KeyboardLayoutModel::rowCount( const QModelIndex& parent ) const
{
    Q_UNUSED( parent )
    return m_layouts.count();
}


QVariant
KeyboardLayoutModel::data( const QModelIndex& index, int role ) const
{
    if ( !index.isValid() )
    {
        return QVariant();
    }

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

const QPair< QString, KeyboardGlobal::KeyboardInfo >
KeyboardLayoutModel::item( const int& index ) const
{
    if ( index >= m_layouts.count() || index < 0 )
    {
        return QPair< QString, KeyboardGlobal::KeyboardInfo >();
    }

    return m_layouts.at( index );
}

void
KeyboardLayoutModel::init()
{
    KeyboardGlobal::LayoutsMap layouts = KeyboardGlobal::getKeyboardLayouts();
    for ( KeyboardGlobal::LayoutsMap::const_iterator it = layouts.constBegin(); it != layouts.constEnd(); ++it )
    {
        m_layouts.append( qMakePair( it.key(), it.value() ) );
    }

    std::stable_sort( m_layouts.begin(),
                      m_layouts.end(),
                      []( const QPair< QString, KeyboardGlobal::KeyboardInfo >& a,
                          const QPair< QString, KeyboardGlobal::KeyboardInfo >& b ) {
                          return a.second.description < b.second.description;
                      } );
}

QHash< int, QByteArray >
KeyboardLayoutModel::roleNames() const
{
    return { { Qt::DisplayRole, "label" }, { KeyboardLayoutKeyRole, "key" }, { KeyboardVariantsRole, "variants" } };
}

void
KeyboardLayoutModel::setCurrentIndex( int index )
{
    if ( index >= m_layouts.count() || index < 0 )
    {
        return;
    }

    if ( m_currentIndex != index )
    {
        m_currentIndex = index;
        emit currentIndexChanged( m_currentIndex );
    }
}

int
KeyboardLayoutModel::currentIndex() const
{
    return m_currentIndex;
}


KeyboardVariantsModel::KeyboardVariantsModel( QObject* parent )
    : XKBListModel( parent )
{
}

void
KeyboardVariantsModel::setVariants( QMap< QString, QString > variants )
{
    beginResetModel();
    m_list.clear();
    m_list.reserve( variants.count() );
    for ( const auto& key : variants.keys() )
    {
        m_list << ModelInfo { variants[ key ], key };
    }
    endResetModel();
}
