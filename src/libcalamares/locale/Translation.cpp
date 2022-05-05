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

#include "Translation.h"

#include <memory>

struct TranslationSpecialCase
{
    const char* id;  // The Calamares ID for the translation
    const char** regions;

    QLocale::Language language;
    QLocale::Script script;
    QLocale::Country country;

    const char* name;  // Native name, if different from Qt

    constexpr bool customLocale() const { return language != QLocale::Language::AnyLanguage; }
};

/** @brief Handle special cases of Calamares language names
 *
 * If a given @p id (e.g. en_US, or sr@latin) has special handling,
 * put an entry in this table. The QLocale constants are used when a
 * particular @p id needs specific configuration, **if** @p language
 * is not @c AnyLanguage. The @p name is used as a human-readable
 * native name if the Qt name is not suitable.
 *
 * Another form of lookup maps a @p language + a region-identifier
 * to a @p id, running around Qt's neglect of `@region` variants.
 *
 * Examples:
 * - `sr@latin` needs specific Qt Locale settnigs, but the name is OK
 * - Chinese needs a specific name, but the Locale is OK
 */
static const char* serbian_latin_regions[] = { "latin", "latn", nullptr };
static const char* catalan_regions[] = { "valencia", nullptr };
static constexpr const TranslationSpecialCase special_cases[] = {
    { "sr@latin",
      serbian_latin_regions,
      QLocale::Language::Serbian,
      QLocale::Script::LatinScript,
      QLocale::Country::Serbia,
      nullptr },
    // Valencian is a regional variant of Catalan
    { "ca@valencia",
      catalan_regions,
      QLocale::Language::Catalan,
      QLocale::Script::AnyScript,
      QLocale::Country::AnyCountry,
      "Català (València)" },
    // Simplified Chinese, but drop the (China) from the name
    { "zh_CN",
      nullptr,
      QLocale::Language::AnyLanguage,
      QLocale::Script::AnyScript,
      QLocale::Country::AnyCountry,
      "简体中文" },
    // Traditional Chinese, but drop (Taiwan) from the name
    { "zh_TW",
      nullptr,
      QLocale::Language::AnyLanguage,
      QLocale::Script::AnyScript,
      QLocale::Country::AnyCountry,
      "繁體中文" },
    { "oc",
      nullptr,
      QLocale::Language::AnyLanguage,
      QLocale::Script::AnyScript,
      QLocale::Country::AnyCountry,
      "Lenga d'òc" },
};

static inline bool
lookup_region( const QByteArray& region, const char** regions_list )
{
    if ( regions_list )
    {
        while ( *regions_list )
        {
            if ( region == *regions_list )
            {
                return true;
            }
            regions_list++;
        }
    }
    return false;
}

static QString
specialCaseSystemLanguage()
{
    const QByteArray lang_p = qgetenv( "LANG" );
    if ( lang_p.isEmpty() )
    {
        // This will figure out the system language some other way
        return {};
    }

    auto lang_parts = lang_p.split( '@' );
    if ( lang_parts.size() != 2 )
    {
        return {};
    }

    QLocale locale( QString::fromLatin1( lang_p ) );
    auto it
        = std::find_if( std::cbegin( special_cases ),
                        std::cend( special_cases ),
                        [ language = locale.language(), region = lang_parts[ 1 ] ]( const TranslationSpecialCase& s )
                        { return ( s.language == language ) && lookup_region( region, s.regions ); } );
    return ( it != std::cend( special_cases ) ) ? QString::fromLatin1( it->id ) : QString();
}

namespace CalamaresUtils
{
namespace Locale
{

Translation::Translation( QObject* parent )
    : Translation( { specialCaseSystemLanguage() }, LabelFormat::IfNeededWithCountry, parent )
{
}

Translation::Translation( const Id& localeId, LabelFormat format, QObject* parent )
    : QObject( parent )
    , m_locale( getLocale( localeId ) )
    , m_localeId( localeId.name.isEmpty() ? m_locale.name() : localeId.name )
{
    auto it = std::find_if( std::cbegin( special_cases ),
                            std::cend( special_cases ),
                            [ &localeId ]( const TranslationSpecialCase& s ) { return localeId.name == s.id; } );
    const char* name = ( it != std::cend( special_cases ) ) ? it->name : nullptr;

    QString longFormat = QObject::tr( "%1 (%2)" );

    QString languageName = name ? QString::fromUtf8( name ) : m_locale.nativeLanguageName();
    QString englishName = m_locale.languageToString( m_locale.language() );

    if ( languageName.isEmpty() )
    {
        languageName = QString( "* %1 (%2)" ).arg( localeId.name, englishName );
    }

    bool needsCountryName = ( format == LabelFormat::AlwaysWithCountry )
        || ( !name && localeId.name.contains( '_' )
             && QLocale::countriesForLanguage( m_locale.language() ).count() > 1 );
    QString countryName = needsCountryName ? m_locale.nativeCountryName() : QString();
    m_label = needsCountryName ? longFormat.arg( languageName, countryName ) : languageName;
    m_englishLabel = needsCountryName ? longFormat.arg( englishName, QLocale::countryToString( m_locale.country() ) )
                                      : englishName;
}

QLocale
Translation::getLocale( const Id& localeId )
{
    const QString& localeName = localeId.name;
    if ( localeName.isEmpty() )
    {
        return QLocale();
    }

    auto it = std::find_if( std::cbegin( special_cases ),
                            std::cend( special_cases ),
                            [ &localeId ]( const TranslationSpecialCase& s ) { return localeId.name == s.id; } );
    if ( it != std::cend( special_cases ) && it->customLocale() )
    {
        return QLocale( it->language, it->script, it->country );
    }
    return QLocale( localeName );
}

}  // namespace Locale
}  // namespace CalamaresUtils
