/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

/** @brief Support for unit-suffixed values.
 *
 * This combines a value with an (enum) unit indicating what kind
 * of value it is, e.g. 10 meters, or 64 pixels. Includes simple
 * parsing support for the values written as strings like <value><unit>,
 * e.g. "10m" or "64px".
 *
 * When a suffixed unit value needs validation, define an isValid()
 * method; similarly for simple construction from a string (with a fixed
 * table of suffixes). Typical use then looks like:
 *
 * class MyUnit : public NamedSuffix<MyUnitEnum, MyUnitEnum::None>
 * {
 * public:
 *      using NamedSuffix::NamedSuffix;  // Keep existing constructors
 *      MyUnit( const QString& s );
 *      bool isValid() const;
 * } ;
 */

#ifndef UTILS_NAMEDSUFFIX_H
#define UTILS_NAMEDSUFFIX_H

#include "NamedEnum.h"

/** @brief Template that takes the enum type to work with and a special none-enum. */
template < typename T, T _none >
class NamedSuffix
{
public:
    using unit_t = T;

    static constexpr unit_t none = _none;

    /** @brief Empty value. */
    NamedSuffix()
        : m_value( 0 )
        , m_unit( none )
    {
    }

    /** @brief Specific value and unit. */
    NamedSuffix( qint64 value, unit_t unit )
        : m_value( value )
        , m_unit( unit )
    {
    }

    /** @brief Construct value and unit from string.
     *
     * This parses the given string @p s by comparing with the suffixes
     * in @p table and uses the first matching suffix as the unit.
     */
    NamedSuffix( const NamedEnumTable< T >& table, const QString& s )
        : NamedSuffix()
    {
        for ( const auto& suffix : table.table )
            if ( s.endsWith( suffix.first ) )
            {
                m_value = s.left( s.length() - suffix.first.length() ).toLongLong();
                m_unit = suffix.second;
                break;
            }
    }


    /** @brief Construct value from string.
     *
     * This is not defined in the template, because it should probably
     * delegate to the constructor above with a fixed table.
     */
    NamedSuffix( const QString& s );

    qint64 value() const { return m_value; }
    unit_t unit() const { return m_unit; }

    /** @brief Check that a value-unit combination is valid.
     *
     * This is not defined in the template, because validity (e.g.
     * range of acceptable values) depends on the kind of unit.
     */
    bool isValid() const;

protected:
    qint64 m_value;
    unit_t m_unit;
};

#endif
