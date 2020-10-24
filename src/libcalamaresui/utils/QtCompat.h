/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

/**@file Handle compatibility and deprecations across Qt versions
 *
 * Since Calamares is supposed to work with Qt 5.9 or later, it covers a
 * lot of changes in the Qt API. Especially the later Qt 5.15 (last LTS)
 * versions deprecate a number of enum values and parts of the QWidgets
 * API. This file adjusts for that by introducing suitable aliases
 * and workaround-functions.
 *
 * For a similar approach for QtCore, see libcalamares/utils/String.h
 */

#ifndef UTILS_QTCOMPAT_H
#define UTILS_QTCOMPAT_H

#include <QPalette>

/* Avoid warnings about QPalette changes */
constexpr static const auto WindowBackground =
#if QT_VERSION < QT_VERSION_CHECK( 5, 15, 0 )
    QPalette::Background
#else
    QPalette::Window
#endif
    ;

constexpr static const auto WindowText =
#if QT_VERSION < QT_VERSION_CHECK( 5, 15, 0 )
    QPalette::Foreground
#else
    QPalette::WindowText
#endif
    ;

#endif
