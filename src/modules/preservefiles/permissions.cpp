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

#include <QString>
#include <QStringList>
#include "permissions.h"

Permissions::Permissions() :
    m_username(),
    m_group(),
    m_valid(false),
    m_value(0)
{
}


Permissions::Permissions(QString p) : Permissions()
{
    parsePermissions(p);
}

void Permissions::parsePermissions(const QString& p) {

    QStringList segments = p.split(":");

    if (segments.length() != 3) {
        m_valid = false;
        return;
    }

    if (segments[0].isEmpty() || segments[1].isEmpty()) {
        m_valid = false;
        return;
    }

    bool ok;
    int octal = segments[2].toInt(&ok, 8);
    if (!ok || octal == 0) {
        m_valid = false;
        return;
    } else {
        m_value = octal;
    }

    // We have exactly three segments and the third is valid octal,
    // so we can declare the string valid and set the user and group names
    m_valid = true;
    m_username = segments[0];
    m_group = segments[1];

    return;

}






