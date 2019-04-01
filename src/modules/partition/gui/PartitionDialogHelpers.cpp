/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
 *   Copyright 2016, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2018-2019 Adriaan de Groot <groot@kde.org>
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
    QStringList mountPoints{ "/", "/boot", "/home", "/opt", "/srv", "/usr", "/var" };
    if ( PartUtils::isEfiSystem() )
        mountPoints << Calamares::JobQueue::instance()->globalStorage()->value( "efiSystemPartition" ).toString();
    mountPoints.removeDuplicates();
    mountPoints.sort();
    return mountPoints;
}

void
standardMountPoints(QComboBox& combo)
{
    combo.clear();
    combo.addItem( QObject::tr( "(no mount point)" ) );
    combo.addItems( standardMountPoints() );
}

void
standardMountPoints(QComboBox& combo, const QString& selected)
{
    standardMountPoints( combo );
    setSelectedMountPoint( combo, selected );
}

QString
selectedMountPoint(QComboBox& combo)
{
    if ( combo.currentIndex() == 0 )
        return QString();
    return combo.currentText();
}

void
setSelectedMountPoint(QComboBox& combo, const QString& selected)
{
    if ( selected.isEmpty() )
        combo.setCurrentIndex( 0 );  // (no mount point)
    else
    {
        for ( int i = 0; i < combo.count(); ++i )
            if ( selected == combo.itemText( i ) )
            {
                combo.setCurrentIndex( i );
                return;
            }
        combo.addItem( selected );
        combo.setCurrentIndex( combo.count() - 1);
    }
}


PartitionTable::Flags
flagsFromList( const QListWidget& list )
{
    PartitionTable::Flags flags;

    for ( int i = 0; i < list.count(); i++ )
        if ( list.item( i )->checkState() == Qt::Checked )
            flags |= static_cast< PartitionTable::Flag >(
                         list.item( i )->data( Qt::UserRole ).toInt() );

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
            item->setCheckState( ( checked & f ) ?
                                     Qt::Checked :
                                     Qt::Unchecked );
        }

        f <<= 1;
    }
}
