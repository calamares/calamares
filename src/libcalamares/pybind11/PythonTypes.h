/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2023, 2024 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef CALAMARES_PYBIND11_PYTHONTYPES_H
#define CALAMARES_PYBIND11_PYTHONTYPES_H

#include <QString>

QT_WARNING_PUSH
QT_WARNING_DISABLE_CLANG( "-Wcovered-switch-default" )
QT_WARNING_DISABLE_CLANG( "-Wfloat-equal" )
QT_WARNING_DISABLE_CLANG( "-Wweak-vtables" )
QT_WARNING_DISABLE_CLANG( "-Wmissing-variable-declarations" )
QT_WARNING_DISABLE_CLANG( "-Wold-style-cast" )
QT_WARNING_DISABLE_CLANG( "-Wshadow-uncaptured-local" )
QT_WARNING_DISABLE_CLANG( "-Wshadow-field-in-constructor" )
QT_WARNING_DISABLE_CLANG( "-Wshadow-field" )
QT_WARNING_DISABLE_CLANG( "-Wdocumentation" )
QT_WARNING_DISABLE_CLANG( "-Wmissing-noreturn" )
QT_WARNING_DISABLE_CLANG( "-Wreserved-identifier" )

#undef slots
#include <pybind11/pybind11.h>

#include <pybind11/embed.h>
#include <pybind11/eval.h>

QT_WARNING_POP

namespace Calamares
{
namespace Python __attribute__( ( visibility( "hidden" ) ) )
{
    using Dictionary = pybind11::dict;
    using List = pybind11::list;
    using Object = pybind11::object;

    inline auto None()
    {
        return pybind11::none();
    }

    using Integer = pybind11::int_;
    using Float = pybind11::float_;
    using Boolean = pybind11::bool_;
    using String = pybind11::str;
}  // namespace Python
}  // namespace Calamares

#endif
