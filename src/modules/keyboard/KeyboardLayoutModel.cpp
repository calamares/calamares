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
