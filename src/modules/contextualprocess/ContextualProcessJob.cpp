/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2017-2020, Adriaan de Groot <groot@kde.org>
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

#include <QDateTime>
#include <QProcess>
#include <QThread>

#include "CalamaresVersion.h"
#include "GlobalStorage.h"
#include "JobQueue.h"

#include "utils/CommandList.h"
#include "utils/Logger.h"
#include "utils/Variant.h"

struct ValueCheck : public QPair< QString, CalamaresUtils::CommandList* >
{
    ValueCheck( const QString& value, CalamaresUtils::CommandList* commands )
        : QPair< QString, CalamaresUtils::CommandList* >( value, commands )
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
};

class ContextualProcessBinding
{
public:
    ContextualProcessBinding( const QString& varname )
        : m_variable( varname )
    {
    }

    ~ContextualProcessBinding();

    QString variable() const { return m_variable; }
    int count() const { return m_checks.count(); }

    /**
     * @brief add commands to be executed when @p value is matched.
     *
     * Ownership of the CommandList passes to this binding.
     */
    void append( const QString& value, CalamaresUtils::CommandList* commands )
    {
        m_checks.append( ValueCheck( value, commands ) );
        if ( value == QString( "*" ) )
        {
            m_wildcard = commands;
        }
    }

    Calamares::JobResult run( const QString& value ) const
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

    /** @brief Tries to obtain this binding's value from GS
     *
     * Stores the value in @p value and returns true if a value
     * was found (e.g. @p storage contains the variable this binding
     * is for) and false otherwise.
     */
    bool fetch( Calamares::GlobalStorage* storage, QString& value ) const
    {
        value.clear();
        if ( !storage )
        {
            return false;
        }
        if ( m_variable.contains( '.' ) )
        {
            QStringList steps = m_variable.split( '.' );
            return fetch( value, steps, 1, storage->value( steps.first() ) );
        }
        else
        {
            value = storage->value( m_variable ).toString();
            return storage->contains( m_variable );
        }
    }

private:
    static bool fetch( QString& value, QStringList& selector, int index, const QVariant& v )
    {
        if ( !v.canConvert( QMetaType::QVariantMap ) )
        {
            return false;
        }
        const QVariantMap map = v.toMap();
        const QString& key = selector.at( index );
        if ( index == selector.length() )
        {
            value = map.value( key ).toString();
            return map.contains( key );
        }
        else
        {
            return fetch( value, selector, index + 1, map.value( key ) );
        }
    }

    QString m_variable;
    QList< ValueCheck > m_checks;
    CalamaresUtils::CommandList* m_wildcard = nullptr;
};


ContextualProcessBinding::~ContextualProcessBinding()
{
    m_wildcard = nullptr;
    for ( const auto& c : m_checks )
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
