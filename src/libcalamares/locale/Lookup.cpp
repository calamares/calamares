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

#include "Lookup.h"

// No data yet

namespace Calamares
{
    
QLocale::Country countryForCode(const QString& code)
{
    return QLocale::Country::AnyCountry;
}

QLocale countryLocale(const QString& code)
{
    return QLocale();
}

QLocale::Language languageForCountry(const QString& code)
{
    return QLocale::Language::AnyLanguage;
}

QLocale::Language languageForCountry(QLocale::Country country)
{
    return QLocale::Language::AnyLanguage;
}

QPair<QLocale::Country, QLocale::Language> countryData(const QString& code)
{
    return qMakePair( QLocale::Country::AnyCountry, QLocale::Language::AnyLanguage );
}

}  // namespace
