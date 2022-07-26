/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2022 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef LOCALENAMES_H
#define LOCALENAMES_H

#include <QString>

/** @brief parts of a locale-name (e.g. "ar_LY.UTF-8", split apart)
 *
 * These are created from lines in `/usr/share/i18n/SUPPORTED`,
 * which lists all the locales supported by the system (there
 * are also other sources of the same).
 *
 */
struct LocaleNameParts
{
    QString language;  // e.g. "ar"
    QString country;  // e.g. "LY" (may be empty)
    QString region;  // e.g. "@valencia" (may be empty)
    QString encoding;  // e.g. "UTF-8" (may be empty)

    bool isValid() const { return !language.isEmpty(); }
    QString name() const;

    static LocaleNameParts fromName( const QString& name );
};

#endif
