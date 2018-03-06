/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2018, Adriaan de Groot <groot@kde.org>
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

#include "CommandList.h"

#include "GlobalStorage.h"
#include "JobQueue.h"

#include "utils/CalamaresUtils.h"
#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"

#include <QCoreApplication>
#include <QVariantList>

namespace CalamaresUtils
{

static CommandLine get_variant_object( const QVariantMap& m )
{
    QString command = CalamaresUtils::getString( m, "command" );
    int timeout = CalamaresUtils::getInteger( m, "timeout", CommandLine::TimeoutNotSet );

    if ( !command.isEmpty() )
        return CommandLine( command, timeout );
    cWarning() << "Bad CommandLine element" << m;
    return CommandLine();
}

static CommandList_t get_variant_stringlist( const QVariantList& l )
{
    CommandList_t retl;
    unsigned int c = 0;
    for ( const auto& v : l )
    {
        if ( v.type() == QVariant::String )
            retl.append( CommandLine( v.toString(), CommandLine::TimeoutNotSet ) );
        else if ( v.type() == QVariant::Map )
        {
            auto c( get_variant_object( v.toMap() ) );
            if ( c.isValid() )
                retl.append( c );
            // Otherwise warning is already given
        }
        else
            cWarning() << "Bad CommandList element" << c << v.type() << v;
        ++c;
    }
    return retl;
}

CommandList::CommandList( bool doChroot, int timeout )
    : m_doChroot( doChroot )
    , m_timeout( timeout )
{
}

CommandList::CommandList::CommandList( const QVariant& v, bool doChroot, int timeout )
    : CommandList( doChroot, timeout )
{
    if ( v.type() == QVariant::List )
    {
        const auto v_list = v.toList();
        if ( v_list.count() )
            append( get_variant_stringlist( v_list ) );
        else
            cWarning() << "Empty CommandList";
    }
    else if ( v.type() == QVariant::String )
        append( v.toString() );
    else if ( v.type() == QVariant::Map )
    {
        auto c( get_variant_object( v.toMap() ) );
        if ( c.isValid() )
            append( c );
        // Otherwise warning is already given
    }
    else
        cWarning() << "CommandList does not understand variant" << v.type();
}

CommandList::~CommandList()
{
}

Calamares::JobResult CommandList::run()
{
    System::RunLocation location = m_doChroot ? System::RunLocation::RunInTarget : System::RunLocation::RunInHost;

    /* Figure out the replacement for @@ROOT@@ */
    QString root = QStringLiteral( "/" );
    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
    if ( location == System::RunLocation::RunInTarget )
    {
        if ( !gs || !gs->contains( "rootMountPoint" ) )
        {
            cError() << "No rootMountPoint defined.";
            return Calamares::JobResult::error( QCoreApplication::translate( "CommandList", "Could not run command." ),
                                                QCoreApplication::translate( "CommandList", "No rootMountPoint is defined, so command cannot be run in the target environment." ) );
        }
        root = gs->value( "rootMountPoint" ).toString();
    }

    for ( CommandList::const_iterator i = cbegin(); i != cend(); ++i )
    {
        QString processed_cmd = i->command();
        processed_cmd.replace( "@@ROOT@@", root );
        bool suppress_result = false;
        if ( processed_cmd.startsWith( '-' ) )
        {
            suppress_result = true;
            processed_cmd.remove( 0, 1 );  // Drop the -
        }

        QStringList shell_cmd { "/bin/sh", "-c" };
        shell_cmd << processed_cmd;

        int timeout = i->timeout() >= 0 ? i->timeout() : m_timeout;
        ProcessResult r = System::runCommand(
                              location, shell_cmd, QString(), QString(), timeout );

        if ( r.getExitCode() != 0 )
        {
            if ( suppress_result )
                cDebug() << "Error code" << r.getExitCode() << "ignored by CommandList configuration.";
            else
                return r.explainProcess( processed_cmd, timeout );
        }
    }

    return Calamares::JobResult::ok();
}

void
CommandList::append( const QString& s )
{
    append( CommandLine( s, m_timeout ) );
}

}  // namespace
