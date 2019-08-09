/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019, Bill Auger
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

#ifndef UTILS_PASTE_H
#define UTILS_PASTE_H

#include <qglobal.h>  // for quint16

class QObject;
class QString;

namespace CalamaresUtils
{

/** @brief Send the current log file to a pastebin
 *
 * Returns the (string) URL that the pastebin gives us.
 */
QString sendLogToPastebin( QObject* parent, const QString& ficheHost, quint16 fichePort );

}  // namespace CalamaresUtils

#endif
