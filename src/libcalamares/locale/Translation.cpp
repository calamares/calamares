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
specialCase( const CalamaresUtils::Locale::Translation::Id& locale )
{
    const QString localeName = locale.name;
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
    if ( localeName == "zh_CN" )
    {
        // Simplified Chinese, but drop the (China) from the name
        static QString name = QStringLiteral( "简体中文" );
        return { nullptr, &name };
    }
    if ( localeName == "zh_TW" )
    {
        // Traditional Chinese, but drop (Taiwan) from the name
        static QString name = QStringLiteral( "繁體中文" );
        return { nullptr, &name };
    }

    return { nullptr, nullptr };
}

static QString
specialCaseSystemLanguage()
{
    const QByteArray lang_p = qgetenv( "LANG" );
    if ( lang_p.isEmpty() )
        return {};
    QString lang = QString::fromLatin1( lang_p );
    if ( lang.isEmpty() )
        return {};

    const QString serbian_latin = QStringLiteral( "sr@latin" );
    const QString serbian_latin_variant = QStringLiteral( "sr@latn" );
    if ( ( lang == serbian_latin ) || ( lang == serbian_latin_variant ) )
    {
        return serbian_latin;
    }

    const QString valencian = QStringLiteral( "ca@valencia" );
    if ( lang == valencian )
    {
        return valencian;
    }

    return {};
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
    auto [ _, name ] = specialCase( localeId );

    QString longFormat = QObject::tr( "%1 (%2)" );

    QString languageName = name ? *name : m_locale.nativeLanguageName();
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

    auto [ locale, _ ] = specialCase( localeId );
    return locale ? *locale : QLocale( localeName );
}

}  // namespace Locale
}  // namespace CalamaresUtils
