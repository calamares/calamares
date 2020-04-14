/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2020, Adriaan de Groot <groot@kde.org>
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

#ifndef UTILS_RAII_H
#define UTILS_RAII_H

#include <QObject>

#include <type_traits>

/// @brief Convenience to zero out and deleteLater of any QObject-derived-class
template < typename T >
struct cqDeleter
{
    T*& p;

    ~cqDeleter()
    {
        static_assert( std::is_base_of< QObject, T >::value, "Not a QObject-class" );
        if ( p )
        {
            p->deleteLater();
        }
        p = nullptr;
    }
};

#endif
