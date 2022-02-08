/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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
    using AcceptFunc = std::function< bool( const QString& ) >;
    using MessageFunc = std::function< QString() >;

    using Weight = size_t;

    /** @brief Generate a @p message if @p filter returns true
     *
     * When @p filter returns true on the proposed password, the
     * password is accepted (by this check). If false, then the
     * @p message will be shown to the user.
     *
     * @p weight is used to order the checks (low-weight goes first).
     */
    PasswordCheck( MessageFunc message, AcceptFunc filter, Weight weight = 1000 );
    /** @brief Null check, always accepts, no message */
    PasswordCheck();

    /** Applies this check to the given password string @p s
        *  and returns an empty string if the password is ok
        *  according to this filter. Returns a message describing
        *  what is wrong if not.
        */
    QString filter( const QString& s ) const { return m_accept( s ) ? QString() : m_message(); }

    Weight weight() const { return m_weight; }
    bool operator<( const PasswordCheck& other ) const { return weight() < other.weight(); }

private:
    Weight m_weight;
    MessageFunc m_message;
    AcceptFunc m_accept;
};

using PasswordCheckList = QVector< PasswordCheck >;

/* Each of these functions adds a check (if possible) to the list
 * of checks; they use the configuration value(s) from the
 * variant. If the value doesn't make sense, each function
 * may skip adding a check, and do nothing (it should log
 * an error, though).
 */
#define DEFINE_CHECK_FUNC_impl( x ) add_check_##x( PasswordCheckList& checks, const QVariant& value )
#define DEFINE_CHECK_FUNC( x ) void DEFINE_CHECK_FUNC_impl( x )
#define DECLARE_CHECK_FUNC( x ) void DEFINE_CHECK_FUNC_impl( x );

DECLARE_CHECK_FUNC( minLength )
DECLARE_CHECK_FUNC( maxLength )
#ifdef HAVE_LIBPWQUALITY
DECLARE_CHECK_FUNC( libpwquality )
#endif

#endif
