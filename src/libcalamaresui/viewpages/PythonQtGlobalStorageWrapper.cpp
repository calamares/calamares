/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2016, Teo Mrnjavac <teo@kde.org>
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

#include "PythonQtGlobalStorageWrapper.h"

#include "GlobalStorage.h"


GlobalStorage::GlobalStorage( Calamares::GlobalStorage* gs )
    : QObject( gs )
    , m_gs( gs )
{}


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
