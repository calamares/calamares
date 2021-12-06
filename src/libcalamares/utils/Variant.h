/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2013-2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#ifndef UTILS_VARIANT_H
#define UTILS_VARIANT_H

#include "DllMacro.h"

#include <QList>
#include <QString>
#include <QVariantMap>

namespace CalamaresUtils
{
/**
 * Get a bool value from a mapping with a given key; returns @p d if no value.
 */
DLLEXPORT bool getBool( const QVariantMap& map, const QString& key, bool d = false );

/** @brief Get a string value from a mapping with a given key; returns @p d if no value.
 *
 * The value must be an actual string; numbers are not automatically converted to strings,
 * nor are lists flattened or converted.
 */
DLLEXPORT QString getString( const QVariantMap& map, const QString& key, const QString& d = QString() );

/** @brief Get a string list from a mapping with a given key; returns @p d if no value.
 *
 * This is slightly more lenient than getString(), and a single-string value will
 * be returned as a 1-item list.
 */
DLLEXPORT QStringList getStringList( const QVariantMap& map, const QString& key, const QStringList& d = QStringList() );

/**
 * Get a list from a mapping with a given key; returns @p d if no value.
 */
DLLEXPORT QList< QVariant >
getList( const QVariantMap& map, const QString& key, const QList< QVariant >& d = QList< QVariant >() );

/**
 * Get an integer value from a mapping with a given key; returns @p d if no value.
 */
DLLEXPORT qint64 getInteger( const QVariantMap& map, const QString& key, qint64 d = 0 );

/**
 * Get an unsigned integer value from a mapping with a given key; returns @p d if no value.
 */
DLLEXPORT quint64 getUnsignedInteger( const QVariantMap& map, const QString& key, quint64 d = 0 );

/**
 * Get a double value from a mapping with a given key (integers are converted); returns @p d if no value.
 */
DLLEXPORT double getDouble( const QVariantMap& map, const QString& key, double d = 0.0 );

/**
 * Returns a sub-map (i.e. a nested map) from a given mapping with a
 * given key. @p success is set to true if the @p key exists
 * in @p map and converts to a map, false otherwise.
 *
 * Returns @p d if there is no such key or it is not a map-value.
 * (e.g. if @p success is false).
 */
DLLEXPORT QVariantMap getSubMap( const QVariantMap& map,
                                 const QString& key,
                                 bool& success,
                                 const QVariantMap& d = QVariantMap() );
}  // namespace CalamaresUtils

#endif
