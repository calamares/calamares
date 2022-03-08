/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef PARTITION_GUI_PARTITIONDIALOGHELPERS
#define PARTITION_GUI_PARTITIONDIALOGHELPERS

#include <kpmcore/core/partitiontable.h>

#include <QStringList>

class QPushButton;
class QComboBox;
class QLabel;
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
static inline QString
selectedMountPoint( QComboBox* combo )
{
    return selectedMountPoint( *combo );
}

void setSelectedMountPoint( QComboBox& combo, const QString& selected );
static inline void
setSelectedMountPoint( QComboBox* combo, const QString& selected )
{
    setSelectedMountPoint( *combo, selected );
}

/** @brief Validate a @p mountPoint and adjust the UI
 *
 * If @p mountPoint is valid -- unused and starts with a /, for instance --
 * then the button is enabled, label is cleared, and returns @c true.
 *
 * If it is not valid, returns @c false and sets the UI
 * to explain why.
 */
bool validateMountPoint( const QString& mountPoint, const QStringList& inUse, QLabel* label, QPushButton* button );

/**
 * Get the flags that have been checked in the list widget.
 */
PartitionTable::Flags flagsFromList( const QListWidget& list );
void setFlagList( QListWidget& list, PartitionTable::Flags available, PartitionTable::Flags checked );

#endif
