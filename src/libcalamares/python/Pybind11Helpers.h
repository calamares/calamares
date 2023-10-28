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

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcovered-switch-default"
#pragma clang diagnostic ignored "-Wfloat-equal"
#pragma clang diagnostic ignored "-Wweak-vtables"
#pragma clang diagnostic ignored "-Wmissing-variable-declarations"
#pragma clang diagnostic ignored "-Wold-style-cast"
#pragma clang diagnostic ignored "-Wshadow-uncaptured-local"
#pragma clang diagnostic ignored "-Wshadow-field-in-constructor"
#pragma clang diagnostic ignored "-Wshadow-field"
#pragma clang diagnostic ignored "-Wdocumentation"
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#pragma clang diagnostic ignored "-Wreserved-identifier"
#endif

#undef slots
#include <pybind11/pybind11.h>

#include <pybind11/embed.h>
#include <pybind11/eval.h>

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

}  // namespace Python
}  // namespace Calamares

#ifdef __clang__
#pragma clang diagnostic pop
#endif

#endif
