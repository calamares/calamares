/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2017-2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "ContextualProcessJob.h"

#include "Binding.h"

#include "CalamaresVersion.h"
#include "GlobalStorage.h"
#include "JobQueue.h"

#include "utils/CommandList.h"
#include "utils/Logger.h"
#include "utils/Variant.h"


ContextualProcessBinding::~ContextualProcessBinding()
{
    m_wildcard = nullptr;
    for ( const auto& c : m_checks )
    {
        delete c.commands();
    }
}

void
ContextualProcessBinding::append( const QString& value, CalamaresUtils::CommandList* commands )
{
    m_checks.append( ValueCheck( value, commands ) );
    if ( value == QString( "*" ) )
    {
        m_wildcard = commands;
    }
}

Calamares::JobResult
ContextualProcessBinding::run( const QString& value ) const
{
    for ( const auto& c : m_checks )
    {
        if ( value == c.value() )
        {
            return c.commands()->run();
        }
    }

    if ( m_wildcard )
    {
        return m_wildcard->run();
    }

    return Calamares::JobResult::ok();
}

///@brief Implementation of fetch() for recursively looking up dotted selector parts.
static bool
fetch( QString& value, QStringList& selector, int index, const QVariant& v )
{
    if ( !v.canConvert( QMetaType::QVariantMap ) )
    {
        return false;
    }
    const QVariantMap map = v.toMap();
    const QString& key = selector.at( index );
    if ( index == selector.length() - 1 )
    {
        value = map.value( key ).toString();
        return map.contains( key );
    }
    else
    {
        return fetch( value, selector, index + 1, map.value( key ) );
    }
}


bool
ContextualProcessBinding::fetch( Calamares::GlobalStorage* storage, QString& value ) const
{
    value.clear();
    if ( !storage )
    {
        return false;
    }
    if ( m_variable.contains( '.' ) )
    {
        QStringList steps = m_variable.split( '.' );
        return ::fetch( value, steps, 1, storage->value( steps.first() ) );
    }
    else
    {
        value = storage->value( m_variable ).toString();
        return storage->contains( m_variable );
    }
}


ContextualProcessJob::ContextualProcessJob( QObject* parent )
    : Calamares::CppJob( parent )
{
}


ContextualProcessJob::~ContextualProcessJob()
{
    qDeleteAll( m_commands );
}


QString
ContextualProcessJob::prettyName() const
{
    return tr( "Contextual Processes Job" );
}


Calamares::JobResult
ContextualProcessJob::exec()
{
    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();

    for ( const ContextualProcessBinding* binding : m_commands )
    {
        QString value;
        if ( binding->fetch( gs, value ) )
        {
            Calamares::JobResult r = binding->run( value );
            if ( !r )
            {
                return r;
            }
        }
        else
        {
            cWarning() << "ContextualProcess checks for unknown variable" << binding->variable();
        }
    }
    return Calamares::JobResult::ok();
}


void
ContextualProcessJob::setConfigurationMap( const QVariantMap& configurationMap )
{
    bool dontChroot = CalamaresUtils::getBool( configurationMap, "dontChroot", false );
    qint64 timeout = CalamaresUtils::getInteger( configurationMap, "timeout", 10 );
    if ( timeout < 1 )
    {
        timeout = 10;
    }

    for ( QVariantMap::const_iterator iter = configurationMap.cbegin(); iter != configurationMap.cend(); ++iter )
    {
        QString variableName = iter.key();
        if ( variableName.isEmpty() || ( variableName == "dontChroot" ) || ( variableName == "timeout" ) )
        {
            continue;
        }

        if ( iter.value().type() != QVariant::Map )
        {
            cWarning() << moduleInstanceKey() << "bad configuration values for" << variableName;
            continue;
        }

        auto binding = new ContextualProcessBinding( variableName );
        m_commands.append( binding );
        QVariantMap values = iter.value().toMap();
        for ( QVariantMap::const_iterator valueiter = values.cbegin(); valueiter != values.cend(); ++valueiter )
        {
            QString valueString = valueiter.key();
            if ( variableName.isEmpty() )
            {
                cWarning() << moduleInstanceKey() << "variable" << variableName << "unrecognized value"
                           << valueiter.key();
                continue;
            }

            CalamaresUtils::CommandList* commands
                = new CalamaresUtils::CommandList( valueiter.value(), !dontChroot, std::chrono::seconds( timeout ) );

            binding->append( valueString, commands );
        }
    }
}

int
ContextualProcessJob::count()
{
    return m_commands.count();
}

int
ContextualProcessJob::count( const QString& variableName )
{
    for ( const ContextualProcessBinding* binding : m_commands )
    {
        if ( binding->variable() == variableName )
        {
            return binding->count();
        }
    }
    return -1;
}

CALAMARES_PLUGIN_FACTORY_DEFINITION( ContextualProcessJobFactory, registerPlugin< ContextualProcessJob >(); )
