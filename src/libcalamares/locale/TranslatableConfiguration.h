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

#ifndef LOCALE_TRANSLATABLECONFIGURATION_H
#define LOCALE_TRANSLATABLECONFIGURATION_H

#include "DllMacro.h"

#include <QLocale>
#include <QMap>
#include <QVariant>

namespace CalamaresUtils
{
namespace Locale
{
/** @brief A human-readable string from a configuration file
 *
 * The configuration files can contain human-readable strings,
 * but those need their own translations and are not supported
 * by QObject::tr or anything else.
 */
class DLLEXPORT TranslatedString
{
public:
    /** @brief Get all the translations connected to @p key
     *
     * Gets map[key] as the "untranslated" form, and then all the
     * keys of the form <key>[lang] are taken as the translation
     * for <lang> of the untranslated form.
     *
     * If @p context is not a nullptr, then that is taken as an
     * indication to **also** use the regular QObject::tr() translation
     * mechanism for these strings. It is recommended to pass in
     * metaObject()->className() as context (from a QObject based class)
     * to give the TranslatedString the same context as other calls
     * to tr() within that class.
     */
    TranslatedString( const QVariantMap& map, const QString& key, const char* context = nullptr );
    /** @brief Not-actually-translated string.
     */
    TranslatedString( const QString& string );
    /// @brief Empty string
    TranslatedString()
        : TranslatedString( QString() )
    {
    }

    /** @brief How many strings (translations) are there?
     *
     * This is always at least 1 (for the untranslated string),
     * but may be more than 1 even when isEmpty() is true --
     * if there is no untranslated version, for instance.
     */
    int count() const { return m_strings.count(); }
    /** @brief Consider this string empty?
     *
     * Only the state of the untranslated string is considered,
     * so count() may be more than 1 even while the string is empty.
     */
    bool isEmpty() const { return m_strings[ QString() ].isEmpty(); }

    /// @brief Gets the string in the current locale
    QString get() const;

    /// @brief Gets the string from the given locale
    QString get( const QLocale& ) const;

private:
    // Maps locale name to human-readable string, "" is English
    QMap< QString, QString > m_strings;
    const char* m_context = nullptr;
};
}  // namespace Locale
}  // namespace CalamaresUtils

#endif
