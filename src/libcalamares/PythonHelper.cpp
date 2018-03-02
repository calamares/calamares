/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
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

namespace CalamaresPython
{


boost::python::object
variantToPyObject( const QVariant& variant )
{
    switch ( variant.type() )
    {
    case QVariant::Map:
        return variantMapToPyDict( variant.toMap() );

    case QVariant::Hash:
        return variantHashToPyDict( variant.toHash() );

    case QVariant::List:
    case QVariant::StringList:
        return variantListToPyList( variant.toList() );

    case QVariant::Int:
        return bp::object( variant.toInt() );

    case QVariant::Double:
        return bp::object( variant.toDouble() );

    case QVariant::String:
        return bp::object( variant.toString().toStdString() );

    case QVariant::Bool:
        return bp::object( variant.toBool() );

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

    else if ( pyType == "bool" )
        return QVariant( bp::extract< bool >( pyObject ) );

    else
        return QVariant();
}


boost::python::list
variantListToPyList( const QVariantList& variantList )
{
    bp::list pyList;
    for ( const QVariant& variant : variantList )
        pyList.append( variantToPyObject( variant ) );
    return pyList;
}


QVariantList
variantListFromPyList( const boost::python::list& pyList )
{
    QVariantList list;
    for ( int i = 0; i < bp::len( pyList ); ++i )
        list.append( variantFromPyObject( pyList[ i ] ) );
    return list;
}


boost::python::dict
variantMapToPyDict( const QVariantMap& variantMap )
{
    bp::dict pyDict;
    for ( auto it = variantMap.constBegin(); it != variantMap.constEnd(); ++it )
        pyDict[ it.key().toStdString() ] = variantToPyObject( it.value() );
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

boost::python::dict
variantHashToPyDict( const QVariantHash& variantHash )
{
    bp::dict pyDict;
    for ( auto it = variantHash.constBegin(); it != variantHash.constEnd(); ++it )
        pyDict[ it.key().toStdString() ] = variantToPyObject( it.value() );
    return pyDict;
}


QVariantHash
variantHashFromPyDict( const boost::python::dict& pyDict )
{
    QVariantHash hash;
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

        hash.insert( QString::fromStdString( key ), variantFromPyObject( obj ) );
    }
    return hash;
}



Helper* Helper::s_instance = nullptr;

static inline void add_if_lib_exists( const QDir& dir, const char* name, QStringList& list )
{
    if ( ! ( dir.exists() && dir.isReadable() ) )
        return;

    QFileInfo fi( dir.absoluteFilePath( name ) );
    if ( fi.exists() && fi.isReadable() )
        list.append( fi.dir().absolutePath() );
}

Helper::Helper( QObject* parent )
    : QObject( parent )
{
    // Let's make extra sure we only call Py_Initialize once
    if ( !s_instance )
    {
        if ( !Py_IsInitialized() )
            Py_Initialize();

        m_mainModule = bp::import( "__main__" );
        m_mainNamespace = m_mainModule.attr( "__dict__" );

        // If we're running from the build dir
        add_if_lib_exists( QDir::current(), "libcalamares.so", m_pythonPaths );

        QDir calaPythonPath( CalamaresUtils::systemLibDir().absolutePath() +
                             QDir::separator() + "calamares" );
        add_if_lib_exists( calaPythonPath, "libcalamares.so", m_pythonPaths );

        bp::object sys = bp::import( "sys" );

        foreach ( QString path, m_pythonPaths )
        {
            bp::str dir = path.toLocal8Bit().data();
            sys.attr( "path" ).attr( "append" )( dir );
        }
    }
    else
    {
        cWarning() << "creating PythonHelper more than once. This is very bad.";
        return;
    }

    s_instance = this;
}

Helper::~Helper()
{
    s_instance = nullptr;
}


boost::python::dict
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
    PyObject* type = nullptr, *val = nullptr, *traceback_p = nullptr;
    PyErr_Fetch( &type, &val, &traceback_p );

    Logger::CDebug debug;
    debug.noquote() << "Python Error:\n";

    QString typeMsg;
    if ( type != nullptr )
    {
        bp::handle<> h_type( type );
        bp::str pystr( h_type );
        bp::extract< std::string > extracted( pystr );
        if ( extracted.check() )
            typeMsg = QString::fromStdString( extracted() ).trimmed();

        if ( typeMsg.isEmpty() )
            typeMsg = tr( "Unknown exception type" );
        debug << typeMsg << '\n';
    }

    QString valMsg;
    if ( val != nullptr )
    {
        bp::handle<> h_val( val );
        bp::str pystr( h_val );
        bp::extract< std::string > extracted( pystr );
        if ( extracted.check() )
            valMsg = QString::fromStdString( extracted() ).trimmed();

        if ( valMsg.isEmpty() )
            valMsg = tr( "unparseable Python error" );

        // Special-case: CalledProcessError has an attribute "output" with the command output,
        // add that to the printed message.
        if ( typeMsg.contains( "CalledProcessError" ) )
        {
            bp::object exceptionObject( h_val );
            auto a = exceptionObject.attr( "output" );
            bp::str outputString( a );
            bp::extract< std::string > extractedOutput( outputString );

            QString output;
            if ( extractedOutput.check() )
            {
                output = QString::fromStdString( extractedOutput() ).trimmed();
            }
            if ( !output.isEmpty() )
            {
                // Replace the Type of the error by the warning string,
                // and use the output of the command (e.g. its stderr) as value.
                typeMsg = valMsg;
                valMsg = output;
            }
        }
        debug << valMsg << '\n';
    }

    QString tbMsg;
    if ( traceback_p != nullptr )
    {
        bp::handle<> h_tb( traceback_p );
        bp::object traceback_module( bp::import( "traceback" ) );
        bp::object format_tb( traceback_module.attr( "format_tb" ) );
        bp::object tb_list( format_tb( h_tb ) );
        bp::object pystr( bp::str( "\n" ).join( tb_list ) );
        bp::extract< std::string > extracted( pystr );
        if ( extracted.check() )
            tbMsg = QString::fromStdString( extracted() ).trimmed();

        if ( tbMsg.isEmpty() )
            tbMsg = tr( "unparseable Python traceback" );
        debug << tbMsg << '\n';
    }

    if ( typeMsg.isEmpty() && valMsg.isEmpty() && tbMsg.isEmpty() )
        return tr( "Unfetchable Python error." );


    QStringList msgList;
    if ( !typeMsg.isEmpty() )
        msgList.append( QString( "<strong>%1</strong>" ).arg( typeMsg.toHtmlEscaped() ) );
    if ( !valMsg.isEmpty() )
        msgList.append( valMsg.toHtmlEscaped() );

    if ( !tbMsg.isEmpty() )
    {
        msgList.append( QStringLiteral( "<br/>Traceback:" ) );
        msgList.append( QString( "<pre>%1</pre>" ).arg( tbMsg.toHtmlEscaped() ) );
    }

    // Return a string made of the msgList items, wrapped in <div> tags
    return QString( "<div>%1</div>" ).arg( msgList.join( "</div><div>" ) );
}


} // namespace CalamaresPython
