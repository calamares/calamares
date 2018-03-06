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

struct ValueCheck : public QPair<QString, CalamaresUtils::CommandList*>
{
    ValueCheck( const QString& value, CalamaresUtils::CommandList* commands )
        : QPair<QString, CalamaresUtils::CommandList*>(value, commands)
    {
    }

    // ~ValueCheck()
    //
    // There is no destructor.
    //
    // We don't own the commandlist, the binding holding this valuecheck
    // does, so don't delete. This is closely tied to (temporaries created
    // by) pass-by-value in QList::append().

    QString value() const { return first; }
    CalamaresUtils::CommandList* commands() const { return second; }
} ;

struct ContextualProcessBinding
{
    ContextualProcessBinding( const QString& varname )
        : variable( varname )
    {
    }

    ~ContextualProcessBinding();

    /**
     * @brief add commands to be executed when @p value is matched.
     *
     * Ownership of the CommandList passes to this binding.
     */
    void append( const QString& value, CalamaresUtils::CommandList* commands )
    {
        checks.append( ValueCheck( value, commands ) );
        if ( value == '*' )
            wildcard = commands;
    }

    Calamares::JobResult run( const QString& value ) const
    {
        for ( const auto& c : checks )
        {
            if ( value == c.value() )
                return c.commands()->run();
        }

        if ( wildcard )
            return wildcard->run();

        return Calamares::JobResult::ok();
    }

    QString variable;
    QList<ValueCheck> checks;
    CalamaresUtils::CommandList* wildcard{ nullptr };
} ;


ContextualProcessBinding::~ContextualProcessBinding()
{
    wildcard = nullptr;
    for ( const auto& c : checks )
    {
        delete c.commands();
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
        if ( gs->contains( binding->variable ) )
        {
            Calamares::JobResult r = binding->run( gs->value( binding->variable ).toString() );
            if ( !r )
                return r;
        }
        else
            cWarning() << "ContextualProcess checks for unknown variable" << binding->variable;
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

        auto binding = new ContextualProcessBinding( variableName );
        m_commands.append( binding );
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
ContextualProcessJob::count(const QString& variableName)
{
    for ( const ContextualProcessBinding* binding : m_commands )
        if ( binding->variable == variableName )
            return binding->checks.count();
    return -1;
}

CALAMARES_PLUGIN_FACTORY_DEFINITION( ContextualProcessJobFactory, registerPlugin<ContextualProcessJob>(); )
