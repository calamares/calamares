/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2016, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2018, Adriaan de Groot <groot@kde.org>
 *
 *   Calamares is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Calamares is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Calamares. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef OSPROBERENTRY_H
#define OSPROBERENTRY_H

#include <QStringList>

struct FstabEntry
{
    QString partitionNode;
    QString mountPoint;
    QString fsType;
    QString options;
    int dump;
    int pass;

    /// Does this entry make sense and is it complete?
    bool isValid() const;  // implemented in Partutils.cpp

    /** @brief Create an entry from a live of /etc/fstab
     *
     * Splits the given string (which ought to follow the format
     * of /etc/fstab) and returns a corresponding Fstab entry.
     * If the string isn't valid (e.g. comment-line, or broken
     * fstab entry) then the entry that is returned is invalid.
     */
    static FstabEntry fromEtcFstab( const QString& );  // implemented in Partutils.cpp
};

typedef QList< FstabEntry > FstabEntryList;

struct OsproberEntry
{
    QString prettyName;
    QString path;
    QString uuid;
    bool canBeResized;
    QStringList line;
    FstabEntryList fstab;
    QString homePath;
};

typedef QList< OsproberEntry > OsproberEntryList;

#endif  // OSPROBERENTRY_H
