/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef ITEMFLATPAK_H
#define ITEMFLATPAK_H

/* Bellow include may be needed in future */
#include "PackageModel.h"

#include "ItemAppStream.h"

/** @brief Loads an AppData XML file and returns a PackageItem
 *
 * The @p map must have a key *appdata*. That is used as the
 * primary source of information, but keys *id* and *screenshotPath*
 * may be used to override parts of the AppData -- so that the
 * ID is under the control of Calamares, and the screenshot can be
 * forced to a local path available on the installation medium.
 *
 * Requires XML support in libcalamares, if not present will
 * return invalid PackageItems.
 */
class PackageItemFlatpak: public PackageItem
{
public:
    PackageItemFlatpak(PackageItem item): PackageItem(item)
    {

    }
    bool installed;
};

PackageItem fromFlatpak(  AppStream::Pool& pool, const QVariantMap& map );

#endif
