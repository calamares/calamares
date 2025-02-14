/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2023 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef CALAMARES_PYBIND11_PYBIND11HELPERS_H
#define CALAMARES_PYBIND11_PYBIND11HELPERS_H

#include "PythonTypes.h"

#include <QString>

namespace Calamares
{
namespace Python __attribute__( ( visibility( "hidden" ) ) )
{
    inline QString asQString( const pybind11::handle& o )
    {
        return QString::fromUtf8( pybind11::str( o ).cast< std::string >().c_str() );
    }

}  // namespace Python
}  // namespace Calamares


#endif
