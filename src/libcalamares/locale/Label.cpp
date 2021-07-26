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

#include "Label.h"

#include <memory>

/** @brief Handle special cases of Calamares language names
 *
 * If a given @p localeName (e.g. en_US, or sr@latin) has special handling,
 * returns a pair of pointers:
 * - a pointer to a QLocale; this is the locale to use, or may be @c nullptr
 *   to indicate that the Qt locale derived from @p localeName is accepatable.
 * - a pointer to a QString; this is the native language name to use, or may
 *   be @c nullptr to indicate that the Qt value is acceptable.
 *
 * Returns a pair of nullptrs for non-special cases.
 */
static std::pair< QLocale*, QString* >
specialCase( const QString& localeName )
{
    if ( localeName == "sr@latin" )
    {
        static QLocale loc( QLocale::Language::Serbian, QLocale::Script::LatinScript, QLocale::Country::Serbia );
        return { &loc, nullptr };
    }
    if ( localeName == "ca@valencia" )
    {
        static QString name = QStringLiteral( "Català (València)" );
        return { nullptr, &name };
    }

    return { nullptr, nullptr };
}

namespace CalamaresUtils
{
namespace Locale
{

Label::Label( QObject* parent )
    : Label( QString(), LabelFormat::IfNeededWithCountry, parent )
{
}

Label::Label( const QString& locale, LabelFormat format, QObject* parent )
    : QObject( parent )
    , m_locale( Label::getLocale( locale ) )
    , m_localeId( locale.isEmpty() ? m_locale.name() : locale )
{
    auto special = specialCase( locale );

    QString longFormat = QObject::tr( "%1 (%2)" );

    QString languageName = special.second ? *special.second : m_locale.nativeLanguageName();
    QString englishName = m_locale.languageToString( m_locale.language() );

    if ( languageName.isEmpty() )
    {
        languageName = QString( "* %1 (%2)" ).arg( locale, englishName );
    }

    bool needsCountryName = ( format == LabelFormat::AlwaysWithCountry )
        || ( locale.contains( '_' ) && QLocale::countriesForLanguage( m_locale.language() ).count() > 1 );
    QString countryName = ( needsCountryName ?

                                             m_locale.nativeCountryName()
                                             : QString() );
    m_label = needsCountryName ? longFormat.arg( languageName, countryName ) : languageName;
    m_englishLabel = needsCountryName ? longFormat.arg( englishName, QLocale::countryToString( m_locale.country() ) )
                                      : englishName;
}

QLocale
Label::getLocale( const QString& localeName )
{
    if ( localeName.isEmpty() )
    {
        return QLocale();
    }

    auto special = specialCase( localeName );
    return special.first ? *special.first : QLocale( localeName );
}

}  // namespace Locale
}  // namespace CalamaresUtils
