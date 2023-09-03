/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2023 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */
#ifndef CALAMARES_COMPAT_MUTEX_H
#define CALAMARES_COMPAT_MUTEX_H

#include <QMutexLocker>

namespace Calamares
{

/*
 * In Qt5, QMutexLocker is a class and operates implicitly on
 * QMutex but in Qt6 it is a template and needs a specialization.
 */
#if QT_VERSION < QT_VERSION_CHECK( 6, 0, 0 )
using MutexLocker = QMutexLocker;
#else
using MutexLocker = QMutexLocker< QMutex >;
#endif

}  // namespace Calamares

#endif
