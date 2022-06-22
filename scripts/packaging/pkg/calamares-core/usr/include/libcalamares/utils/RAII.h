/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#ifndef UTILS_RAII_H
#define UTILS_RAII_H

#include <QObject>
#include <QSignalBlocker>

#include <optional>
#include <type_traits>

/** @brief Convenience to zero out and deleteLater of any QObject-derived-class
 *
 * If, before destruction, preserve is set to @c true, then
 * the object is "preserved", and not deleted at all.
 */
template < typename T >
struct cqDeleter
{
    T*& p;
    bool preserve = false;

    ~cqDeleter()
    {
        static_assert( std::is_base_of< QObject, T >::value, "Not a QObject-class" );
        if ( !preserve )
        {
            if ( p )
            {
                p->deleteLater();
            }
            p = nullptr;
        }
    }
};

/// @brief Blocks signals on a QObject until destruction
using cSignalBlocker = QSignalBlocker;

/** @brief Writes a value on destruction to a pointed-to location.
 *
 * If the pointer is non-null, write the last-given-value if there
 * is one to the pointed-to object. This is called the "then-value".
 *
 */
template < typename T >
struct cScopedAssignment
{
    std::optional< T > m_value;
    T* m_pointer;

    /** @brief Create a setter with no value set
     *
     * Until a value is set via operator=(), this pointer-setter
     * will do nothing on destruction, leaving the pointed-to
     * value unchanged.
     */
    cScopedAssignment( T* p )
        : m_pointer( p )
    {
    }
    /** @brief Create a setter with a then-value already set
     *
     * This ensures that on destruction, the value @p v will be written;
     * it is equivalent to assigning @p v immediately. The pointed-to
     * value is **not** changed (until destruction).
     */
    cScopedAssignment( T* p, T then )
        : m_value( then )
        , m_pointer( p )
    {
    }
    /** @brief Create a setter with a then-value and assign a new value now
     *
     * As above, but also assign @p now to the thing pointed-to.
     */
    cScopedAssignment( T* p, T now, T then )
        : m_value( then )
        , m_pointer( p )
    {
        if ( p )
        {
            *p = now;
        }
    }

    ~cScopedAssignment()
    {
        if ( m_pointer && m_value.has_value() )
        {
            *m_pointer = m_value.value();
        }
    }

    const T& operator=( const T& then )
    {
        m_value = then;
        return then;
    }
};

template < typename T >
cScopedAssignment( T p ) -> cScopedAssignment< decltype( *p ) >;
#endif
