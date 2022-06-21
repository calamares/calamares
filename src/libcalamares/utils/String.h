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

namespace Calamares
{
/**
 * @brief The Calamares::String namespace
 *
 * This namespace contains functions related to string-handling,
 * string-expansion, etc.
 */
namespace String
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

/** @brief Parameter for counting lines at beginning and end of string
 *
 * This is used by truncateMultiLine() to indicate how many lines from
 * the beginning and how many from the end should be kept.
 */
struct LinesStartEnd
{
    int atStart = 0;
    int atEnd = 0;
};

/** @brief Parameter for counting characters in truncateMultiLine()
 */
struct CharCount
{
    int total = 0;
};

/** @brief Truncate a string to some reasonable length for display
 *
 * Keep the first few, or last few (or both) lines of a possibly lengthy
 * message @p string and reduce it to a displayable size (e.g. for
 * pop-up windows that display the message). If the message is longer
 * than @p chars, then characters are removed from the front (if
 * @p lines.atStart is zero) or end (if @p lines.atEnd is zero) or in the middle
 * (if both are nonzero).
 *
 * Asking for 0 lines will make this behave like QString::truncate().
 *
 * @param string the input string.
 * @param lines number of lines to preserve.
 * @param chars maximum number of characters in the returned string.
 * @return a string built from parts of the input string.
 */
DLLEXPORT QString truncateMultiLine( const QString& string,
                                     LinesStartEnd lines = LinesStartEnd { 3, 5 },
                                     CharCount chars = CharCount { 812 } );

/** @brief Remove all @p c at the beginning of @p string
 *
 * Modifies the @p string in-place. If @p c is not the first character
 * of @p string, the string is left unchanged; otherwise the first character
 * is removed and the process repeats.
 */
DLLEXPORT void removeLeading( QString& string, QChar c );
/** @brief Remove all @p c at the end of @p string
 *
 * Like removeLeading(), but at the end of the string.
 */
DLLEXPORT void removeTrailing( QString& string, QChar c );

}  // namespace String
}  // namespace Calamares

#endif
