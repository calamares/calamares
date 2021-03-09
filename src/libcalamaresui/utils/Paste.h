/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Bill Auger
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef UTILS_PASTE_H
#define UTILS_PASTE_H

#include <QString>

class QObject;

namespace CalamaresUtils
{
namespace Paste
{

/** @brief Send the current log file to a pastebin
 *
 * Returns the (string) URL that the pastebin gives us.
 */
QString doLogUpload( QObject* parent );
}  // namespace Paste

}  // namespace CalamaresUtils

#endif
