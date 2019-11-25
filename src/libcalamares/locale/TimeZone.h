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

#ifndef LOCALE_TIMEZONE_H
#define LOCALE_TIMEZONE_H

#include <QString>

namespace CalamaresUtils
{
namespace Locale
{

/** @brief A pair of strings, one human-readable, one a key
 *
 * Given an identifier-like string (e.g. "New_York"), makes
 * a human-readable version of that and keeps a copy of the
 * identifier itself.
 *
 * This explicitly uses const char* instead of just being
 * QPair<QString, QString> because there is API that needs
 * C-style strings.
 */
class CStringPair
{
public:
    explicit CStringPair(const char *s1);
    CStringPair(CStringPair&& t);
    CStringPair(const CStringPair&) = delete;
    ~CStringPair();

private:
    const char* m_human = nullptr;
    const char* m_key = nullptr;
};

/// @brief A pair of strings for timezone regions (e.g. "America")
class TZRegion : public CStringPair
{
public:
    using CStringPair::CStringPair;
};

/// @brief A pair of strings for specific timezone names (e.g. "New_York")
class TZZone : public CStringPair
{
public:
    using CStringPair::CStringPair;
};

}
}

#endif  // LOCALE_TIMEZONE_H
