/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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

#ifdef WITH_PYTHON
#include "PythonHelper.h"

#undef slots
#include <boost/python/list.hpp>
#include <boost/python/str.hpp>

namespace bp = boost::python;
#endif

namespace Calamares
{

GlobalStorage::GlobalStorage()
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
}


QStringList
GlobalStorage::keys() const
{
    return m.keys();
}


int
GlobalStorage::remove( const QString& key )
{
    return m.remove( key );
}


QVariant
GlobalStorage::value( const QString& key ) const
{
    return m.value( key );
}

#ifdef WITH_PYTHON

bool
GlobalStorage::python_contains( const std::string& key ) const
{
    return contains( QString::fromStdString( key ) );
}


void
GlobalStorage::python_insert( const std::string& key,
                              const bp::object& value )
{
    insert( QString::fromStdString( key ),
            CalamaresPython::variantFromPyObject( value ) );
}


bp::list
GlobalStorage::python_keys() const
{
    bp::list pyList;
    foreach ( const QString& key, keys() )
        pyList.append( key.toStdString() );
    return pyList;
}


int
GlobalStorage::python_remove( const std::string& key )
{
    return remove( QString::fromStdString( key ) );
}


bp::object
GlobalStorage::python_value( const std::string& key ) const
{
    return CalamaresPython::variantToPyObject( value( QString::fromStdString( key ) ) );
}

#endif // WITH_PYTHON

} // namespace Calamares
