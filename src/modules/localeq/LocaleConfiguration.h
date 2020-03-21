/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2016, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017-2019, Adriaan de Groot <groot@kde.org>
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

#ifndef LOCALECONFIGURATION_H
#define LOCALECONFIGURATION_H

#include <QDebug>
#include <QMap>
#include <QString>

class LocaleConfiguration
{
public:
    /// @brief Create an empty locale, with nothing set
    explicit LocaleConfiguration();
    /// @brief Create a locale with everything set to the given @p localeName
    explicit LocaleConfiguration( const QString& localeName /* "en_US.UTF-8" */ )
        : LocaleConfiguration( localeName, localeName )
    {
    }
    /// @brief Create a locale with language and formats separate
    explicit LocaleConfiguration( const QString& localeName, const QString& formatsName );

    static LocaleConfiguration
    fromLanguageAndLocation( const QString& language, const QStringList& availableLocales, const QString& countryCode );

    bool isEmpty() const;

    /** @brief sets lang and the BCP47 representation
     *
     * Note that the documentation how this works is in packages.conf
     */
    void setLanguage( const QString& localeName );
    QString language() const { return m_lang; }

    // Note that the documentation how this works is in packages.conf
    QString toBcp47() const { return m_languageLocaleBcp47; }

    QMap< QString, QString > toMap() const;

    // These become all uppercase in locale.conf, but we keep them lowercase here to
    // avoid confusion with locale.h.
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
