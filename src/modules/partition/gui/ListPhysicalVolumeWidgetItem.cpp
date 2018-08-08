/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2018, Caio Jordão Carvalho <caiojcarvalho@gmail.com>
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

#include "ListPhysicalVolumeWidgetItem.h"

#include <kpmcore/util/capacity.h>

ListPhysicalVolumeWidgetItem::ListPhysicalVolumeWidgetItem( const Partition* partition, bool checked )
    : QListWidgetItem(QString("%1 | %2").arg( partition->deviceNode(), Capacity::formatByteSize( partition->capacity() )))
    , m_partition(partition)
{
    setToolTip( partition->deviceNode() );
    setSizeHint( QSize(0, 32) );
    setCheckState( checked ? Qt::Checked : Qt::Unchecked );
}

const Partition*
ListPhysicalVolumeWidgetItem::partition() const
{
    return m_partition;
}
