/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2022 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef CALAMARES_CALAMARESABOUT_H
#define CALAMARES_CALAMARESABOUT_H

#include "DllMacro.h"

#include <QString>

namespace Calamares
{
/** @brief Returns an about string for the application
 *
 * The about string includes a header-statement, a list of maintainer
 * addresses, and a thank-you to Blue Systems. There is on %-substitution
 * left, where you can fill in the name of the product (e.g. to say
 * "Calamares for Netrunner" or ".. for Manjaro").
 */
DLLEXPORT const QString aboutStringUntranslated();
/// @brief As above, but translated in the current Calamares language
DLLEXPORT const QString aboutString();
}  // namespace Calamares

#endif
