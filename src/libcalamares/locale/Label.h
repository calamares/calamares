/* === This file is part of Calamares - <https://github.com/calamares> ===
 * 
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017-2019 Adriaan de Groot <groot@kde.org>
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
 *
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *   License-Filename: LICENSE
 *
 */

#ifndef LOCALE_LABEL_H
#define LOCALE_LABEL_H

#include <QLocale>
#include <QObject>
#include <QString>

namespace CalamaresUtils
{
namespace Locale
{

/**
 * @brief Consistent locale (language + country) naming.
 *
 * Support class to turn locale names (as used by Calamares's
 * translation system) into QLocales, and also into consistent
 * human-readable text labels.
 */
class Label : public QObject
{
    Q_OBJECT

public:
    /** @brief Formatting option for label -- add (country) to label. */
    enum class LabelFormat
    {
        AlwaysWithCountry,
        IfNeededWithCountry
    };

    /** @brief Empty locale. This uses the system-default locale. */
    Label( QObject* parent = nullptr );

    /** @brief Construct from a locale name.
     *
     * The @p localeName should be one that Qt recognizes, e.g. en_US or ar_EY.
     * The @p format determines whether the country name is always present
     * in the label (human-readable form) or only if needed for disambiguation.
     */
    Label( const QString& localeName,
           LabelFormat format = LabelFormat::IfNeededWithCountry,
           QObject* parent = nullptr );


    /** @brief Define a sorting order.
     *
     * Locales are sorted by their id, which means the ISO 2-letter code + country.
     */
    bool operator<( const Label& other ) const { return m_localeId < other.m_localeId; }

    /** @brief Is this locale English?
     *
     * en_US and en (American English) is defined as English. The Queen's
     * English -- proper English -- is relegated to non-English status.
     */
    bool isEnglish() const { return m_localeId == QLatin1String( "en_US" ) || m_localeId == QLatin1String( "en" ); }

    /** @brief Get the human-readable name for this locale. */
    QString label() const { return m_label; }
    /** @brief Get the *English* human-readable name for this locale. */
    QString englishLabel() const { return m_englishLabel; }

    /** @brief Get the Qt locale. */
    QLocale locale() const { return m_locale; }

    QString name() const { return m_locale.name(); }
    QString id() const { return m_localeId; }

    /// @brief Convenience accessor to the language part of the locale
    QLocale::Language language() const { return m_locale.language(); }

    /// @brief Convenience accessor to the country part (if any) of the locale
    QLocale::Country country() const { return m_locale.country(); }

    /** @brief Get a Qt locale for the given @p localeName
     *
     * This special-cases `sr@latin`, which is used as a translation
     * name in Calamares, while Qt recognizes `sr@latn`.
     */
    static QLocale getLocale( const QString& localeName );

protected:
    QLocale m_locale;
    QString m_localeId;  // the locale identifier, e.g. "en_GB"
    QString m_label;  // the native name of the locale
    QString m_englishLabel;
};

}  // namespace Locale
}  // namespace CalamaresUtils

#endif
