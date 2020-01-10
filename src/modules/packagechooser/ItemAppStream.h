/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019, Adriaan de Groot <groot@kde.org>
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
