/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "PythonQtGlobalStorageWrapper.h"

#include "GlobalStorage.h"


GlobalStorage::GlobalStorage( Calamares::GlobalStorage* gs )
    : QObject( gs )
    , m_gs( gs )
{
}


bool
GlobalStorage::contains( const QString& key ) const
{
    return m_gs->contains( key );
}


int
GlobalStorage::count() const
{
    return m_gs->count();
}


void
GlobalStorage::insert( const QString& key, const QVariant& value )
{
    m_gs->insert( key, value );
}


QStringList
GlobalStorage::keys() const
{
    return m_gs->keys();
}


int
GlobalStorage::remove( const QString& key )
{
    return m_gs->remove( key );
}


QVariant
GlobalStorage::value( const QString& key ) const
{
    return m_gs->value( key );
}
