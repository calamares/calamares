/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2023 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#ifndef CALAMARES_PYTHON_LOGGER_H
#define CALAMARES_PYTHON_LOGGER_H

/** @file
 *
 * Additional logging helpers for pybind11 types.
 */

#include "utils/Logger.h"

#include "python/Pybind11Helpers.h"

#include <string>

inline QDebug&
operator<<( QDebug& s, const pybind11::handle& h )
{
#if QT_VERSION < QT_VERSION_CHECK( 6, 0, 0 )
    return s << QString::fromUtf8( pybind11::str( h ).cast< std::string >().c_str() );
#else
    return s << pybind11::str( h ).cast< std::string >();
#endif
}

#endif
