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

#include "PythonHelper.h"

#include "utils/CalamaresUtils.h"
#include "utils/Logger.h"

#include <QDir>
#include <QFileInfo>

#undef slots
#include <boost/python.hpp>

namespace bp = boost::python;

namespace CalamaresPython {


boost::python::object
variantToPyObject( const QVariant& variant )
{
    switch ( variant.type() )
    {
    case QVariant::Map:
        return variantMapToPyDict( variant.toMap() );

    case QVariant::List:
    case QVariant::StringList:
        return variantListToPyList( variant.toList() );

    case QVariant::Int:
        return bp::object( variant.toInt() );

    case QVariant::Double:
        return bp::object( variant.toDouble() );

    case QVariant::String:
        return bp::object( variant.toString().toStdString() );

    default:
        return bp::object();
    }
}


QVariant
variantFromPyObject( const boost::python::object& pyObject )
{
    std::string pyType = bp::extract< std::string >( pyObject.attr( "__class__" ).attr( "__name__" ) );
    if ( pyType == "dict" )
        return variantMapFromPyDict( bp::extract< bp::dict >( pyObject ) );

    else if ( pyType == "list" )
        return variantListFromPyList( bp::extract< bp::list >( pyObject ) );

    else if ( pyType == "int" )
        return QVariant( bp::extract< int >( pyObject ) );

    else if ( pyType == "float" )
        return QVariant( bp::extract< double >( pyObject ) );

    else if ( pyType == "str" )
        return QVariant( QString::fromStdString( bp::extract< std::string >( pyObject ) ) );

    else
        return QVariant();
}


boost::python::list
variantListToPyList( const QVariantList& variantList )
{
    bp::list pyList;
    foreach ( const QVariant& variant, variantList )
    {
        pyList.append( variantToPyObject( variant ) );
    }
    return pyList;
}


QVariantList
variantListFromPyList( const boost::python::list& pyList )
{
    QVariantList list;
    for ( int i = 0; i < bp::len( pyList ); ++i )
    {
        list.append( variantFromPyObject( pyList[ i ] ) );
    }
    return list;
}


boost::python::dict
variantMapToPyDict( const QVariantMap& variantMap )
{
    bp::dict pyDict;
    for ( auto it = variantMap.constBegin(); it != variantMap.constEnd(); ++it )
    {
        pyDict[ it.key().toStdString() ] = variantToPyObject( it.value() );
    }
    return pyDict;
}


QVariantMap
variantMapFromPyDict( const boost::python::dict& pyDict )
{
    QVariantMap map;
    bp::list keys = pyDict.keys();
    for ( int i = 0; i < bp::len( keys ); ++i )
    {
        bp::extract< std::string > extracted_key( keys[ i ] );
        if ( !extracted_key.check() )
        {
            cDebug() << "Key invalid, map might be incomplete.";
            continue;
        }

        std::string key = extracted_key;

        bp::object obj = pyDict[ key ];

        map.insert( QString::fromStdString( key ), variantFromPyObject( obj ) );
    }
    return map;
}


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
        cDebug() << "WARNING: creating PythonHelper more than once. This is very bad.";
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
