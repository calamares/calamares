/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017-2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#ifndef LOCALE_TRANSLATION_H
#define LOCALE_TRANSLATION_H

#include "utils/Logger.h"

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
 *
 * This handles special-cases in Calamares translations:
 * - `sr@latin` is the name which Qt recognizes as `sr@latn`,
 *   Serbian written with Latin characters (not Cyrillic).
 * - `ca@valencia` is the Catalan dialect spoken in Valencia.
 *   There is no Qt code for it.
 */
class Translation : public QObject
{
    Q_OBJECT

public:
    /** @brief Formatting option for label -- add (country) to label. */
    enum class LabelFormat
    {
        AlwaysWithCountry,
        IfNeededWithCountry
    };

    struct Id
    {
        QString name;
    };

    /** @brief Empty locale. This uses the system-default locale. */
    Translation( QObject* parent = nullptr );

    /** @brief Construct from a locale name.
     *
     * The @p localeName should be one that Qt recognizes, e.g. en_US or ar_EY.
     * The @p format determines whether the country name is always present
     * in the label (human-readable form) or only if needed for disambiguation.
     */
    Translation( const Id& localeId, LabelFormat format = LabelFormat::IfNeededWithCountry, QObject* parent = nullptr );


    /** @brief Define a sorting order.
     *
     * Locales are sorted by their id, which means the ISO 2-letter code + country.
     */
    bool operator<( const Translation& other ) const { return m_localeId < other.m_localeId; }

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

    /** @brief Gets the Calamares internal name (code) of the locale.
     *
     * This is a strongly-typed return to avoid it ending up all over
     * the place as a QString.
     */
    Id id() const { return { m_localeId }; }

    /// @brief Convenience accessor to the language part of the locale
    QLocale::Language language() const { return m_locale.language(); }

    /// @brief Convenience accessor to the country part (if any) of the locale
    QLocale::Country country() const { return m_locale.country(); }

    /** @brief Get a Qt locale for the given @p localeName
     *
     * This obeys special cases as described in the class documentation.
     */
    static QLocale getLocale( const Id& localeId );

private:
    QLocale m_locale;
    QString m_localeId;  // the locale identifier, e.g. "en_GB"
    QString m_label;  // the native name of the locale
    QString m_englishLabel;
};

static inline QDebug&
operator<<( QDebug& s, const Translation::Id& id )
{
    return s << id.name;
}
static inline bool
operator==( const Translation::Id& lhs, const Translation::Id& rhs )
{
    return lhs.name == rhs.name;
}

}  // namespace Locale
}  // namespace CalamaresUtils

#endif
