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
        append( v.toString() );
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

CommandList::~CommandList() {}

static inline bool
findInCommands( const CommandList& l, const QString& needle )
{
    for ( CommandList::const_iterator i = l.cbegin(); i != l.cend(); ++i )
        if ( i->command().contains( needle ) )
        {
            return true;
        }
    return false;
}

Calamares::JobResult
CommandList::run()
{
    QLatin1String rootMagic( "@@ROOT@@" );
    QLatin1String userMagic( "@@USER@@" );

    System::RunLocation location = m_doChroot ? System::RunLocation::RunInTarget : System::RunLocation::RunInHost;

    /* Figure out the replacement for @@ROOT@@ */
    QString root = QStringLiteral( "/" );
    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();

    bool needsRootSubstitution = findInCommands( *this, rootMagic );
    if ( needsRootSubstitution && ( location == System::RunLocation::RunInHost ) )
    {
        if ( !gs || !gs->contains( "rootMountPoint" ) )
        {
            cError() << "No rootMountPoint defined.";
            return Calamares::JobResult::error(
                QCoreApplication::translate( "CommandList", "Could not run command." ),
                QCoreApplication::translate( "CommandList",
                                             "The command runs in the host environment and needs to know the root "
                                             "path, but no rootMountPoint is defined." ) );
        }
        root = gs->value( "rootMountPoint" ).toString();
    }

    bool needsUserSubstitution = findInCommands( *this, userMagic );
    if ( needsUserSubstitution && ( !gs || !gs->contains( "username" ) ) )
    {
        cError() << "No username defined.";
        return Calamares::JobResult::error(
            QCoreApplication::translate( "CommandList", "Could not run command." ),
            QCoreApplication::translate( "CommandList",
                                         "The command needs to know the user's name, but no username is defined." ) );
    }
    QString user = gs->value( "username" ).toString();  // may be blank if unset

    for ( CommandList::const_iterator i = cbegin(); i != cend(); ++i )
    {
        QString processed_cmd = i->command();
        processed_cmd.replace( rootMagic, root ).replace( userMagic, user );
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

void
CommandList::append( const QString& s )
{
    append( CommandLine( s, m_timeout ) );
}

}  // namespace CalamaresUtils
