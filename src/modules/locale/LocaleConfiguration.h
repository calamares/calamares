/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017-2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef LOCALECONFIGURATION_H
#define LOCALECONFIGURATION_H

#include <QDebug>
#include <QMap>
#include <QString>

class LocaleConfiguration
{
public:  // TODO: private (but need to be public for tests)
    /** @brief Create a locale with everything set to the given @p localeName
     *
     * Consumers should use fromLanguageAndLocation() instead.
     */
    explicit LocaleConfiguration( const QString& localeName /* "en_US.UTF-8" */ )
        : LocaleConfiguration( localeName, localeName )
    {
    }
    /** @brief Create a locale with language and formats separate
     *
     * Consumers should use fromLanguageAndLocation() instead.
     */
    explicit LocaleConfiguration( const QString& localeName, const QString& formatsName );

    /// @brief Create an empty locale, with nothing set
    explicit LocaleConfiguration();

    /** @brief Create a "sensible" locale configuration for @p language and @p countryCode
     *
     * This method applies some heuristics to pick a good locale (from the list
     * @p availableLocales), along with a good language (for instance, in
     * large countries with many languages, picking a generally used one).
     */
    static LocaleConfiguration
    fromLanguageAndLocation( const QString& language, const QStringList& availableLocales, const QString& countryCode );

    /// Is this an empty (default-constructed and not modified) configuration?
    bool isEmpty() const;

    /** @brief sets language to @p localeName
     *
     * The language may be regionalized, e.g. "nl_BE". Both the language
     * (with region) and BCP47 representation (without region, lowercase)
     * are updated. The BCP47 representation is used by the packages module.
     * See also `packages.conf` for a discussion of how this is used.
     */
    void setLanguage( const QString& localeName );
    /// Current language (including region)
    QString language() const { return m_lang; }
    /// Current language (lowercase, BCP47 format, no region)
    QString toBcp47() const { return m_languageLocaleBcp47; }

    QMap< QString, QString > toMap() const;

    // These become all uppercase in locale.conf, but we keep them lowercase here to
    // avoid confusion with <locale.h>, which defines (e.g.) LC_NUMERIC macro.
    QString lc_numeric, lc_time, lc_monetary, lc_paper, lc_name, lc_address, lc_telephone, lc_measurement,
        lc_identification;

    // If the user has explicitly selected language (from the dialog)
    // or numbers format, set these to avoid implicit changes to them.
    bool explicit_lang, explicit_lc;

private:
    QString m_lang;
    QString m_languageLocaleBcp47;
};

inline QDebug&
operator<<( QDebug& s, const LocaleConfiguration& l )
{
    return s << l.language() << '(' << l.toBcp47() << ") +" << l.lc_numeric;
}

#endif  // LOCALECONFIGURATION_H
