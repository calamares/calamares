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

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "compat/Variant.h"
#include "locale/Global.h"
#include "partition/Mount.h"
#include "python/Pybind11Helpers.h"
#include "python/PythonJob.h"
#include "utils/Logger.h"
#include "utils/RAII.h"
#include "utils/Runner.h"
#include "utils/String.h"
#include "utils/System.h"
#include "utils/Yaml.h"

#include <QCoreApplication>
#include <QDir>
#include <QStandardPaths>

namespace py = pybind11;

/** @namespace
 *
 * Helper functions for converting Python (pybind11) types to Qt types.
 */
namespace
{
// Forward declarations, since most of these are mutually recursive
Calamares::Python::List variantListToPyList( const QVariantList& variantList );
Calamares::Python::Dictionary variantMapToPyDict( const QVariantMap& variantMap );
Calamares::Python::Dictionary variantHashToPyDict( const QVariantHash& variantHash );

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
#if QT_VERSION < QT_VERSION_CHECK( 6, 0, 0 )
#else
    // In Qt6, QChar is also available and different from CharVariantType
    case QMetaType::Type::QChar:
#endif
    case Calamares::StringVariantType:
        return Calamares::Python::String( variant.toString().toStdString() );

    case Calamares::BoolVariantType:
        return py::bool_( variant.toBool() );

#if QT_VERSION < QT_VERSION_CHECK( 6, 0, 0 )
    case QVariant::Invalid:
#endif
    default:
        return py::none();
    }
#ifdef __clang__
#pragma clang diagnostic pop
#endif
}

Calamares::Python::List
variantListToPyList( const QVariantList& variantList )
{
    Calamares::Python::List pyList;
    for ( const QVariant& variant : variantList )
    {
        pyList.append( variantToPyObject( variant ) );
    }
    return pyList;
}

Calamares::Python::Dictionary
variantMapToPyDict( const QVariantMap& variantMap )
{
    Calamares::Python::Dictionary pyDict;
    for ( auto it = variantMap.constBegin(); it != variantMap.constEnd(); ++it )
    {
        pyDict[ Calamares::Python::String( it.key().toStdString() ) ] = variantToPyObject( it.value() );
    }
    return pyDict;
}

Calamares::Python::Dictionary
variantHashToPyDict( const QVariantHash& variantHash )
{
    Calamares::Python::Dictionary pyDict;
    for ( auto it = variantHash.constBegin(); it != variantHash.constEnd(); ++it )
    {
        pyDict[ Calamares::Python::String( it.key().toStdString() ) ] = variantToPyObject( it.value() );
    }
    return pyDict;
}

QVariantList variantListFromPyList( const Calamares::Python::List& list );
QVariantMap variantMapFromPyDict( const Calamares::Python::Dictionary& dict );

QVariant
variantFromPyObject( const py::handle& o )
{
    if ( py::isinstance< Calamares::Python::Dictionary >( o ) )
    {
        return variantMapFromPyDict( py::cast< Calamares::Python::Dictionary >( o ) );
    }
    else if ( py::isinstance< Calamares::Python::List >( o ) )
    {
        return variantListFromPyList( py::cast< Calamares::Python::List >( o ) );
    }
    else if ( py::isinstance< py::int_ >( o ) )
    {
        return QVariant( qlonglong( py::cast< py::int_ >( o ) ) );
    }
    else if ( py::isinstance< py::float_ >( o ) )
    {
        return QVariant( double( py::cast< py::float_ >( o ) ) );
    }
    else if ( py::isinstance< py::str >( o ) )
    {
        return QVariant( QString::fromStdString( std::string( py::str( o ) ) ) );
    }
    else if ( py::isinstance< py::bool_ >( o ) )
    {
        return QVariant( bool( py::cast< py::bool_ >( o ) ) );
    }

    return QVariant();
}

QVariantList
variantListFromPyList( const Calamares::Python::List& list )
{
    QVariantList l;
    for ( const auto item : list )
    {
        l.append( variantFromPyObject( item ) );
    }
    return l;
}

QVariantMap
variantMapFromPyDict( const Calamares::Python::Dictionary& dict )
{
    QVariantMap m;
    for ( const auto item : dict )
    {
        m.insert( Calamares::Python::asQString( item.first ), variantFromPyObject( ( item.second ) ) );
    }
    return m;
}

QStringList
stringListFromPyList( const Calamares::Python::List& list )
{
    QStringList l;
    for ( const auto item : list )
    {
        l.append( Calamares::Python::asQString( item ) );
    }
    return l;
}

const char output_prefix[] = "[PYTHON JOB]:";
inline void
log_action( unsigned int level, const std::string& s )
{
    Logger::CDebug( level ) << output_prefix << QString::fromStdString( s );
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
    //    own GlobalStorageProxy, which then holds a
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

int
raise_on_error( const Calamares::ProcessResult& ec, const QStringList& commandList )
{
    if ( ec.first == 0 )
    {
        return 0;
    }

    QString raise = QString( "import subprocess\n"
                             "e = subprocess.CalledProcessError(%1,\"%2\")\n" )
                        .arg( ec.first )
                        .arg( commandList.join( ' ' ) );
    if ( !ec.second.isEmpty() )
    {
        raise.append( QStringLiteral( "e.output = \"\"\"%1\"\"\"\n" ).arg( ec.second ) );
    }
    raise.append( "raise e" );
    py::exec( raise.toStdString() );
    py::error_already_set();
    return ec.first;
}

int
process_output( Calamares::Utils::RunLocation location,
                const QStringList& args,
                const Calamares::Python::Object& callback,
                const std::string& input,
                int timeout )
{
    Calamares::Utils::Runner r( args );
    r.setLocation( location );
    if ( !callback.is_none() )
    {
        if ( py::isinstance< Calamares::Python::List >( callback ) )
        {
            QObject::connect( &r,
                              &decltype( r )::output,
                              [ list_append = callback.attr( "append" ) ]( const QString& s )
                              { list_append( s.toStdString() ); } );
        }
        else
        {
            QObject::connect(
                &r, &decltype( r )::output, [ &callback ]( const QString& s ) { callback( s.toStdString() ); } );
        }
        r.enableOutputProcessing();
    }
    if ( !input.empty() )
    {
        r.setInput( QString::fromStdString( input ) );
    }
    if ( timeout > 0 )
    {
        r.setTimeout( std::chrono::seconds( timeout ) );
    }

    auto result = r.run();
    return raise_on_error( result, args );
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

Dictionary
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
                return String( localedir.toStdString() );
            }
        }
    }
    cWarning() << "No translation found for languages" << candidateLanguages;
    return py::none();  // None
}

int
target_env_call( const List& args, const std::string& input, int timeout )
{
    return Calamares::System::instance()
        ->targetEnvCommand(
            stringListFromPyList( args ), QString(), QString::fromStdString( input ), std::chrono::seconds( timeout ) )
        .first;
}

int
check_target_env_call( const List& args, const std::string& input, int timeout )
{
    const auto commandList = stringListFromPyList( args );
    auto ec = Calamares::System::instance()->targetEnvCommand(
        commandList, QString(), QString::fromStdString( input ), std::chrono::seconds( timeout ) );
    return raise_on_error( ec, commandList );
}

std::string
check_target_env_output( const List& args, const std::string& input, int timeout )
{
    const auto commandList = stringListFromPyList( args );
    auto ec = Calamares::System::instance()->targetEnvCommand(
        commandList, QString(), QString::fromStdString( input ), std::chrono::seconds( timeout ) );
    raise_on_error( ec, commandList );
    return ec.second.toStdString();
}

int
target_env_process_output( const List& args, const Object& callback, const std::string& input, int timeout )
{
    return process_output(
        Calamares::System::RunLocation::RunInTarget, stringListFromPyList( args ), callback, input, timeout );
}
int
host_env_process_output( const List& args, const Object& callback, const std::string& input, int timeout )
{
    return process_output(
        Calamares::System::RunLocation::RunInHost, stringListFromPyList( args ), callback, input, timeout );
}

int
mount( const std::string& device_path,
       const std::string& mount_point,
       const std::string& filesystem_name,
       const std::string& options )
{
    return Calamares::Partition::mount( QString::fromStdString( device_path ),
                                        QString::fromStdString( mount_point ),
                                        QString::fromStdString( filesystem_name ),
                                        QString::fromStdString( options ) );
}

JobProxy::JobProxy( Calamares::Python::Job* parent )
    : prettyName( parent->prettyName().toStdString() )
    , workingPath( parent->workingPath().toStdString() )
    , moduleName( QDir( parent->workingPath() ).dirName().toStdString() )
    , configuration( variantMapToPyDict( parent->configuration() ) )
    , m_parent( parent )
{
}

void
JobProxy::setprogress( qreal progress )
{
    if ( progress >= 0.0 && progress <= 1.0 )
    {
        m_parent->emitProgress( progress );
    }
}


Calamares::GlobalStorage* GlobalStorageProxy::s_gs_instance = nullptr;

// The special handling for nullptr is only for the testing
// script for the python bindings, which passes in None;
// normal use will have a GlobalStorage from JobQueue::instance()
// passed in. Testing use will leak the allocated GlobalStorage
// object, but that's OK for testing.
GlobalStorageProxy::GlobalStorageProxy( Calamares::GlobalStorage* gs )
    : m_gs( gs ? gs : s_gs_instance )
{
    if ( !m_gs )
    {
        s_gs_instance = new Calamares::GlobalStorage;
        m_gs = s_gs_instance;
    }
}

bool
GlobalStorageProxy::contains( const std::string& key ) const
{
    return m_gs->contains( QString::fromStdString( key ) );
}

int
GlobalStorageProxy::count() const
{
    return m_gs->count();
}

void
GlobalStorageProxy::insert( const std::string& key, const Object& value )
{
    m_gs->insert( QString::fromStdString( key ), variantFromPyObject( value ) );
}

List
GlobalStorageProxy::keys() const
{
    List pyList;
    const auto keys = m_gs->keys();
    for ( const QString& key : keys )
    {
        pyList.append( key.toStdString() );
    }
    return pyList;
}

int
GlobalStorageProxy::remove( const std::string& key )
{
    const QString gsKey( QString::fromStdString( key ) );
    if ( !m_gs->contains( gsKey ) )
    {
        cWarning() << "Unknown GS key" << key.c_str();
    }
    return m_gs->remove( gsKey );
}

Object
GlobalStorageProxy::value( const std::string& key ) const
{
    const QString gsKey( QString::fromStdString( key ) );
    if ( !m_gs->contains( gsKey ) )
    {
        cWarning() << "Unknown GS key" << key.c_str();
        return py::none();
    }
    return variantToPyObject( m_gs->value( gsKey ) );
}

}  // namespace Python
}  // namespace Calamares
