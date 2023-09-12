/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017-2020, 2023 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */
#include "python/Api.h"

#include "CalamaresVersion.h"
#include "GlobalStorage.h"
#include "JobQueue.h"
#include "compat/Variant.h"
#include "locale/Global.h"
#include "utils/Logger.h"
#include "utils/RAII.h"
#include "utils/String.h"
#include "utils/Yaml.h"

#include <QCoreApplication>
#include <QDir>
#include <QStandardPaths>

#undef slots
#include <pybind11/embed.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

/** @namespace
 *
 * Helper functions for converting Python (pybind11) types to Qt types.
 */
namespace
{
// Forward declarations, since most of these are mutually recursive
py::list variantListToPyList( const QVariantList& variantList );
py::dict variantMapToPyDict( const QVariantMap& variantMap );
py::dict variantHashToPyDict( const QVariantHash& variantHash );

py::object
variantToPyObject( const QVariant& variant )
{
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wswitch-enum"
#endif

#if QT_VERSION < QT_VERSION_CHECK( 6, 0, 0 )
    const auto IntVariantType = QVariant::Int;
    const auto UIntVariantType = QVariant::UInt;
#else
    const auto IntVariantType = QMetaType::Type::Int;
    const auto UIntVariantType = QMetaType::Type::UInt;
#endif
    // 49 enumeration values not handled
    switch ( Calamares::typeOf( variant ) )
    {
    case Calamares::MapVariantType:
        return variantMapToPyDict( variant.toMap() );

    case Calamares::HashVariantType:
        return variantHashToPyDict( variant.toHash() );

    case Calamares::ListVariantType:
    case Calamares::StringListVariantType:
        return variantListToPyList( variant.toList() );

    case IntVariantType:
        return py::int_( variant.toInt() );
    case UIntVariantType:
        return py::int_( variant.toUInt() );

    case Calamares::LongLongVariantType:
        return py::int_( variant.toLongLong() );
    case Calamares::ULongLongVariantType:
        return py::int_( variant.toULongLong() );

    case Calamares::DoubleVariantType:
        return py::float_( variant.toDouble() );

    case Calamares::CharVariantType:
#if QT_VERSION > QT_VERSION_CHECK( 6, 0, 0 )
    case QMetaType::Type::QChar:
#endif
    case Calamares::StringVariantType:
        return py::str( variant.toString().toStdString() );

    case Calamares::BoolVariantType:
        return py::bool_( variant.toBool() );

#if QT_VERSION < QT_VERSION_CHECK( 6, 0, 0 )
    case QVariant::Invalid:
#endif
    default:
        return py::object();
    }
#ifdef __clang__
#pragma clang diagnostic pop
#endif
}

py::list
variantListToPyList( const QVariantList& variantList )
{
    py::list pyList;
    for ( const QVariant& variant : variantList )
    {
        pyList.append( variantToPyObject( variant ) );
    }
    return pyList;
}

py::dict
variantMapToPyDict( const QVariantMap& variantMap )
{
    py::dict pyDict;
    for ( auto it = variantMap.constBegin(); it != variantMap.constEnd(); ++it )
    {
        pyDict[ py::str( it.key().toStdString() ) ] = variantToPyObject( it.value() );
    }
    return pyDict;
}

py::dict
variantHashToPyDict( const QVariantHash& variantHash )
{
    py::dict pyDict;
    for ( auto it = variantHash.constBegin(); it != variantHash.constEnd(); ++it )
    {
        pyDict[ py::str( it.key().toStdString() ) ] = variantToPyObject( it.value() );
    }
    return pyDict;
}

}  // namespace

/** @namespace
 *
 * This is where the "public Python API" lives. It does not need to
 * be a namespace, and it does not need to be public, but it's
 * convenient to group things together.
 */
namespace Calamares
{
namespace Python
{
const char output_prefix[] = "[PYTHON JOB]:";
inline void
log_action( unsigned int level, const std::string& s )
{
    Logger::CDebug( level ) << output_prefix << QString::fromStdString( s );
}

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

py::dict
load_yaml( const std::string& path )
{
    const QString filePath = QString::fromUtf8( path.c_str() );
    bool ok = false;
    auto map = Calamares::YAML::load( filePath, &ok );
    if ( !ok )
    {
        cWarning() << "Loading YAML from" << filePath << "failed.";
    }

    return variantMapToPyDict( map );
}

static Calamares::GlobalStorage*
_global_storage()
{
    static Calamares::GlobalStorage* p = new Calamares::GlobalStorage;
    return p;
}

static QStringList
_gettext_languages()
{
    QStringList languages;

    // There are two ways that Python jobs can be initialised:
    //  - through JobQueue, in which case that has an instance which holds
    //    a GlobalStorage object, or
    //  - through the Python test-script, which initialises its
    //    own GlobalStoragePythonWrapper, which then holds a
    //    GlobalStorage object for all of Python.
    Calamares::JobQueue* jq = Calamares::JobQueue::instance();
    Calamares::GlobalStorage* gs = jq ? jq->globalStorage() : _global_storage();

    QString lang = Calamares::Locale::readGS( *gs, QStringLiteral( "LANG" ) );
    if ( !lang.isEmpty() )
    {
        languages.append( lang );
        if ( lang.indexOf( '.' ) > 0 )
        {
            lang.truncate( lang.indexOf( '.' ) );
            languages.append( lang );
        }
        if ( lang.indexOf( '_' ) > 0 )
        {
            lang.truncate( lang.indexOf( '_' ) );
            languages.append( lang );
        }
    }
    return languages;
}

py::list
gettext_languages()
{
    py::list pyList;
    for ( auto lang : _gettext_languages() )
    {
        pyList.append( lang.toStdString() );
    }
    return pyList;
}

static void
_add_localedirs( QStringList& pathList, const QString& candidate )
{
    if ( !candidate.isEmpty() && !pathList.contains( candidate ) )
    {
        pathList.prepend( candidate );
        if ( QDir( candidate ).cd( "lang" ) )
        {
            pathList.prepend( candidate + "/lang" );
        }
    }
}

py::object
gettext_path()
{
    // Going to log informatively just once
    static bool first_time = true;
    cScopedAssignment( &first_time, false );

    // TODO: distinguish between -d runs and normal runs
    // TODO: can we detect DESTDIR-installs?
    QStringList candidatePaths
        = QStandardPaths::locateAll( QStandardPaths::GenericDataLocation, "locale", QStandardPaths::LocateDirectory );
    QString extra = QCoreApplication::applicationDirPath();
    _add_localedirs( candidatePaths, extra );  // Often /usr/local/bin
    if ( !extra.isEmpty() )
    {
        QDir d( extra );
        if ( d.cd( "../share/locale" ) )  // Often /usr/local/bin/../share/locale -> /usr/local/share/locale
        {
            _add_localedirs( candidatePaths, d.canonicalPath() );
        }
    }
    _add_localedirs( candidatePaths, QDir().canonicalPath() );  // .

    if ( first_time )
    {
        cDebug() << "Determining gettext path from" << candidatePaths;
    }

    QStringList candidateLanguages = _gettext_languages();
    for ( const auto& lang : candidateLanguages )
    {
        for ( auto localedir : candidatePaths )
        {
            QDir ldir( localedir );
            if ( ldir.cd( lang ) )
            {
                Logger::CDebug( Logger::LOGDEBUG )
                    << output_prefix << "Found gettext" << lang << "in" << ldir.canonicalPath();
                return py::str( localedir.toStdString() );
            }
        }
    }
    cWarning() << "No translation found for languages" << candidateLanguages;
    return py::none();  // None
}

}  // namespace Python
}  // namespace Calamares

PYBIND11_EMBEDDED_MODULE( utils, m )
{
    m.doc() = "Calamares Utility API for Python";

    m.def( "obscure", &Calamares::Python::obscure, "A function that obscures (encodes) a string" );

    m.def( "debug", &Calamares::Python::debug, "Log a debug-message" );
    m.def( "warn", &Calamares::Python::warning, "Log a warning-message" );
    m.def( "warning", &Calamares::Python::warning, "Log a warning-message" );
    m.def( "error", &Calamares::Python::error, "Log an error-message" );

    m.def( "load_yaml", &Calamares::Python::load_yaml, "Loads YAML from a file." );

    m.def( "gettext_languages",
           &Calamares::Python::gettext_languages,
           "Returns list of languages (most to least-specific) for gettext." );
    m.def( "gettext_path", &Calamares::Python::gettext_path, "Returns path for gettext search." );
}

PYBIND11_MODULE( libcalamares, m )
{
    m.doc() = "Calamares API for Python";

    m.add_object( "ORGANIZATION_NAME", py::str( CALAMARES_ORGANIZATION_NAME ) );
    m.add_object( "ORGANIZATION_DOMAIN", py::str( CALAMARES_ORGANIZATION_DOMAIN ) );
    m.add_object( "APPLICATION_NAME", py::str( CALAMARES_APPLICATION_NAME ) );
    m.add_object( "VERSION", py::str( CALAMARES_VERSION ) );
    m.add_object( "VERSION_SHORT", py::str( CALAMARES_VERSION_SHORT ) );

    m.add_object( "utils", py::module::import( "utils" ) );
}
