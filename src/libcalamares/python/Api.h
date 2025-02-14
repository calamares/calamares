/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2023, 2024 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef CALAMARES_PYTHON_API_H
#define CALAMARES_PYTHON_API_H

/** @file
 *
 * Contains some of the API that Python modules use from the Python code
 * of that module. The functions declared here have no complications
 * regarding the (Python) types being used.
 */

#include "PythonTypes.h"

#include <string>

namespace Calamares
{
namespace Python __attribute__( ( visibility( "hidden" ) ) )
{
    std::string obscure( const std::string& string );

    void debug( const std::string& s );
    void warning( const std::string& s );
    // void warn( const std::string& s) is an alias of warning() defined at the Python level
    void error( const std::string& s );

    Dictionary load_yaml( const std::string& path );

    List gettext_languages();
    Object gettext_path();

    int mount( const std::string& device_path,
            const std::string& mount_point,
            const std::string& filesystem_name = std::string(),
            const std::string& options = std::string() );

}
}

#endif
