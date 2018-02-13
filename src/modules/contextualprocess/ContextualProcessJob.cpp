/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2017-2018, Adriaan de Groot <groot@kde.org>
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

#include "ContextualProcessJob.h"

#include <QProcess>
#include <QDateTime>
#include <QThread>

#include "CalamaresVersion.h"
#include "JobQueue.h"
#include "GlobalStorage.h"

#include "utils/CalamaresUtils.h"
#include "utils/CommandList.h"
#include "utils/Logger.h"

struct ContextualProcessBinding
{
    ContextualProcessBinding( const QString& _n, const QString& _v, CalamaresUtils::CommandList* _c )
        : variable( _n )
        , value( _v )
        , commands( _c )
    {
    }

    ~ContextualProcessBinding();

    int count() const
    {
        return commands ? commands->count() : 0;
    }

    QString variable;
    QString value;
    CalamaresUtils::CommandList* commands;
} ;


ContextualProcessBinding::~ContextualProcessBinding()
{
    delete commands;
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
        if ( gs->contains( binding->variable ) && ( gs->value( binding->variable ).toString() == binding->value ) )
        {
            Calamares::JobResult r = binding->commands->run();
            if ( !r )
                return r;
        }
    }
    return Calamares::JobResult::ok();
}


void
ContextualProcessJob::setConfigurationMap( const QVariantMap& configurationMap )
{
    bool dontChroot = CalamaresUtils::getBool( configurationMap, "dontChroot", false );
    int timeout = CalamaresUtils::getInteger( configurationMap, "timeout", 10 );
    if ( timeout < 1 )
        timeout = 10;

    for ( QVariantMap::const_iterator iter = configurationMap.cbegin(); iter != configurationMap.cend(); ++iter )
    {
        QString variableName = iter.key();
        if ( variableName.isEmpty() || ( variableName == "dontChroot" ) || ( variableName == "timeout" ) )
            continue;

        if ( iter.value().type() != QVariant::Map )
        {
            cWarning() << moduleInstanceKey() << "bad configuration values for" << variableName;
            continue;
        }

        QVariantMap values = iter.value().toMap();
        for ( QVariantMap::const_iterator valueiter = values.cbegin(); valueiter != values.cend(); ++valueiter )
        {
            QString valueString = valueiter.key();
            if ( variableName.isEmpty() )
            {
                cWarning() << moduleInstanceKey() << "variable" << variableName << "unrecognized value" << valueiter.key();
                continue;
            }

            CalamaresUtils::CommandList* commands = new CalamaresUtils::CommandList( valueiter.value(), !dontChroot, timeout );

            if ( commands->count() > 0 )
            {
                m_commands.append( new ContextualProcessBinding( variableName, valueString, commands ) );
                cDebug() << variableName << '=' << valueString << "will execute" << commands->count() << "commands";
            }
            else
                delete commands;
        }
    }
}

CALAMARES_PLUGIN_FACTORY_DEFINITION( ContextualProcessJobFactory, registerPlugin<ContextualProcessJob>(); )
