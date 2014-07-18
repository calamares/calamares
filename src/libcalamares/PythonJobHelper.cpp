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

#include "utils/CalamaresUtils.h"
#include "utils/Logger.h"

#include <QDir>
#include <QFileInfo>

#undef slots
#include <boost/python.hpp>

namespace bp = boost::python;

namespace CalamaresPython {

Helper* Helper::s_instance = nullptr;

Helper::Helper( QObject* parent )
    : QObject( parent )
{
    // Let's make extra sure we only call Py_Initialize once
    if ( !s_instance )
    {
        Py_Initialize();

        m_mainModule = bp::import( "__main__" );
        m_mainNamespace = m_mainModule.attr( "__dict__" );

        // If we're running from the build dir
        QFileInfo fi( QDir::current().absoluteFilePath( "libcalamares.so" ) );
        if ( fi.exists() && fi.isReadable() )
        {
            m_pythonPaths.append( fi.dir().absolutePath() );
        }

        QDir calaPythonPath( CalamaresUtils::systemLibDir().absolutePath() +
                             QDir::separator() + "calamares" );
        if ( calaPythonPath.exists() &&
             calaPythonPath.isReadable() )
        {
            QFileInfo fi( calaPythonPath.absoluteFilePath( "libcalamares.so" ) );
            if ( fi.exists() && fi.isReadable() )
            {
                m_pythonPaths.append( fi.dir().absolutePath() );
            }
        }


        bp::object sys = bp::import( "sys" );

        foreach ( QString path, m_pythonPaths )
        {
            bp::str dir = path.toLocal8Bit().data();
            sys.attr( "path" ).attr( "append" )( dir );
        }
    }
    else
    {
        cDebug() << "WARNING: creating PythonJobHelper more than once. This is very bad.";
        return;
    }

    s_instance = this;
}

Helper::~Helper()
{}


boost::python::object
Helper::createCleanNamespace()
{
    // To make sure we run each script with a clean namespace, we only fetch the
    // builtin namespace from the interpreter as it was when freshly initialized.
    bp::dict scriptNamespace;
    scriptNamespace[ "__builtins__" ] = m_mainNamespace[ "__builtins__" ];

    return scriptNamespace;
}


QString
Helper::handleLastError()
{
    using namespace boost::python;
    using namespace boost;

    PyObject *exc,*val,*tb;
    object formatted_list, formatted;
    PyErr_Fetch(&exc,&val,&tb);
    handle<> hexc(exc),hval(allow_null(val)),htb(allow_null(tb));
    object traceback(import("traceback"));
    if (!tb) {
        object format_exception_only(traceback.attr("format_exception_only"));
        formatted_list = format_exception_only(hexc,hval);
    } else {
        object format_exception(traceback.attr("format_exception"));
        formatted_list = format_exception(hexc,hval,htb);
    }
    formatted = str("\n").join(formatted_list);
    return QString::fromStdString( extract<std::string>(formatted) );
}


} // namespace Calamares
