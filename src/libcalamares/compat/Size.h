/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2024 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */
#ifndef CALAMARES_COMPAT_SIZE_H
#define CALAMARES_COMPAT_SIZE_H

#include <QVariant>

namespace Calamares
{
/* Compatibility of size types (e.g. qsizetype, STL sizes, int) between Qt5 and Qt6 */

using NumberForTr = int;

}

#endif
