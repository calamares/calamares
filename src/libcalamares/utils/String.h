/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2013-2016, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2018, Adriaan de Groot <groot@kde.org>
 *
 *   Originally from Tomahawk, portions:
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2010-2011, Leo Franchi <lfranchi@kde.org>
 *   Copyright 2010-2012, Jeff Mitchell <jeff@tomahawk-player.org>
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

#ifndef UTILS_STRING_H
#define UTILS_STRING_H

#include "DllMacro.h"

#include <QString>

/**
 * @brief The CalamaresUtils namespace contains utility functions.
 */
namespace CalamaresUtils
{
/**
 * @brief removeDiacritics replaces letters with diacritics and ligatures with
 * alternative forms and digraphs.
 * @param string the string to transform.
 * @return the output string with plain characters.
 */
DLLEXPORT QString removeDiacritics( const QString& string );

/**
 * @brief obscure is a bidirectional obfuscation function, from KStringHandler.
 * @param string the input string.
 * @return the obfuscated string.
 */
DLLEXPORT QString obscure( const QString& string );
}  // namespace CalamaresUtils

#endif
