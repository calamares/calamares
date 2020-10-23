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

#include <algorithm>


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
KeyboardLayoutModel::setCurrentIndex( const int& index )
{
    if ( index >= m_layouts.count() || index < 0 )
    {
        return;
    }

    m_currentIndex = index;
    emit currentIndexChanged( m_currentIndex );
}

int
KeyboardLayoutModel::currentIndex() const
{
    return m_currentIndex;
}

KeyboardModelsModel::KeyboardModelsModel( QObject* parent )
    : QAbstractListModel( parent )
{
    detectModels();
}

void
KeyboardModelsModel::detectModels()
{
    beginResetModel();
    const auto models = KeyboardGlobal::getKeyboardModels();
    auto index = -1;
    for ( const auto& key : models.keys() )
    {
        index++;
        m_list << QMap< QString, QString > { { "label", key }, { "key", models[ key ] } };
        if ( models[ key ] == "pc105" )
        {
            this->setCurrentIndex( index );
        }
    }
    endResetModel();
}

void
KeyboardModelsModel::refresh()
{
    m_list.clear();
    setCurrentIndex( -1 );
    detectModels();
}

QVariant
KeyboardModelsModel::data( const QModelIndex& index, int role ) const
{
    if ( !index.isValid() )
    {
        return QVariant();
    }
    const auto item = m_list.at( index.row() );
    return role == Qt::DisplayRole ? item[ "label" ] : item[ "key" ];
}

int
KeyboardModelsModel::rowCount( const QModelIndex& ) const
{
    return m_list.count();
}

QHash< int, QByteArray >
KeyboardModelsModel::roleNames() const
{
    return { { Qt::DisplayRole, "label" }, { Qt::UserRole, "key" } };
}

int
KeyboardModelsModel::currentIndex() const
{
    return m_currentIndex;
}

const QMap< QString, QString >
KeyboardModelsModel::item( const int& index ) const
{
    if ( index >= m_list.count() || index < 0 )
    {
        return QMap< QString, QString >();
    }

    return m_list.at( index );
}

const QMap< QString, QString >
KeyboardVariantsModel::item( const int& index ) const
{
    if ( index >= m_list.count() || index < 0 )
    {
        return QMap< QString, QString >();
    }

    return m_list.at( index );
}

void
KeyboardModelsModel::setCurrentIndex( const int& index )
{
    if ( index >= m_list.count() || index < 0 )
    {
        return;
    }

    m_currentIndex = index;
    emit currentIndexChanged( m_currentIndex );
}

KeyboardVariantsModel::KeyboardVariantsModel( QObject* parent )
    : QAbstractListModel( parent )
{
}

int
KeyboardVariantsModel::currentIndex() const
{
    return m_currentIndex;
}

void
KeyboardVariantsModel::setCurrentIndex( const int& index )
{
    if ( index >= m_list.count() || index < 0 )
    {
        return;
    }

    m_currentIndex = index;
    emit currentIndexChanged( m_currentIndex );
}

QVariant
KeyboardVariantsModel::data( const QModelIndex& index, int role ) const
{
    if ( !index.isValid() )
    {
        return QVariant();
    }
    const auto item = m_list.at( index.row() );
    return role == Qt::DisplayRole ? item[ "label" ] : item[ "key" ];
}

int
KeyboardVariantsModel::rowCount( const QModelIndex& ) const
{
    return m_list.count();
}

QHash< int, QByteArray >
KeyboardVariantsModel::roleNames() const
{
    return { { Qt::DisplayRole, "label" }, { Qt::UserRole, "key" } };
}

void
KeyboardVariantsModel::setVariants( QMap< QString, QString > variants )
{
    m_list.clear();
    beginResetModel();
    for ( const auto& key : variants.keys() )
    {
        const auto item = QMap< QString, QString > { { "label", key }, { "key", variants[ key ] } };
        m_list << item;
    }
    endResetModel();
}

