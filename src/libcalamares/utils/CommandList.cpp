/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#include "CommandList.h"

#include "GlobalStorage.h"
#include "JobQueue.h"

// #include "utils/CalamaresUtils.h"
#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"
#include "utils/StringExpander.h"
#include "utils/Variant.h"

#include <QCoreApplication>
#include <QVariantList>

namespace CalamaresUtils
{

static CommandLine
get_variant_object( const QVariantMap& m )
{
    QString command = CalamaresUtils::getString( m, "command" );
    qint64 timeout = CalamaresUtils::getInteger( m, "timeout", -1 );

    if ( !command.isEmpty() )
    {
        return CommandLine( command, timeout >= 0 ? std::chrono::seconds( timeout ) : CommandLine::TimeoutNotSet() );
    }
    cWarning() << "Bad CommandLine element" << m;
    return CommandLine();
}

static CommandList_t
get_variant_stringlist( const QVariantList& l )
{
    CommandList_t retl;
    unsigned int count = 0;
    for ( const auto& v : l )
    {
        if ( v.type() == QVariant::String )
        {
            retl.append( CommandLine( v.toString(), CommandLine::TimeoutNotSet() ) );
        }
        else if ( v.type() == QVariant::Map )
        {
            auto command( get_variant_object( v.toMap() ) );
            if ( command.isValid() )
            {
                retl.append( command );
            }
            // Otherwise warning is already given
        }
        else
        {
            cWarning() << "Bad CommandList element" << count << v.type() << v;
        }
        ++count;
    }
    return retl;
}

static Calamares::String::DictionaryExpander
get_gs_expander( System::RunLocation location )
{
    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();

    Calamares::String::DictionaryExpander expander;

    // Figure out the replacement for ${ROOT}
    if ( location == System::RunLocation::RunInTarget )
    {
        expander.insert( QStringLiteral( "ROOT" ), QStringLiteral( "/" ) );
    }
    else if ( gs && gs->contains( "rootMountPoint" ) )
    {
        expander.insert( QStringLiteral( "ROOT" ), gs->value( "rootMountPoint" ).toString() );
    }

    // Replacement for ${USER}
    if ( gs && gs->contains( "username" ) )
    {
        expander.insert( QStringLiteral( "USER" ), gs->value( "username" ).toString() );
    }

    return expander;
}

CommandLine
CommandLine::expand( KMacroExpanderBase& expander ) const
{
    QString c = first;
    expander.expandMacrosShellQuote( c );
    return { c, second };
}

CalamaresUtils::CommandLine
CommandLine::expand() const
{
    auto expander = get_gs_expander( System::RunLocation::RunInHost );
    return expand( expander );
}


CommandList::CommandList( bool doChroot, std::chrono::seconds timeout )
    : m_doChroot( doChroot )
    , m_timeout( timeout )
{
}

CommandList::CommandList::CommandList( const QVariant& v, bool doChroot, std::chrono::seconds timeout )
    : CommandList( doChroot, timeout )
{
    if ( v.type() == QVariant::List )
    {
        const auto v_list = v.toList();
        if ( v_list.count() )
        {
            append( get_variant_stringlist( v_list ) );
        }
        else
        {
            cWarning() << "Empty CommandList";
        }
    }
    else if ( v.type() == QVariant::String )
    {
        append( { v.toString(), m_timeout } );
    }
    else if ( v.type() == QVariant::Map )
    {
        auto c( get_variant_object( v.toMap() ) );
        if ( c.isValid() )
        {
            append( c );
        }
        // Otherwise warning is already given
    }
    else
    {
        cWarning() << "CommandList does not understand variant" << v.type();
    }
}

Calamares::JobResult
CommandList::run()
{
    System::RunLocation location = m_doChroot ? System::RunLocation::RunInTarget : System::RunLocation::RunInHost;

    auto expander = get_gs_expander( location );
    auto expandedList = expand( expander );
    if ( expander.hasErrors() )
    {
        const auto missing = expander.errorNames();
        cError() << "Missing variables:" << missing;
        return Calamares::JobResult::error(
            QCoreApplication::translate( "CommandList", "Could not run command." ),
            QCoreApplication::translate( "CommandList",
                                         "The commands use variables that are not defined. "
                                         "Missing variables are: %1." )
                .arg( missing.join( ',' ) ) );
    }

    for ( CommandList::const_iterator i = expandedList.cbegin(); i != expandedList.cend(); ++i )
    {
        QString processed_cmd = i->command();
        bool suppress_result = false;
        if ( processed_cmd.startsWith( '-' ) )
        {
            suppress_result = true;
            processed_cmd.remove( 0, 1 );  // Drop the -
        }

        QStringList shell_cmd { "/bin/sh", "-c" };
        shell_cmd << processed_cmd;

        std::chrono::seconds timeout = i->timeout() >= std::chrono::seconds::zero() ? i->timeout() : m_timeout;
        ProcessResult r = System::runCommand( location, shell_cmd, QString(), QString(), timeout );

        if ( r.getExitCode() != 0 )
        {
            if ( suppress_result )
            {
                cDebug() << "Error code" << r.getExitCode() << "ignored by CommandList configuration.";
            }
            else
            {
                return r.explainProcess( processed_cmd, timeout );
            }
        }
    }

    return Calamares::JobResult::ok();
}

CommandList
CommandList::expand( KMacroExpanderBase& expander ) const
{
    // Copy and expand the list, collecting missing variables (so don't call expand())
    CommandList expandedList( m_doChroot, m_timeout );
    std::transform( cbegin(),
                    cend(),
                    std::back_inserter( expandedList ),
                    [ &expander ]( const CommandLine& c ) { return c.expand( expander ); } );
    return expandedList;
}

CommandList
CommandList::expand() const
{
    auto expander = get_gs_expander( System::RunLocation::RunInHost );
    return expand( expander );
}


}  // namespace CalamaresUtils
