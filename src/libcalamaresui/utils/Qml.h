/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2020, Adriaan de Groot <groot@kde.org>
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

#ifndef UTILS_QML_H
#define UTILS_QML_H

#include "DllMacro.h"

class QQuickItem;

namespace CalamaresUtils
{

/** @brief Calls the QML method @p method on @p qmlObject
 *
 * Pass in only the name of the method (e.g. onActivate). This function
 * checks if the method exists (with no arguments) before trying to
 * call it, so that no warnings are printed due to missing methods.
 *
 * If there is a return value from the QML method, it is logged (but not otherwise used).
 */
UIDLLEXPORT void
callQMLFunction( QQuickItem* qmlObject, const char* method );

}  // namespace CalamaresUtils

#endif
