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

#ifndef PARTITION_GUI_PARTITIONDIALOGHELPERS
#define PARTITION_GUI_PARTITIONDIALOGHELPERS

#include <kpmcore/core/partitiontable.h>

#include <QStringList>

class QComboBox;
class QListWidget;

/**
 * Returns a list of standard mount points (e.g. /, /usr, ...).
 * This also includes the EFI mount point if that is necessary
 * on the target system.
 */
QStringList standardMountPoints();

/**
 * Clears the combobox and fills it with "(no mount point)"
 * and the elements of standardMountPoints(), above.
 */
void standardMountPoints( QComboBox& );

/**
 * As above, but also sets the displayed mount point to @p selected,
 * unless it is empty, in which case "(no mount point)" is chosen.
 */
void standardMountPoints( QComboBox&, const QString& selected );

/**
 * Get the mount point selected in the combo box (which should
 * have been set up with standardMountPoints(), above); this
 * will map the topmost item (i.e. "(no mount point)") back
 * to blank, to allow easy detection of no-mount-selected.
 */
QString selectedMountPoint( QComboBox& combo );
static inline QString selectedMountPoint(QComboBox* combo) { return selectedMountPoint(*combo); }

void setSelectedMountPoint( QComboBox& combo, const QString& selected );
static inline void setSelectedMountPoint(QComboBox* combo, const QString& selected) { setSelectedMountPoint( *combo, selected); }

/**
 * Get the flags that have been checked in the list widget.
 */
PartitionTable::Flags flagsFromList( const QListWidget& list );
void setFlagList( QListWidget& list, PartitionTable::Flags available, PartitionTable::Flags checked );

#endif
