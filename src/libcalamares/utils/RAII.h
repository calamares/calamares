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

/// @brief Sets a bool to @p value and resets to !value on destruction
template < bool value >
struct cBoolSetter
{
    bool& m_b;

    cBoolSetter( bool& b )
        : m_b( b )
    {
        m_b = value;
    }
    ~cBoolSetter() { m_b = !value; }
};

/// @brief Blocks signals on a QObject until destruction
using cSignalBlocker = QSignalBlocker;

#endif
