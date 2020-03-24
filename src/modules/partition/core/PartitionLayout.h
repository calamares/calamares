/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2018-2019, Collabora Ltd <arnaud.ferraris@collabora.com>
 *   Copyright 2019, Adriaan de Groot <groot@kde.org>
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

#include "partition/PartitionSize.h"

#include "core/PartUtils.h"

// KPMcore
#include <kpmcore/core/partitiontable.h>
#include <kpmcore/fs/filesystem.h>

// Qt
#include <QList>
#include <QObject>
#include <QVariantMap>

class Partition;

class PartitionLayout
{
public:
    struct PartitionEntry
    {
        QString partLabel;
        QString partType;
        QString partMountPoint;
        FileSystem::Type partFileSystem = FileSystem::Unknown;
        QVariantMap partFeatures;
        CalamaresUtils::Partition::PartitionSize partSize;
        CalamaresUtils::Partition::PartitionSize partMinSize;
        CalamaresUtils::Partition::PartitionSize partMaxSize;

        /// @brief All-zeroes PartitionEntry
        PartitionEntry() {}
        /// @brief Parse @p size, @p min and @p max to their respective member variables
        PartitionEntry( const QString& size, const QString& min, const QString& max );

        bool isValid() const
        {
            if ( !partSize.isValid()
                 || ( partMinSize.isValid() && partMaxSize.isValid() && partMinSize > partMaxSize ) )
            {
                return false;
            }
            return true;
        }
    };

    PartitionLayout();
    PartitionLayout( PartitionEntry entry );
    PartitionLayout( const PartitionLayout& layout );
    ~PartitionLayout();

    bool addEntry( PartitionEntry entry );
    bool addEntry( const QString& mountPoint,
                   const QString& size,
                   const QString& min = QString(),
                   const QString& max = QString() );
    bool addEntry( const QString& label,
                   const QString& type,
                   const QString& mountPoint,
                   const QString& fs,
                   const QVariantMap& features,
                   const QString& size,
                   const QString& min = QString(),
                   const QString& max = QString() );

    /**
     * @brief Apply the current partition layout to the selected drive space.
     * @return  A list of Partition objects.
     */
    QList< Partition* > execute( Device* dev,
                                 qint64 firstSector,
                                 qint64 lastSector,
                                 QString luksPassphrase,
                                 PartitionNode* parent,
                                 const PartitionRole& role );

private:
    FileSystem::Type m_defaultFsType;
    QList< PartitionEntry > m_partLayout;
};

#endif /* PARTITIONLAYOUT_H */
