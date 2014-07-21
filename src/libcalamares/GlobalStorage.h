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

#ifndef CALAMARES_GLOBALSTORAGE_H
#define CALAMARES_GLOBALSTORAGE_H

#include "CalamaresConfig.h"

#include <QVariantMap>

#ifdef WITH_PYTHON
namespace boost
{
namespace python
{
namespace api
{
class object;
}
class list;
}
}
#endif

namespace Calamares
{

class GlobalStorage
{
public:
    explicit GlobalStorage();

    //NOTE: thread safety is guaranteed by JobQueue, which executes jobs one by one.
    //      If at any time jobs become concurrent, this class must be made thread-safe.
    bool contains( const QString& key ) const;
    int count() const;
    void insert( const QString& key, const QVariant& value );
    QStringList keys() const;
    int remove( const QString& key );
    QVariant value( const QString& key ) const;

#ifdef WITH_PYTHON
    bool python_contains( const std::string& key ) const;
    void python_insert( const std::string& key, const boost::python::api::object& value );
    boost::python::list python_keys() const;
    int python_remove( const std::string& key );
    boost::python::api::object python_value( const std::string& key ) const;
#endif
private:
    QVariantMap m;
};

} // namespace Calamares

#endif // CALAMARES_GLOBALSTORAGE_H
