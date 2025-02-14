/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019-2020, 2024 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

/*
 * The Python and Boost::Python headers are not C++14 warning-proof, especially
 * with picky compilers like Clang 8 and 9. Since we use Clang for the
 * find-all-the-warnings case, switch those warnings off for
 * the we-can't-change-them system headers.
 *
 * This convenience header handles including all the bits we need for
 * Python support, while silencing warnings.
 */
#ifndef CALAMARES_PYBOOST_PYTHONTYPES_H
#define CALAMARES_PYBOOST_PYTHONTYPES_H

#include <qglobal.h>

QT_WARNING_PUSH
QT_WARNING_DISABLE_CLANG( "-Wreserved-id-macro" )
QT_WARNING_DISABLE_CLANG( "-Wold-style-cast" )
QT_WARNING_DISABLE_CLANG( "-Wzero-as-null-pointer-constant" )
QT_WARNING_DISABLE_CLANG( "-Wextra-semi-stmt" )
QT_WARNING_DISABLE_CLANG( "-Wall" )
QT_WARNING_DISABLE_CLANG( "-Wimplicit-float-conversion" )
QT_WARNING_DISABLE_CLANG( "-Wundef" )
QT_WARNING_DISABLE_CLANG( "-Wdeprecated-dynamic-exception-spec" )
QT_WARNING_DISABLE_CLANG( "-Wshadow-field-in-constructor" )
QT_WARNING_DISABLE_CLANG( "-Wshadow" )
QT_WARNING_DISABLE_CLANG( "-Wmissing-noreturn" )
QT_WARNING_DISABLE_CLANG( "-Wcast-qual" )
QT_WARNING_DISABLE_CLANG( "-Wcast-align" )
QT_WARNING_DISABLE_CLANG( "-Wsign-conversion" )
QT_WARNING_DISABLE_CLANG( "-Wdouble-promotion" )
QT_WARNING_DISABLE_CLANG( "-Wredundant-parens" )
QT_WARNING_DISABLE_CLANG( "-Wweak-vtables" )
QT_WARNING_DISABLE_CLANG( "-Wdeprecated" )
QT_WARNING_DISABLE_CLANG( "-Wmissing-field-initializers" )
QT_WARNING_DISABLE_CLANG( "-Wdisabled-macro-expansion" )
QT_WARNING_DISABLE_CLANG( "-Wdocumentation" )
QT_WARNING_DISABLE_CLANG( "-Wcomma" )
QT_WARNING_DISABLE_CLANG( "-Wunused-parameter" )
QT_WARNING_DISABLE_CLANG( "-Wunused-template" )

// Actually for Python headers
QT_WARNING_DISABLE_CLANG( "-Wreserved-id-macro" )

#undef slots
#include <boost/python.hpp>
#include <boost/python/args.hpp>
#include <boost/python/dict.hpp>
#include <boost/python/list.hpp>
#include <boost/python/object.hpp>

QT_WARNING_POP

namespace Calamares
{
namespace Python __attribute__( ( visibility( "hidden" ) ) )
{
    using Dictionary = boost::python::dict;
    using List = boost::python::list;
    using Object = boost::python::object;

    inline auto None()
    {
        return Object();
    }

    using Integer = Object;
    using Float = Object;
    using Boolean = Object;
    using String = Object;
}  // namespace Python
}  // namespace Calamares

#endif
