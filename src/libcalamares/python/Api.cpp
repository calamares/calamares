/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2023 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */
#include "python/Api.h"

#include "utils/Logger.h"
#include "utils/String.h"

#undef slots
#include <pybind11/pybind11.h>

namespace
{
const char output_prefix[] = "[PYTHON JOB]:";
inline void
log_action( unsigned int level, const std::string& s )
{
    Logger::CDebug( level ) << output_prefix << QString::fromStdString( s );
}

}  // namespace

namespace Calamares
{
namespace Python
{
std::string
obscure( const std::string& string )
{
    return Calamares::String::obscure( QString::fromStdString( string ) ).toStdString();
}

void
debug( const std::string& s )
{
    log_action( Logger::LOGDEBUG, s );
}

void
warning( const std::string& s )
{
    log_action( Logger::LOGWARNING, s );
}

void
error( const std::string& s )
{
    log_action( Logger::LOGERROR, s );
}

}  // namespace Python
}  // namespace Calamares

PYBIND11_MODULE( libcalamares, m )
{
    m.doc() = "Calamares API from Python";  // optional module docstring

    m.def( "obscure", &Calamares::Python::obscure, "A function that obscures (encodes) a string" );

    m.def( "debug", &Calamares::Python::debug, "Log a debug-message" );
    m.def( "warning", &Calamares::Python::warning, "Log a warning-message" );
    m.def( "error", &Calamares::Python::error, "Log an error-message" );
}
