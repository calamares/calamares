/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019, Adriaan de Groot <groot@kde.org>
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

/** @brief Support for unit-suffixed values.
 */

#ifndef LIBCALAMARES_NAMEDSUFFIX_H
#define LIBCALAMARES_NAMEDSUFFIX_H

#include "NamedEnum.h"

template<typename T, T none>
class NamedSuffix
{
public:
    using unit_t = T;

    NamedSuffix()
        : m_value(0)
        , m_unit( none )
    {
    }

    int value() const { return m_value; }
    T unit() const { return m_unit; }

    bool isValid() const { return m_unit != none; }

protected:
    NamedSuffix( const NamedEnumTable<T>& table, const QString& s )
        : NamedSuffix()
    {
        for( const auto suffix : table.table )
            if ( s.endsWith( suffix.first ) )
            {
                m_value = s.left( s.length() - suffix.first.length() + 1 ).toInt();
                m_unit = suffix.second;
                break;
            }
    }

    int m_value;
    T m_unit;
};


#endif
