/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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

#include "GlobalStorage.h"

#include "utils/Logger.h"

#ifdef WITH_PYTHON
#include "PythonHelper.h"

#undef slots
#include <boost/python/list.hpp>
#include <boost/python/str.hpp>

namespace bp = boost::python;
#endif

namespace Calamares {

GlobalStorage::GlobalStorage()
    : QObject( nullptr )
{
}


bool
GlobalStorage::contains( const QString& key ) const
{
    return m.contains( key );
}


int
GlobalStorage::count() const
{
    return m.count();
}


void
GlobalStorage::insert( const QString& key, const QVariant& value )
{
    m.insert( key, value );
    emit changed();
}


QStringList
GlobalStorage::keys() const
{
    return m.keys();
}


int
GlobalStorage::remove( const QString& key )
{
    int nItems = m.remove( key );
    emit changed();
    return nItems;
}


QVariant
GlobalStorage::value( const QString& key ) const
{
    return m.value( key );
}

void
GlobalStorage::debugDump() const
{
    for ( auto it = m.cbegin(); it != m.cend(); ++it )
    {
        cDebug() << it.key() << '\t' << it.value();
    }
}

} // namespace Calamares

#ifdef WITH_PYTHON

namespace CalamaresPython
{

GlobalStoragePythonWrapper::GlobalStoragePythonWrapper( Calamares::GlobalStorage* gs )
    : m_gs( gs )
{}

bool
GlobalStoragePythonWrapper::contains( const std::string& key ) const
{
    return m_gs->contains( QString::fromStdString( key ) );
}


int
GlobalStoragePythonWrapper::count() const
{
    return m_gs->count();
}


void
GlobalStoragePythonWrapper::insert( const std::string& key,
                       const bp::object& value )
{
    m_gs->insert( QString::fromStdString( key ),
                CalamaresPython::variantFromPyObject( value ) );
}


bp::list
GlobalStoragePythonWrapper::keys() const
{
    bp::list pyList;
    const auto keys = m_gs->keys();
    for ( const QString& key : keys )
        pyList.append( key.toStdString() );
    return pyList;
}


int
GlobalStoragePythonWrapper::remove( const std::string& key )
{
    return m_gs->remove( QString::fromStdString( key ) );
}


bp::object
GlobalStoragePythonWrapper::value( const std::string& key ) const
{
    return CalamaresPython::variantToPyObject( m_gs->value( QString::fromStdString( key ) ) );
}

} // namespace CalamaresPython

#endif // WITH_PYTHON
