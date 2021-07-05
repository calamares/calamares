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
        quint64 partAttributes = 0;
        QString partMountPoint;
        FileSystem::Type partFileSystem = FileSystem::Unknown;
        QVariantMap partFeatures;
        CalamaresUtils::Partition::PartitionSize partSize;
        CalamaresUtils::Partition::PartitionSize partMinSize;
        CalamaresUtils::Partition::PartitionSize partMaxSize;

        /// @brief All-zeroes PartitionEntry
        PartitionEntry();
        /** @brief Parse @p mountPoint, @p size, @p minSize and @p maxSize to their respective member variables
         *
         * Sets a specific FS type (not parsed from string like the other
         * constructor).
         */
        PartitionEntry( FileSystem::Type fs,
                        const QString& mountPoint,
                        const QString& size,
                        const QString& minSize = QString(),
                        const QString& maxSize = QString() );
        /// @brief All-field PartitionEntry
        PartitionEntry( const QString& label,
                        const QString& uuid,
                        const QString& type,
                        quint64 attributes,
                        const QString& mountPoint,
                        const QString& fs,
                        const QVariantMap& features,
                        const QString& size,
                        const QString& minSize = QString(),
                        const QString& maxSize = QString() );
        /// @brief Copy PartitionEntry
        PartitionEntry( const PartitionEntry& e ) = default;

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
    PartitionLayout( const PartitionLayout& layout );
    ~PartitionLayout();

    /** @brief create the configuration from @p config
     *
     * @p config is a list of partition entries (in QVariant form,
     * read from YAML). If no entries are given, then a single
     * partition is created with type Unkown.
     *
     * Any partitions with FS type Unknown will get the default filesystem
     * that is set at **apply** time (e.g. when createPartitions() is
     * called as well.
     *
     * @see setDefaultFsType()
     */
    void init( FileSystem::Type defaultFsType, const QVariantList& config );
    /** @brief add an entry as if it had been listed in the config
     *
     * The same comments about filesystem type apply.
     */
    bool addEntry( const PartitionEntry& entry );

    /** @brief set the default filesystem type
     *
     * Any partitions in the layout with type Unknown will get
     * the default type when createPartitions() is called.
     */
    void setDefaultFsType( FileSystem::Type defaultFsType );

    /**
     * @brief Apply the current partition layout to the selected drive space.
     * @return  A list of Partition objects.
     */
    QList< Partition* > createPartitions( Device* dev,
                                          qint64 firstSector,
                                          qint64 lastSector,
                                          QString luksPassphrase,
                                          PartitionNode* parent,
                                          const PartitionRole& role );

private:
    QList< PartitionEntry > m_partLayout;
    FileSystem::Type m_defaultFsType = FileSystem::Type::Unknown;
};

#endif /* PARTITIONLAYOUT_H */
