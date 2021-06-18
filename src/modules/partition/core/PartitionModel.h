/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2017 2019, Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */
#ifndef PARTITIONMODEL_H
#define PARTITIONMODEL_H

#include "OsproberEntry.h"

// Qt
#include <QAbstractItemModel>
#include <QMutex>

class Device;
class Partition;
class PartitionNode;

/**
 * A Qt tree model which exposes the partitions of a device.
 *
 * Its depth is only more than 1 if the device has extended partitions.
 *
 * Note on updating:
 *
 * The Device class does not notify the outside world of changes on the
 * Partition objects it owns. Since a Qt model must notify its views *before*
 * and *after* making changes, it is important to make use of
 * the PartitionModel::ResetHelper class to wrap changes.
 *
 * This is what PartitionCoreModule does when it create jobs.
 */
class PartitionModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    /**
     * This helper class must be instantiated on the stack *before* making
     * changes to the device represented by this model. It will cause the model
     * to Q_EMIT modelAboutToBeReset() when instantiated and modelReset() when
     * destructed.
     */
    class ResetHelper
    {
    public:
        ResetHelper( PartitionModel* model );
        ~ResetHelper();

        ResetHelper( const ResetHelper& ) = delete;
        ResetHelper& operator=( const ResetHelper& ) = delete;

    private:
        PartitionModel* m_model;
    };

    enum
    {
        // The raw size, as a qlonglong. This is different from the DisplayRole of
        // SizeColumn, which is a human-readable string.
        SizeRole = Qt::UserRole + 1,
        IsFreeSpaceRole,
        IsPartitionNewRole,
        FileSystemLabelRole,
        FileSystemTypeRole,
        PartitionPathRole,
        PartitionPtrRole,  // passed as void*, use sparingly
        OsproberNameRole,
        OsproberPathRole,
        OsproberCanBeResizedRole,
        OsproberRawLineRole,
        OsproberHomePartitionPathRole
    };

    enum Column
    {
        NameColumn,
        FileSystemColumn,
        FileSystemLabelColumn,
        MountPointColumn,
        SizeColumn,
        ColumnCount  // Must remain last
    };

    PartitionModel( QObject* parent = nullptr );
    /**
     * device must remain alive for the life of PartitionModel
     */
    void init( Device* device, const OsproberEntryList& osproberEntries );

    // QAbstractItemModel API
    QModelIndex index( int row, int column, const QModelIndex& parent = QModelIndex() ) const override;
    QModelIndex parent( const QModelIndex& child ) const override;
    int columnCount( const QModelIndex& parent = QModelIndex() ) const override;
    int rowCount( const QModelIndex& parent = QModelIndex() ) const override;
    QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const override;
    QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const override;

    Partition* partitionForIndex( const QModelIndex& index ) const;

    Device* device() const { return m_device; }

    void update();

private:
    friend class ResetHelper;

    Device* m_device;
    OsproberEntryList m_osproberEntries;
    mutable QMutex m_lock;
};

#endif /* PARTITIONMODEL_H */
