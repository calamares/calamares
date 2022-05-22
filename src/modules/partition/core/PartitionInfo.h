/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */
#ifndef PARTITIONINFO_H
#define PARTITIONINFO_H

#include <QHash>
#include <QString>

#include <kpmcore/core/partitiontable.h>

class Partition;

/**
 * Functions to store Calamares-specific information in the Qt properties of a
 * Partition object.
 *
 * See README.md for the rational behind this design.
 *
 * Properties:
 * - mountPoint: which directory will a partition be mounted on the installed
 *   system. This is different from Partition::mountPoint, which is the
 *   directory on which a partition is *currently* mounted while the installer
 *   is running.
 * - format: whether this partition should be formatted at install time.
 */
namespace PartitionInfo
{

QString mountPoint( const Partition* partition );
void setMountPoint( Partition* partition, const QString& value );

bool format( const Partition* partition );
void setFormat( Partition* partition, bool value );

PartitionTable::Flags flags( const Partition* partition );
void setFlags( Partition* partition, PartitionTable::Flags f );

void reset( Partition* partition );

/**
 * Returns true if one of the property has been set. This information is used
 * by the UI to decide whether the "Revert" button should be enabled or
 * disabled.
 */
bool isDirty( Partition* partition );

};  // namespace PartitionInfo

#endif /* PARTITIONINFO_H */
