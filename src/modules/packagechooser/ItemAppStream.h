/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef ITEMAPPSTREAM_H
#define ITEMAPPSTREAM_H

#include "PackageModel.h"

namespace AppStream
{
class Pool;
}

/** @brief Loads an item from AppStream data.
 *
 * The @p map must have a key *appstream*. That is used as the
 * primary source of information from the AppStream cache, but
 * keys *id* and *screenshotPath* may be used to override parts
 * of the AppStream data -- so that the ID is under the control
 * of Calamares, and the screenshot can be forced to a local path
 * available on the installation medium.
 *
 * Requires AppStreamQt, if not present will return invalid
 * PackageItems.
 */
PackageItem fromAppStream( AppStream::Pool& pool, const QVariantMap& map );

#endif
