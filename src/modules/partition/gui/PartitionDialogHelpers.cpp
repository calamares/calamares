/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018-2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "PartitionDialogHelpers.h"

#include "core/PartUtils.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/Logger.h"

#include <QComboBox>
#include <QListWidget>

QStringList
standardMountPoints()
{
    QStringList mountPoints { "/", "/home", "/opt", "/srv", "/usr", "/var" };
    if ( PartUtils::isEfiSystem() )
    {
        mountPoints << Calamares::JobQueue::instance()->globalStorage()->value( "efiSystemPartition" ).toString();
    }
    else
    {
        mountPoints << QStringLiteral( "/boot" );
    }
    mountPoints.removeDuplicates();
    mountPoints.sort();
    return mountPoints;
}

void
standardMountPoints( QComboBox& combo )
{
    combo.clear();
    combo.addItem( QObject::tr( "(no mount point)" ) );
    combo.addItems( standardMountPoints() );
}

void
standardMountPoints( QComboBox& combo, const QString& selected )
{
    standardMountPoints( combo );
    setSelectedMountPoint( combo, selected );
}

QString
selectedMountPoint( QComboBox& combo )
{
    if ( combo.currentIndex() == 0 )
    {
        return QString();
    }
    return combo.currentText();
}

void
setSelectedMountPoint( QComboBox& combo, const QString& selected )
{
    if ( selected.isEmpty() )
    {
        combo.setCurrentIndex( 0 );  // (no mount point)
    }
    else
    {
        for ( int i = 0; i < combo.count(); ++i )
        {
            if ( selected == combo.itemText( i ) )
            {
                combo.setCurrentIndex( i );
                return;
            }
        }
        combo.addItem( selected );
        combo.setCurrentIndex( combo.count() - 1 );
    }
}


PartitionTable::Flags
flagsFromList( const QListWidget& list )
{
    PartitionTable::Flags flags;

    for ( int i = 0; i < list.count(); i++ )
    {
        if ( list.item( i )->checkState() == Qt::Checked )
        {
            flags |= static_cast< PartitionTable::Flag >( list.item( i )->data( Qt::UserRole ).toInt() );
        }
    }

    return flags;
}

void
setFlagList( QListWidget& list, PartitionTable::Flags available, PartitionTable::Flags checked )
{
    int f = 1;
    QString s;
    while ( !( s = PartitionTable::flagName( static_cast< PartitionTable::Flag >( f ) ) ).isEmpty() )
    {
        if ( available & f )
        {
            QListWidgetItem* item = new QListWidgetItem( s );
            list.addItem( item );
            item->setFlags( Qt::ItemIsUserCheckable | Qt::ItemIsEnabled );
            item->setData( Qt::UserRole, f );
            item->setCheckState( ( checked & f ) ? Qt::Checked : Qt::Unchecked );
        }

        f <<= 1;
    }
}
