/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *  SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
 *  SPDX-License-Identifier: GPL-3.0-or-later
 *
 */
#ifndef LUKSOPENSWAPHOOKCFG_LOSHINFO_H
#define LUKSOPENSWAPHOOKCFG_LOSHINFO_H

#include <QString>

/** @brief Information needed to create a suitable config file
 *
 * The LUKS swap configuration has a handful of keys that need to
 * be written to the config file. This struct holds those keys
 * and can find the key values from Global Storage (where the
 * *partition* module sets them).
 */
struct LOSHInfo
{
    // Member names copied from Python code
    QString swap_outer_uuid;
    QString swap_mapper_name;
    QString mountable_keyfile_device;
    QString swap_device_path;
    QString keyfile_device_mount_options;

    bool isValid() const { return !swap_device_path.isEmpty(); }

    /** @brief Helper method for doing key-value replacements
     *
     * Given a named @p key (e.g. "duck", or "swap_device"), returns the
     * value set for that key. Invalid keys (e.g. "duck") return an empty string.
     */
    QString replacementFor( const QString& key ) const
    {
        if ( key == QStringLiteral( "swap_device" ) )
        {
            return swap_device_path;
        }
        if ( key == QStringLiteral( "crypt_swap_name" ) )
        {
            return swap_mapper_name;
        }
        if ( key == QStringLiteral( "keyfile_device" ) )
        {
            return mountable_keyfile_device;
        }
        if ( key == QStringLiteral( "keyfile_filename" ) )
        {
            return QStringLiteral( "crypto_keyfile.bin" );
        }
        if ( key == QStringLiteral( "keyfile_device_mount_options" ) )
        {
            return keyfile_device_mount_options;
        }
        return QString();
    }

    /** @brief Creates a struct from information already set in GS
     *
     */
    static LOSHInfo fromGlobalStorage();
};

#endif
