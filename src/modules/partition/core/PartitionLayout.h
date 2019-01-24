/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2018, Collabora Ltd
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

#ifndef PARTITIONLAYOUT_H
#define PARTITIONLAYOUT_H

#include "Typedefs.h"

// KPMcore
#include <kpmcore/core/partitiontable.h>

// Qt
#include <QList>
#include <QObject>

class Partition;

class PartitionLayout
{
public:

    enum SizeUnit
    {
        Percent = 0,
        Byte,
        KiB,
        MiB,
        GiB
    };

    struct PartitionEntry
    {
        QString partLabel;
        QString partMountPoint;
        int partFileSystem;
        double partSize;
        SizeUnit partSizeUnit;
        double partMinSize;
        SizeUnit partMinSizeUnit;
    };

    PartitionLayout();
    PartitionLayout( PartitionEntry entry );
    PartitionLayout( const PartitionLayout& layout );
    ~PartitionLayout();

    void addEntry( PartitionEntry entry );
    void addEntry( QString mountPoint, QString size, QString min = "" );
    void addEntry( QString label, QString mountPoint, QString fs, QString size, QString min = "" );

    /**
     * @brief Apply the current partition layout to the selected drive space.
     * @return  A list of Partition objects.
     */
    QList< Partition* > execute( Device *dev, qint64 firstSector, qint64 lastSector, QString luksPassphrase, PartitionNode* parent, const PartitionRole& role );

private:
    QList< PartitionEntry > partLayout;
};

#endif /* PARTITIONLAYOUT_H */
