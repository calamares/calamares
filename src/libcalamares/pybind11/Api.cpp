/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017-2020, 2023 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */
#include "Api.h"

#include "Pybind11Helpers.h"
#include "PythonJob.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "compat/Variant.h"
#include "locale/Global.h"
#include "python/Variant.h"
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

int
target_env_call( const List& args, const std::string& input, int timeout )
{
    return Calamares::System::instance()
        ->targetEnvCommand(
            stringListFromPyList( args ), QString(), QString::fromStdString( input ), std::chrono::seconds( timeout ) )
        .first;
}

int
target_env_call( const std::string& command, const std::string& input, int timeout )
{
    return Calamares::System::instance()
        ->targetEnvCommand( { QString::fromStdString( command ) },
                            QString(),
                            QString::fromStdString( input ),
                            std::chrono::seconds( timeout ) )
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

JobProxy::JobProxy( Calamares::Python::Job* parent )
    : prettyName( parent->prettyName().toStdString() )
    , workingPath( parent->workingPath().toStdString() )
    , moduleName( QDir( parent->workingPath() ).dirName().toStdString() )
    , configuration( Calamares::Python::variantMapToPyDict( parent->configuration() ) )
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
    return Calamares::Python::variantToPyObject( m_gs->value( gsKey ) );
}

}  // namespace Python
}  // namespace Calamares
