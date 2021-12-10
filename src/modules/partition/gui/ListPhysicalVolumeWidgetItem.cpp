/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2018 Caio Jordão Carvalho <caiojcarvalho@gmail.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "ListPhysicalVolumeWidgetItem.h"

#include "core/SizeUtils.h"

ListPhysicalVolumeWidgetItem::ListPhysicalVolumeWidgetItem( const Partition* partition, bool checked )
    : QListWidgetItem( QString( "%1 | %2" ).arg( partition->deviceNode(), formatByteSize( partition->capacity() ) ) )
    , m_partition( partition )
{
    setToolTip( partition->deviceNode() );
    setSizeHint( QSize( 0, 32 ) );
    setCheckState( checked ? Qt::Checked : Qt::Unchecked );
}

const Partition*
ListPhysicalVolumeWidgetItem::partition() const
{
    return m_partition;
}

ListPhysicalVolumeWidgetItem::~ListPhysicalVolumeWidgetItem() {}
