/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2013-2016, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2018, Adriaan de Groot <groot@kde.org>
 *
 *   Originally from Tomahawk, portions:
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2010-2011, Leo Franchi <lfranchi@kde.org>
 *   Copyright 2010-2012, Jeff Mitchell <jeff@tomahawk-player.org>
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

#ifndef UTILS_DIRS_H
#define UTILS_DIRS_H

#include "DllMacro.h"

#include <QDir>

namespace CalamaresUtils
{
DLLEXPORT QDir qmlModulesDir();

/**
 * @brief appDataDir returns the directory with common application data.
 * Defaults to CMAKE_INSTALL_FULL_DATADIR (usually /usr/share/calamares).
 */
DLLEXPORT QDir appDataDir();

/**
 * @brief appLogDir returns the directory for Calamares logs.
 * Defaults to QStandardPaths::CacheLocation (usually ~/.cache/Calamares).
 */
DLLEXPORT QDir appLogDir();

/**
 * @brief systemLibDir returns the system's lib directory.
 * Defaults to CMAKE_INSTALL_FULL_LIBDIR (usually /usr/lib64 or /usr/lib).
 */
DLLEXPORT QDir systemLibDir();

/**
 * Override app data dir. Only for testing purposes.
 */
DLLEXPORT void setAppDataDir( const QDir& dir );
DLLEXPORT bool isAppDataDirOverridden();

DLLEXPORT void setQmlModulesDir( const QDir& dir );

/** @brief Setup extra config and data dirs from the XDG variables.
 */
DLLEXPORT void setXdgDirs();
/** @brief Are any extra directories configured? */
DLLEXPORT bool haveExtraDirs();
/** @brief XDG_CONFIG_DIRS, each guaranteed to end with / */
DLLEXPORT QStringList extraConfigDirs();
/** @brief XDG_DATA_DIRS, each guaranteed to end with / */
DLLEXPORT QStringList extraDataDirs();
}  // namespace CalamaresUtils

#endif
