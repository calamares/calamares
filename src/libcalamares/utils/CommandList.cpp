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

#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"

#include <QVariantList>

static QStringList get_variant_stringlist( const QVariantList& l )
{
    QStringList retl;
    unsigned int c = 0;
    for ( const auto& v : l )
    {
        if ( v.type() == QVariant::String )
            retl.append( v.toString() );
        else
            cDebug() << "WARNING Bad CommandList element" << c << v.type() << v;
        ++c;
    }
    return retl;
}

namespace CalamaresUtils
{

CommandList::CommandList( bool doChroot )
    : m_doChroot( doChroot )
{
}

CommandList::CommandList::CommandList( const QVariant& v, bool doChroot )
    : CommandList( doChroot )
{
    if ( v.type() == QVariant::List )
    {
        const auto v_list = v.toList();
        if ( v_list.count() )
            append( get_variant_stringlist( v_list ) );
        else
            cDebug() << "WARNING: Empty CommandList";
    }
    else if ( v.type() == QVariant::String )
        append( v.toString() );
    else
        cDebug() << "WARNING: CommandList does not understand variant" << v.type();
}

CommandList::~CommandList()
{
}

Calamares::JobResult CommandList::run( const QObject* parent )
{
    System::RunLocation location = m_doChroot ? System::RunLocation::RunInTarget : System::RunLocation::RunInHost;

    /* Figure out the replacement for @@ROOT@@ */
    QString root = QStringLiteral( "/" );
    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
    if ( location == System::RunLocation::RunInTarget )
    {
        if ( !gs || !gs->contains( "rootMountPoint" ) )
        {
            cDebug() << "ERROR: No rootMountPoint defined.";
            return Calamares::JobResult::error( parent->tr( "Could not run command." ),
                                                parent->tr( "No rootMountPoint is defined, so command cannot be run in the target environment." ) );
        }
        root = gs->value( "rootMountPoint" ).toString();
    }

    for ( CommandList::const_iterator i = cbegin(); i != cend(); ++i )
    {
        QString processed_cmd = *i;
        processed_cmd.replace( "@@ROOT@@", root );  // FIXME?
        bool suppress_result = false;
        if ( processed_cmd.startsWith( '-' ) )
        {
            suppress_result = true;
            processed_cmd.remove( 0, 1 );  // Drop the -  // FIXME?
        }

        QStringList shell_cmd { "/bin/sh", "-c" };
        shell_cmd << processed_cmd;

        ProcessResult r = System::runCommand(
                              location, shell_cmd, QString(), QString(), 10 );

        if ( r.getExitCode() != 0 )
        {
            if ( suppress_result )
                cDebug() << "Error code" << r.getExitCode() << "ignored by ShellProcess configuration.";
            else
                return r.explainProcess( parent, processed_cmd, 10 );
        }
    }

    return Calamares::JobResult::ok();
}

}  // namespace
