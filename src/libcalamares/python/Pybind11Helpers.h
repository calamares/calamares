/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2023 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef CALAMARES_PYTHON_PYBIND11_HELPERS_H
#define CALAMARES_PYTHON_PYBIND11_HELPERS_H

#include <QString>

#include <string>

#undef slots
#include <pybind11/pybind11.h>

namespace Calamares
{
namespace Python __attribute__( ( visibility( "hidden" ) ) )
{
    using Dictionary = pybind11::dict;
    using String = pybind11::str;
    using List = pybind11::list;
    using Object = pybind11::object;

    using Float = double;

    inline QString asQString( const pybind11::handle& o )
    {
        return QString::fromUtf8( pybind11::str( o ).cast< std::string >().c_str() );
    }

}  // namespace )
}  // namespace Calamares
#endif
