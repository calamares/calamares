/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
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
