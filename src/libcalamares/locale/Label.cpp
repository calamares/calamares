/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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

#include "Label.h"

namespace CalamaresUtils::Locale
{

Label::Label()
    : m_locale( QLocale() )
{
    m_localeId = m_locale.name();

    setLabels( QString(), LabelFormat::IfNeededWithCountry );
}

Label::Label( const QString& locale, LabelFormat format )
    : m_locale( Label::getLocale( locale ) )
    , m_localeId( locale )
{
    setLabels( locale, format );
}

void
Label::setLabels( const QString& locale, LabelFormat format )
{
    //: language[name] (country[name])
    QString longFormat = QObject::tr( "%1 (%2)" );

    QString languageName = m_locale.nativeLanguageName();
    QString englishName = m_locale.languageToString( m_locale.language() );
    QString countryName;

    if ( languageName.isEmpty() )
        languageName = QString( "* %1 (%2)" ).arg( locale, englishName );

    bool needsCountryName = ( format == LabelFormat::AlwaysWithCountry ) ||
        (locale.contains( '_' ) && QLocale::countriesForLanguage( m_locale.language() ).count() > 1 );

    if ( needsCountryName )
        countryName = m_locale.nativeCountryName();
    m_label = needsCountryName ? longFormat.arg( languageName, countryName ) : languageName;
    m_englishLabel = needsCountryName ? longFormat.arg( englishName, QLocale::countryToString( m_locale.country() ) ) : englishName;
}

QLocale Label::getLocale( const QString& localeName )
{
    if ( localeName.contains( "@latin" ) )
    {
        QLocale loc( localeName );  // Ignores @latin
        return QLocale( loc.language(), QLocale::Script::LatinScript, loc.country() );
    }
    else
        return QLocale( localeName );
}

}  // namespace
