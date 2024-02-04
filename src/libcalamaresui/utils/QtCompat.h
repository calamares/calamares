/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

/**@file Handle compatibility and deprecations across Qt versions
 *
 * Since Calamares is supposed to work with Qt 5.15 or Qt 6 or later, it
 * covers a lot of changes in the Qt API.
 *
 * This file adjusts for that by introducing suitable aliases
 * and workaround-functions.
 *
 * For a similar approach for QtCore, see libcalamares/utils/String.h
 */

#ifndef UTILS_QTCOMPAT_H
#define UTILS_QTCOMPAT_H

#include <QPalette>

/* Avoid warnings about QPalette changes */
constexpr static const auto WindowBackground = QPalette::Window;

constexpr static const auto WindowText = QPalette::WindowText;

#endif
