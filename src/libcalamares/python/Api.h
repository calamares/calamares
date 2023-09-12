/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2023 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef CALAMARES_PYTHON_API_H
#define CALAMARES_PYTHON_API_H

/** @file
 *
 * Contains the API that Python modules use from the Python code
 * of that module. This is the C++ side that implements the functions
 * imported by the Python code as `import libcalamares`.
 */

#include <string>

/** @note There is no point in making this API "visible" in the C++
 *        code, so there are no declarations here. See Api.cpp for
 *        the Python declarations that do the work.
 */
#endif
