/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *  SPDX-FileCopyrightText: 2018 Scott Harvey <scott@spharvey.me>
 *  SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifndef LIBCALAMARES_PERMISSIONS_H
#define LIBCALAMARES_PERMISSIONS_H

#include "DllMacro.h"

#include <QString>

namespace CalamaresUtils
{

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
     * <user>, <group>, and <value> (permissions), where <value> is interpreted
     * as an **octal** integer. That is, "root:wheel:755" will give
     * you an integer value of four-hundred-ninety-three (493),
     * corresponding to the UNIX file permissions rwxr-xr-x,
     * as one would expect from chmod and other command-line utilities.
     */
    Permissions( QString const& p );

    /// @brief Default constructor of an invalid Permissions.
    Permissions();

    /// @brief Was the Permissions object constructed from valid data?
    bool isValid() const { return m_valid; }
    /// @brief The user (first component, e.g. "root" in "root:wheel:755")
    QString username() const { return m_username; }
    /// @brief The group (second component, e.g. "wheel" in "root:wheel:755")
    QString group() const { return m_group; }
    /** @brief The value (file permission) as an integer.
     *
     * Bear in mind that input is in octal, but integers are just integers;
     * naively printing them will get decimal results (e.g. 493 from the
     * input of "root:wheel:755"). This is suitable to pass to apply().
     */
    int value() const { return m_value; }
    /** @brief The value (file permission) as octal string
     *
     * This is suitable for passing to chmod-the-program, or for
     * recreating the original Permissions string.
     */
    QString octal() const { return QString::number( value(), 8 ); }

    /** @brief Sets the file-access @p mode of @p path
     *
     * Pass a path that is relative (or absolute) in the **host** system.
     *
     * @return @c true on success
     */
    static bool apply( const QString& path, int mode );
    /** @brief Do both chmod and chown on @p path
     *
     * Note that interpreting user- and group- names for applying the
     * permissions can be different between the host system and the target
     * system; the target might not have a "live" user, for instance, and
     * the host won't have the user-entered username for the installation.
     *
     * For this call, the names are interpreted in the **host** system.
     * Pass a path that is relative (or absolute) in the **host** system.
     *
     * @return @c true on success of **both** operations
     */
    static bool apply( const QString& path, const Permissions& p );
    /// Convenience method for apply(const QString&, const Permissions& )
    bool apply( const QString& path ) const { return apply( path, *this ); }

private:
    void parsePermissions( QString const& p );

    QString m_username;
    QString m_group;
    int m_value;
    bool m_valid;
};

}  // namespace CalamaresUtils

#endif  // LIBCALAMARES_PERMISSIONS_H
