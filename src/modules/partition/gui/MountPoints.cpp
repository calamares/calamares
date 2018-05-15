/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
 *   Copyright 2016, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2018, Adriaan de Groot <groot@kde.org>
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

#include "MountPoints.h"

#include "core/PartUtils.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/Logger.h"

#include <QComboBox>

QStringList
standardMountPoints()
{
    QStringList mountPoints{ "/", "/boot", "/home", "/opt", "/usr", "/var" };
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
    combo.addItem( combo.tr( "(no mount point)" ) );
    combo.addItems( standardMountPoints() );
}

void
standardMountPoints(QComboBox& combo, const QString& selected)
{
    standardMountPoints( combo );
    if ( selected.isEmpty() )
        combo.setCurrentIndex( 0 );
    else
        combo.setCurrentText( selected );
}

QString
selectedMountPoint(QComboBox& combo)
{
    cDebug() << "Selected mount point" << combo.currentIndex() << combo.currentText();
    if ( combo.currentIndex() == 0 )
        return QString();
    return combo.currentText();
}

void
setSelectedMountPoint(QComboBox& combo, const QString& selected)
{
    cDebug() << "Setting mount point" << selected;
    if ( selected.isEmpty() )
        combo.setCurrentIndex( 0 );  // (no mount point)
    else
    {
        for ( int i = 0; i < combo.count(); ++i )
            if ( selected == combo.itemText( i ) )
            {
                cDebug() << " .. found at index" << i;
                combo.setCurrentIndex( i );
                return;
            }
        cDebug() << " .. new item";
        combo.addItem( selected );
        combo.setCurrentIndex( combo.count() - 1);
    }
}
