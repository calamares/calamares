/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2013-2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Originally from Tomahawk, portions:
 *   SPDX-FileCopyrightText: 2010-2011 Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   SPDX-FileCopyrightText: 2010-2011 Leo Franchi <lfranchi@kde.org>
 *   SPDX-FileCopyrightText: 2010-2012 Jeff Mitchell <jeff@tomahawk-player.org>
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#ifndef UTILS_STRING_H
#define UTILS_STRING_H

#include "DllMacro.h"

#include <QString>

/* Qt 5.14 changed the API to QString::split(), adding new overloads
 * that take a different enum, then Qt 5.15 deprecated the old ones.
 * To avoid overly-many warnings related to the API change, introduce
 * Calamares-specific constants that pull from the correct enum.
 */
constexpr static const auto SplitSkipEmptyParts =
#if QT_VERSION < QT_VERSION_CHECK( 5, 14, 0 )
    QString::SkipEmptyParts
#else
    Qt::SkipEmptyParts
#endif
    ;

constexpr static const auto SplitKeepEmptyParts =
#if QT_VERSION < QT_VERSION_CHECK( 5, 14, 0 )
    QString::KeepEmptyParts
#else
    Qt::KeepEmptyParts
#endif
    ;

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
