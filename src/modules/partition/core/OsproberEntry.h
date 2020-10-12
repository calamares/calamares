/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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
    QString file;
    QString uuid;
    bool canBeResized;
    QStringList line;
    FstabEntryList fstab;
    QString homePath;
};

typedef QList< OsproberEntry > OsproberEntryList;

#endif  // OSPROBERENTRY_H
