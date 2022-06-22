/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

/** @file GlobalStorage management for Locale settings
 *
 * The *localeConf* key in Global Storage is semi-structured,
 * and there are multiple modules that write to it (and some that
 * read from it). Functions in this file provide access to
 * that semi-structured data.
 */

#ifndef LOCALE_GLOBAL_H
#define LOCALE_GLOBAL_H

#include "DllMacro.h"

#include <QMap>
#include <QString>
#include <QVariantMap>

namespace Calamares
{
class GlobalStorage;
}

namespace CalamaresUtils
{
namespace Locale
{

/** @brief Selector for methods that insert multiple values.
 *
 * When inserting, use @c Overwrite to remove all keys not in the collection
 * of values being inserted; use @c Merge to preserve whatever is
 * already in Global Storage but not mentioned in the collection.
 */
enum class InsertMode
{
    Overwrite,
    Merge
};

/** @brief Insert the given @p values into the *localeConf* map in @p gs
 *
 * @param gs      The Global Storage to write to
 * @param values  The collection of keys and values to write to @p gs
 * @param mode    Indicates whether the *localeConf* key is cleared first
 *
 * The keys in the collection @p values should be first-level keys
 * in *localeConf*, e.g. "LANG" or "LC_TIME". No effort is made to
 * enforce this.
 */
DLLEXPORT void insertGS( Calamares::GlobalStorage& gs, const QVariantMap& values, InsertMode mode = InsertMode::Merge );
/** @brief Insert the given @p values into the *localeConf* map in @p gs
 *
 * Alternate way of providing the keys and values.
 */
DLLEXPORT void
insertGS( Calamares::GlobalStorage& gs, const QMap< QString, QString >& values, InsertMode mode = InsertMode::Merge );
/** @brief Write a single @p key and @p value to the *localeConf* map
 */
DLLEXPORT void insertGS( Calamares::GlobalStorage& gs, const QString& key, const QString& value );
/** @brief Remove a single @p key from the *localeConf* map
 */
DLLEXPORT void removeGS( Calamares::GlobalStorage& gs, const QString& key );
/** @brief Remove the *localeConf* map from Global Storage
 */
DLLEXPORT void clearGS( Calamares::GlobalStorage& gs );

}  // namespace Locale
}  // namespace CalamaresUtils

#endif
