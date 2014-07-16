/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
 *
 *   Calamares is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Calamares is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Calamares. If not, see <http://www.gnu.org/licenses/>.
 */

#include "PythonJobHelper.h"

#include "utils/Logger.h"

#include <boost/python.hpp>

namespace bp = boost::python;

namespace Calamares {

PythonJobHelper* PythonJobHelper::s_instance = nullptr;

PythonJobHelper::PythonJobHelper( QObject* parent )
    : QObject( parent )
{
    // Let's make extra sure we only call Py_Initialize once
    if ( !s_instance )
    {
        Py_Initialize();

        m_mainModule = bp::import( "__main__" );
        m_mainNamespace = m_mainModule.attr( "__dict__" );
    }
    else
    {
        cDebug() << "WARNING: creating PythonJobHelper more than once. This is very bad.";
        return;
    }

    s_instance = this;
}

PythonJobHelper::~PythonJobHelper()
{}


boost::python::object
PythonJobHelper::createCleanNamespace()
{
    // To make sure we run each script with a clean namespace, we only fetch the
    // builtin namespace from the interpreter as it was when freshly initialized.
    bp::dict scriptNamespace;
    scriptNamespace[ "__builtins__" ] = m_mainNamespace[ "__builtins__" ];

    return scriptNamespace;
}


} // namespace Calamares
