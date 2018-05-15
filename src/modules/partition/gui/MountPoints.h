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

#ifndef PARTITION_GUI_MOUNTPOINTS
#define PARTITION_GUI_MOUNTPOINTS

#include <QStringList>

class QComboBox;

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

#endif
