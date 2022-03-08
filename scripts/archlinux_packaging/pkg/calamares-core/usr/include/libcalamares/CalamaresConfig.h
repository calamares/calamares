/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */
#ifndef CALAMARESCONFIG_H
#define CALAMARESCONFIG_H

#define CMAKE_INSTALL_PREFIX "/usr"
#define CMAKE_INSTALL_FULL_LIBEXECDIR "/usr/lib/libexec"
#define CMAKE_INSTALL_LIBDIR "lib"
#define CMAKE_INSTALL_FULL_LIBDIR "/usr/lib"
#define CMAKE_INSTALL_FULL_DATADIR "/usr/share/calamares"
#define CMAKE_INSTALL_FULL_SYSCONFDIR "/etc"

/*
 * These are feature-settings that affect consumers of Calamares
 * libraries as well; without Python-support in the libs, for instance,
 * there's no point in having a Python plugin.
 *
 * This list should match the one in CalamaresConfig.cmake
 * which is the CMake-time side of the same configuration.
 */
#define WITH_PYTHON
/* #undef WITH_PYTHONQT */
#define WITH_QML

#endif  // CALAMARESCONFIG_H
