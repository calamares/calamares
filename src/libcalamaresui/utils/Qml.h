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

#include "modulesystem/InstanceKey.h"
#include "utils/NamedEnum.h"

#include <QDir>

class QQuickItem;

namespace CalamaresUtils
{
/// @brief the extra directory where Calamares searches for QML files
UIDLLEXPORT QDir qmlModulesDir();
/// @brief sets specific directory for searching for QML files
UIDLLEXPORT void setQmlModulesDir( const QDir& dir );

/** @brief initialize QML search path with branding directories
 *
 * Picks a suitable branding directory (from the build-dir in debug mode,
 * otherwise based on the branding directory) and adds it to the
 * QML modules directory; returns @c false if none is found.
 */
UIDLLEXPORT bool initQmlModulesDir();

/** @brief Sets up global Calamares models for QML
 *
 * This needs to be called at least once to make the global Calamares
 * models (Branding, ViewManager, ...) available to QML.
 *
 * The following objects are made available globally:
 *  - `io.calamares.ui.Branding` (an object, see Branding.h)
 *  - `io.calamares.core.ViewManager` (a model, see ViewManager.h)
 *  - `io.calamares.core.Global` (an object, see GlobalStorage.h)
 * Additionally, modules based on QmlViewStep have a context
 * property `config` referring to that module's configuration (if any).
 */
UIDLLEXPORT void registerQmlModels();

/** @brief Calls the QML method @p method on @p qmlObject
 *
 * Pass in only the name of the method (e.g. onActivate). This function
 * checks if the method exists (with no arguments) before trying to
 * call it, so that no warnings are printed due to missing methods.
 *
 * If there is a return value from the QML method, it is logged (but not otherwise used).
 */
UIDLLEXPORT void callQmlFunction( QQuickItem* qmlObject, const char* method );

/** @brief Search modes for loading Qml files.
 *
 * A QML file could be compiled into QRC, or it could live
 * in the branding directory (and, in debug-runs, in
 * the current-directory). Modules have some control
 * over where the search is done.
 */
enum class QmlSearch
{
    QrcOnly,
    BrandingOnly,
    Both
};

/// @brief Names for the search terms (in config files)
UIDLLEXPORT const NamedEnumTable< QmlSearch >& qmlSearchNames();

/** @brief Find a suitable QML file, given the search method and name hints
 *
 * Returns QString() if nothing is found (which would mean the module
 * is badly configured).
 */
UIDLLEXPORT QString searchQmlFile( QmlSearch method,
                                   const QString& configuredName,
                                   const Calamares::ModuleSystem::InstanceKey& i );
UIDLLEXPORT QString searchQmlFile( QmlSearch method, const QString& fileNameNoSuffix );

}  // namespace CalamaresUtils

#endif
