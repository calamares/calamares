/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */
#ifndef LOCALE_TRANSLATABLESTRING_H
#define LOCALE_TRANSLATABLESTRING_H

#include <QString>

namespace CalamaresUtils
{
namespace Locale
{

/** @brief A pair of strings, one human-readable, one a key
 *
 * Given an identifier-like string (e.g. "New_York"), makes
 * a human-readable version of that and keeps a copy of the
 * identifier itself.
 *
 * This explicitly uses const char* instead of just being
 * QPair<QString, QString> because the human-readable part
 * may need to be translated through tr(), and that takes a char*
 * C-style strings.
 */
class TranslatableString
{
public:
    /// @brief An empty pair
    TranslatableString() {}
    /// @brief Given an identifier, create the pair
    explicit TranslatableString( const char* s1 );
    explicit TranslatableString( const QString& s );
    TranslatableString( TranslatableString&& t );
    TranslatableString( const TranslatableString& );
    virtual ~TranslatableString();

    /// @brief Give the localized human-readable form
    virtual QString tr() const = 0;
    QString key() const { return m_key; }

    bool operator==( const TranslatableString& other ) const { return m_key == other.m_key; }
    bool operator<( const TranslatableString& other ) const { return m_key < other.m_key; }

protected:
    char* m_human = nullptr;
    QString m_key;
};

}  // namespace Locale
}  // namespace CalamaresUtils

#endif
