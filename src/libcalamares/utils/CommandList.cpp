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

#include "compat/Variant.h"
#include "locale/Global.h"
#include "utils/Logger.h"
#include "utils/StringExpander.h"
#include "utils/System.h"
#include "utils/Variant.h"

#include <QCoreApplication>
#include <QVariantList>

namespace Calamares
{

static CommandList_t
get_variant_stringlist( const QVariantList& l )
{
    CommandList_t retl;
    unsigned int count = 0;
    for ( const auto& v : l )
    {
        if ( Calamares::typeOf( v ) == Calamares::StringVariantType )
        {
            retl.append( CommandLine( v.toString(), CommandLine::TimeoutNotSet() ) );
        }
        else if ( Calamares::typeOf( v ) == Calamares::MapVariantType )
        {
            CommandLine command( v.toMap() );
            if ( command.isValid() )
            {
                retl.append( command );
            }
            // Otherwise warning is already given
        }
        else
        {
            cWarning() << "Bad CommandList element" << count << v;
        }
        ++count;
    }
    return retl;
}

/** @brief Inserts the keys from @p map into @p expander as "gs"-keys
 *
 * For each key k in @p map, a key with literal `gs[` + prefix + '.' + key +
 * literal `]` is inserted into the exapander.
 */
static void
expand_tree( Calamares::String::DictionaryExpander& expander, const QString& prefix, const QVariantMap& map )
{
    // With the current prefix, turn a key into gs[prefix.key]
    auto gs_key = [ &prefix ]( const QString& k ) -> QString
    { return QStringLiteral( "gs[" ) + ( prefix.isEmpty() ? QString() : prefix + '.' ) + k + ']'; };

    for ( QVariantMap::const_iterator valueiter = map.cbegin(); valueiter != map.cend(); ++valueiter )
    {
        const QString key = valueiter.key();
        const QVariant value = valueiter.value();

        switch ( Calamares::typeOf( value ) )
        {
        case Calamares::MapVariantType:
            expand_tree( expander, prefix.isEmpty() ? key : ( prefix + '.' + key ), value.toMap() );
            break;
        case Calamares::StringVariantType:
            expander.add( gs_key( key ), value.toString() );
            break;
        case Calamares::IntVariantType:
            expander.add( gs_key( key ), QString::number( value.toInt() ) );
            break;
        default:
            // Silently ignore
            break;
        }
    }
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

    if ( gs )
    {
        const auto key = QStringLiteral( "LANG" );
        const QString lang = Calamares::Locale::readGS( *gs, key );
        if ( !lang.isEmpty() )
        {
            expander.insert( key, lang );
        }
    }

    if ( gs )
    {
        expand_tree( expander, QString(), gs->data() );
    }

    return expander;
}

CommandLine::CommandLine( const QVariantMap& m )
{
    const QString command = Calamares::getString( m, "command" );
    const qint64 timeout = Calamares::getInteger( m, "timeout", -1 );
    if ( !command.isEmpty() )
    {
        m_command = command;
        m_timeout = timeout >= 0 ? std::chrono::seconds( timeout ) : CommandLine::TimeoutNotSet();
        m_environment = Calamares::getStringList( m, "environment" );
    }
    else
    {
        cWarning() << "Bad CommandLine element" << m;
        // this CommandLine is invalid
    }
}

CommandLine
CommandLine::expand( KMacroExpanderBase& expander ) const
{
    // Calamares variable expansion in the command
    QString c = m_command;
    expander.expandMacrosShellQuote( c );

    // .. and expand in each environment key=value string.
    QStringList e = m_environment;
    std::for_each( e.begin(), e.end(), [ &expander ]( QString& s ) { expander.expandMacrosShellQuote( s ); } );

    return { c, m_environment, m_timeout };
}

Calamares::CommandLine
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
    if ( Calamares::typeOf( v ) == Calamares::ListVariantType )
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
    else if ( Calamares::typeOf( v ) == Calamares::StringVariantType )
    {
        append( { v.toString(), m_timeout } );
    }
    else if ( Calamares::typeOf( v ) == Calamares::MapVariantType )
    {
        CommandLine c( v.toMap() );
        if ( c.isValid() )
        {
            append( c );
        }
        // Otherwise warning is already given
    }
    else
    {
        cWarning() << "CommandList does not understand variant" << Calamares::typeOf( v );
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

        const QString environmentSetting = []( const QStringList& l ) -> QString
        {
            if ( l.isEmpty() )
            {
                return {};
            }

            return QStringLiteral( "export " ) + l.join( " " ) + QStringLiteral( " ; " );
        }( i->environment() );

        QStringList shell_cmd { "/bin/sh", "-c" };
        shell_cmd << ( environmentSetting + processed_cmd );

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

}  // namespace Calamares
