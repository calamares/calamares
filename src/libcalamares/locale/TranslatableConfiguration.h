/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

/** @file Run-time translation of strings from configuration files
 *
 * The TranslatedString class provides a way of doing run-time
 * lookups of human-readable strings, from data provided in
 * the configuration files (*.conf) for Calamares. This acts
 * like "normal" translation through tr() calls, as far as the
 * user-visible part goes.
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
     *
     * The @p context, if any, should point to static data; it is
     * **not** owned by the TranslatedString.
     */
    TranslatedString( const QVariantMap& map, const QString& key, const char* context = nullptr );
    /** @brief Not-actually-translated string.
     */
    TranslatedString( const QString& string );
    /** @brief Proxy for calling QObject::tr()
     *
     * This is like the two constructors above, with an empty map an a
     * non-null context. It will end up calling tr() with that context.
     *
     * The @p context, if any, should point to static data; it is
     * **not** owned by the TranslatedString.
     */
    TranslatedString( const QString& key, const char* context );
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
