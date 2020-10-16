/* === This file is part of Calamares - <https://github.com/calamares> ===
 * 
 *   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
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

#ifndef DLLMACRO_H
#define DLLMACRO_H

#include <qglobal.h>

/*
 * Mark symbols exported from Calamares non-GUI library with DLLEXPORT.
 * These are the public API of libcalamares.
 */
#ifndef DLLEXPORT
#if defined( DLLEXPORT_PRO )
#define DLLEXPORT Q_DECL_EXPORT
#else
#define DLLEXPORT Q_DECL_IMPORT
#endif
#endif

/*
 * Mark symbols exported from Calamares GUI library with DLLEXPORT.
 * These are the public API of libcalamaresui.
 */
#ifndef UIDLLEXPORT
#if defined( UIDLLEXPORT_PRO )
#define UIDLLEXPORT Q_DECL_EXPORT
#else
#define UIDLLEXPORT Q_DECL_IMPORT
#endif
#endif

/*
 * Mark symbols exported from Calamares C++ plugins with PLUGINDLLEXPORT.
 * These are the public API of the libraries (generally, the plugin
 * entry point)
 */
#ifndef PLUGINDLLEXPORT
#if defined( PLUGINDLLEXPORT_PRO )
#define PLUGINDLLEXPORT Q_DECL_EXPORT
#else
#define PLUGINDLLEXPORT Q_DECL_IMPORT
#endif
#endif

/*
 * For functions that should be static in production but also need to
 * be tested, use STATICTEST as linkage specifier. When built as part
 * of a test, the function will be given normal linkage.
 */
#ifndef STATICTEST
#if defined( BUILD_AS_TEST )
#define STATICTEST
#else
#define STATICTEST static
#endif
#endif

#endif
