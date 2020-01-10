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

#ifndef LOCALE_LOOKUP_H
#define LOCALE_LOOKUP_H

#include "DllMacro.h"

#include <QLocale>
#include <QPair>

namespace CalamaresUtils
{
namespace Locale
{
/* All the functions in this file do lookups of locale data
 * based on CLDR tables; these are lookups that you can't (easily)
 * do with just QLocale (e.g. from 2-letter country code to a likely
 * locale).
 */

/// @brief Map a 2-letter code to a Country, or AnyCountry if not found
DLLEXPORT QLocale::Country countryForCode( const QString& code );
/** @brief Map a Country to a Language, or AnyLanguage if not found
 *
 * This is a *likely* language for the given country, based on the
 * CLDR tables. For instance, this maps Belgium to Dutch.
 */
DLLEXPORT QLocale::Language languageForCountry( QLocale::Country country );
/// @brief Map a 2-letter code to a Language, or AnyLanguage if not found
DLLEXPORT QLocale::Language languageForCountry( const QString& code );

/// @brief Get both Country and Language for a 2-letter code
DLLEXPORT QPair< QLocale::Country, QLocale::Language > countryData( const QString& code );
/// @brief Get a likely locale for a 2-letter country code
DLLEXPORT QLocale countryLocale( const QString& code );
}  // namespace Locale
}  // namespace CalamaresUtils

#endif
