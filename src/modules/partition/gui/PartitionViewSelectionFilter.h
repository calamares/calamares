/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef PARTITIONVIEWSELECTIONFILTER_H
#define PARTITIONVIEWSELECTIONFILTER_H

#include <QModelIndex>

#include <functional>

typedef std::function< bool( const QModelIndex& ) > SelectionFilter;

#endif  // PARTITIONVIEWSELECTIONFILTER_H
