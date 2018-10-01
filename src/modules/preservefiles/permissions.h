/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *  Copyright (C) 2018 Scott Harvey <scott@spharvey.me>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef PERMISSIONS_H
#define PERMISSIONS_H

#include <QString>

/**
 * @brief The Permissions class takes a QString @p in the form of 
 * <user>:<group>:<permissions>, checks it for validity, and makes the three
 * components available indivdually.
 */
class Permissions
{

public:

    /** @brief Constructor
     * 
     * Splits the string @p at the colon (":") into separate elements for 
     * <user>, <group>, and <value> (permissions), where <value> is returned as
     * an **octal** integer.
     */
    Permissions(QString p);
    
    /** @brief Default constructor of an invalid Permissions. */
    Permissions();

    bool isValid() const { return m_valid; }
    QString username() const { return m_username; }
    QString group() const { return m_group; }
    int value() const { return m_value; }
    QString octal() const { return QString::number( m_value, 8 ); }

private:
    void parsePermissions(QString const &p);

    QString m_username;
    QString m_group;
    bool m_valid;
    int m_value;

};

#endif // PERMISSIONS_H
