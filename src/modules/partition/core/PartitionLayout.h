/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2018-2019 Collabora Ltd <arnaud.ferraris@collabora.com>
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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
        QString partUUID;
        QString partType;
        quint64 partAttributes;
        QString partMountPoint;
        FileSystem::Type partFileSystem = FileSystem::Unknown;
        QVariantMap partFeatures;
        CalamaresUtils::Partition::PartitionSize partSize;
        CalamaresUtils::Partition::PartitionSize partMinSize;
        CalamaresUtils::Partition::PartitionSize partMaxSize;

        /// @brief All-zeroes PartitionEntry
        PartitionEntry();
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
                   const QString& uuid,
                   const QString& type,
                   quint64 attributes,
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
