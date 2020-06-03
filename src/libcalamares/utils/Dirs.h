/* === This file is part of Calamares - <https://github.com/calamares> ===
 * 
 *   SPDX-FileCopyrightText: 2013-2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *
 *   Originally from Tomahawk, portions:
 *   SPDX-FileCopyrightText: 2010-2011 Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   SPDX-FileCopyrightText: 2010-2011 Leo Franchi <lfranchi@kde.org>
 *   SPDX-FileCopyrightText: 2010-2012 Jeff Mitchell <jeff@tomahawk-player.org>
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
 *
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *   License-Filename: LICENSE
 *
 */

#ifndef UTILS_DIRS_H
#define UTILS_DIRS_H

#include "DllMacro.h"

#include <QDir>

namespace CalamaresUtils
{
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
