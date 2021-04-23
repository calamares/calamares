/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Collabora Ltd <arnaud.ferraris@collabora.com>
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

/** @brief Support for "named" enumerations
 *
 * When a string needs to be one specific string out of a set of
 * alternatives -- one "name" from an enumerated set -- then it
 * is useful to have an **enum type** for the enumeration so that
 * C++ code can work with the (strong) type of the enum, while
 * the string can be used for human-readable interaction.
 * The `NamedEnumTable<E>` template provides support for naming
 * values of an enum.
 */

#ifndef UTILS_NAMEDENUM_H
#define UTILS_NAMEDENUM_H

#include <QString>

#include <initializer_list>
#include <type_traits>
#include <vector>

/** @brief Type for collecting parts of a named enum.
 *
 * The `NamedEnumTable<E>` template provides support for naming
 * values of an enum. It supports mapping strings to enum values
 * and mapping enum values to strings.
 *
 * ## Example
 *
 * Suppose we have code where there are three alternatives; it is
 * useful to have a strong type to make the alternatives visible
 * in that code, so the compiler can help check:
 *
 * ```
 * enum class MilkshakeSize { None, Small, Large };
 * ```
 *
 * In a switch() statement, the compiler will check that all kinds
 * of milkshakes are dealt with; we can pass a MilkshakeSize to
 * a function and rest assured that nobody will call that function
 * with a silly value, like `1`.
 *
 * There is no relation between the C++ identifiers used, and
 * any I/O related to that enumeration. In other words,
 *
 * ```
 * std::cout << MilkshakeSize::Small;
 * ```
 *
 * Will **not** print out "Small", or "small", or 1. It won't even
 * compile, because there is no mapping of the enum values to
 * something that can be output.
 *
 * By making a `NamedEnumTable<MilkshakeSize>` we can define a mapping
 * between strings (names) and enum values, so that we can easily
 * output the human-readable name, and also take string input
 * and convert it to an enum value. Suppose we have a function
 * `milkshakeSizeNames()` that returns a reference to such a table,
 * then we can use `find()` to map enums-to-names and names-to-enums.
 *
 * ```
 * const auto& names = milkshakeSizeNames();
 * MilkshakeSize sz{ MilkshakeSize::Large };
 * std::cout << names.find(sz);  // Probably "large"
 *
 * bool ok;
 * sz = names.find( "small", ok );  // Probably MilkshakeSize::Small
 * ```
 *
 * ## Usage
 *
 * It is recommended to use a static const declaration for the table;
 * typical use will define a function that returns a reference to
 * the table, for shared use.
 *
 * The constructor for a table takes an initializer_list; each element
 * of the initializer_list is a **pair** consisting of a name and
 * an associated enum value. The names should be QStrings. For each enum
 * value that is listed, the canonical name should come **first** in the
 * table, so that printing the enum values gives the canonical result.
 *
 * ```
 * static const NamedEnumTable<MilkshakeSize>& milkshakeSizeNames()
 * {
 *     static NamedEnumTable<MilkshakeSize> n { // Initializer list for n
 *         { "large", MilkshakeSize::Large },  // One pair of name-and-value
 *         { "small", MilkshakeSize::Small },
 *         { "big", MilkshakeSize::Large }
 *     };
 *     return n;
 * }
 * ```
 *
 * The function `eNames()`, above, returns a reference to a name table
 * for the enum (presumably an enum class) `E`. It is possible to have
 * more than one table for an enum, or to make the table locally,
 * but **usually** you want one definitive table of names and values.
 * The `eNames()` function gives you that definitive table. In Calamres
 * code, such functions are usually named after the underlying enum.
 *
 * Using this particular table, looking up "large" will return `MilkshakeSize::Large`,
 * looking up "big" will **also** return `MilkshakeSize::Large`, looking up "derp"
 * will return `MilkshakeSize::Large` (because that is the first value in the table)
 * but will set the boolean `ok` parameter to false. Conversely, looking
 * up `MilkshakeSize::Large` will return "large" (never "big").
 *
 * Note that this particular table does **not** name MilkshakeSize::None,
 * so it is probably wrong: you can't get a string for that enum
 * value, and no string will map to MilkshakeSize::None either.
 * In general, tables should cover all of the enum values.
 *
 * Passing an empty initializer_list to the constructor is supported,
 * but will cause UB if the table is ever used for looking up a string.
 *
 */
template < typename T >
struct NamedEnumTable
{
    using string_t = QString;
    using enum_t = T;
    using pair_t = std::pair< string_t, enum_t >;
    using type = std::vector< pair_t >;

    type table;

    /** @brief Create a table of named enum values.
     *
     * Use braced-initialisation for NamedEnum, and remember that the
     * elements of the list are **pairs**, e.g.
     *
     * ```
     * static const NamedEnumTable<Colors> c{ {"red", Colors::Red } };
     * ```
     */
    NamedEnumTable( const std::initializer_list< pair_t >& v )
        : table( v )
    {
        /* static_assert( v.size() > 0 ); */
    }

    /** @brief Find a name @p s in the table.
     *
     * Searches case-insensitively.
     *
     * If the name @p s is not found, @p ok is set to @c false and
     * the first enum value in the table is returned. Otherwise,
     * @p ok is set to @c true and the corresponding value is returned.
     * Use the output value of @p ok to determine if the lookup was
     * successful: there is otherwise no sensible way to distinguish
     * found-the-name-of-the-first-item from not-found.
     */
    enum_t find( const string_t& s, bool& ok ) const
    {
        ok = false;

        for ( const auto& p : table )
            if ( 0 == QString::compare( s, p.first, Qt::CaseInsensitive ) )
            {
                ok = true;
                return p.second;
            }

        // ok is still false
        return table.begin()->second;
    }

    /** @brief Find a name @p s in the table.
     *
     * Searches case-insensitively.
     *
     * If the name @p s is not found, the value @p d is returned as
     * a default. Otherwise the value corresponding to @p s is returned.
     * This is a shortcut over find() using a bool to distinguish
     * successful and unsuccesful lookups.
     */
    enum_t find( const string_t& s, enum_t d ) const
    {
        bool ok = false;
        enum_t e = find( s, ok );
        return ok ? e : d;
    }

    /** @brief Find a value @p s in the table and return its name.
     *
     * If @p s is an enum value in the table, return the corresponding
     * name (the first name with that value, if there are aliases)
     * and set @p ok to @c true.
     *
     * If the value @p s is not found, @p ok is set to @c false and
     * an empty string is returned. This indicates that the table does
     * not cover all of the values * in `enum_t` (and @p s is one
     * of them), **or** that the passed-in value of @p s is
     * not a legal value, e.g. via a static_cast<enum_t>.
     */
    string_t find( enum_t s, bool& ok ) const
    {
        ok = false;

        for ( const auto& p : table )
            if ( s == p.second )
            {
                ok = true;
                return p.first;
            }

        // ok is still false
        return string_t();
    }

    /** @brief Find a value @p s in the table and return its name.
     *
     * Returns an empty string if the value @p s is not found (this
     * indicates that the table does not cover all of the values
     * in `enum_t`, **or** that the passed-in value of @p s is
     * not a legal value, e.g. via a static_cast<enum_t>).
     */
    string_t find( enum_t s ) const
    {
        bool ok = false;
        return find( s, ok );
    }
};

/** @brief Smashes an enum value to its underlying type.
 *
 * While an enum **class** is not an integral type, and its values can't be
 * printed or treated like an integer (like an old-style enum can),
 * the underlying type **is** integral. This template function
 * returns the value of an enum value, in its underlying type.
 * This can be useful for debugging purposes, e.g.
 *
 * ```
 * MilkshakeSize sz{ MilkshakeSize::None };
 * std::cout << milkshakeSizeNames().find( sz ) << smash( sz );
 * ```
 *
 * This will print both the name and the underlying integer for the
 * value; assuming the table from the example is used, there is
 * no name for MilkshakeSize::None, so it will print an empty string,
 * followed by the integral representation -- probably a 0.
 */
template < typename E >
constexpr typename std::underlying_type< E >::type
smash( const E e )
{
    return static_cast< typename std::underlying_type< E >::type >( e );
}

#endif
