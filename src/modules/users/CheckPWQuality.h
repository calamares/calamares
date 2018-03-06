/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2018, Adriaan de Groot <groot@kde.org>
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

#ifndef CHECKPWQUALITY_H
#define CHECKPWQUALITY_H

#include <QString>
#include <QVariant>
#include <QVector>

#include <functional>

/**
 * Support for (dynamic) checks on the password's validity.
 * This can be used to implement password requirements like
 * "at least 6 characters". Function addPasswordCheck()
 * instantiates these and adds them to the list of checks.
 */
class PasswordCheck
{
public:
    /** Return true if the string is acceptable. */
    using AcceptFunc = std::function<bool( const QString& )>;
    using MessageFunc = std::function<QString()>;

    /** Generate a @p message if @p filter returns true */
    PasswordCheck( MessageFunc message, AcceptFunc filter );
    /** Yields @p message if @p filter returns true */
    PasswordCheck( const QString& message, AcceptFunc filter );
    /** Null check, always returns empty */
    PasswordCheck();

    /** Applies this check to the given password string @p s
        *  and returns an empty string if the password is ok
        *  according to this filter. Returns a message describing
        *  what is wrong if not.
        */
    QString filter( const QString& s ) const
    {
        return m_accept( s ) ? QString() : m_message();
    }

private:
    MessageFunc m_message;
    AcceptFunc m_accept;
} ;

using PasswordCheckList = QVector<PasswordCheck>;

/* Each of these functions adds a check (if possible) to the list
 * of checks; they use the configuration value(s) from the
 * variant. If the value doesn't make sense, each function
 * may skip adding a check, and do nothing (it should log
 * an error, though).
 */
#define _xDEFINE_CHECK_FUNC(x) \
    add_check_##x( PasswordCheckList& checks, const QVariant& value )
#define DEFINE_CHECK_FUNC(x) void _xDEFINE_CHECK_FUNC(x)
#define DECLARE_CHECK_FUNC(x) void _xDEFINE_CHECK_FUNC(x);

DECLARE_CHECK_FUNC(minLength)
DECLARE_CHECK_FUNC(maxLength)
#ifdef HAVE_LIBPWQUALITY
DECLARE_CHECK_FUNC(libpwquality)
#endif

#endif

