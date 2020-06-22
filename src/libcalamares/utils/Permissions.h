/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *  SPDX-FileCopyrightText: 2018 Scott Harvey <scott@spharvey.me>
 *  SPDX-License-Identifier: GPL-3.0-or-later
 *  License-Filename: LICENSE
 *
 */

#ifndef LIBCALAMARES_PERMISSIONS_H
#define LIBCALAMARES_PERMISSIONS_H

#include "DllMacro.h"

#include <QString>

/**
 * @brief The Permissions class takes a QString @p in the form of
 * <user>:<group>:<permissions>, checks it for validity, and makes the three
 * components available indivdually.
 */
class DLLEXPORT Permissions
{

public:
    /** @brief Constructor
     *
     * Splits the string @p at the colon (":") into separate elements for
     * <user>, <group>, and <value> (permissions), where <value> is returned as
     * an **octal** integer.
     */
    Permissions( QString p );

    /** @brief Default constructor of an invalid Permissions. */
    Permissions();

    bool isValid() const { return m_valid; }
    QString username() const { return m_username; }
    QString group() const { return m_group; }
    int value() const { return m_value; }
    QString octal() const { return QString::number( m_value, 8 ); }

private:
    void parsePermissions( QString const& p );

    QString m_username;
    QString m_group;
    bool m_valid;
    int m_value;
};

#endif  // LIBCALAMARES_PERMISSIONS_H
