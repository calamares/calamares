/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2018 Caio Jordão Carvalho <caiojcarvalho@gmail.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef LISTPHYSICALVOLUMEWIDGETITEM_H
#define LISTPHYSICALVOLUMEWIDGETITEM_H

#include <kpmcore/core/partition.h>

#include <QListWidgetItem>

class ListPhysicalVolumeWidgetItem : public QListWidgetItem
{
public:
    ListPhysicalVolumeWidgetItem( const Partition* partition, bool checked );

    const Partition* partition() const;

private:
    const Partition* m_partition;
};

#endif  // LISTPHYSICALVOLUMEWIDGETITEM_H
