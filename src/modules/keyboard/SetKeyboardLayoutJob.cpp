/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2011 Lennart Poettering
 *   SPDX-FileCopyrightText: Kay Sievers
 *   SPDX-FileCopyrightText: 2014-2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2014 Kevin Kofler <kevin.kofler@chello.at>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Portions from systemd (localed.c):
 *   Copyright 2011 Lennart Poettering
 *   Copyright 2013 Kay Sievers
 *   (originally under LGPLv2.1+, used under the LGPL to GPL conversion clause)
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "SetKeyboardLayoutJob.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/Logger.h"
#include "utils/String.h"
#include "utils/System.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QSettings>
#include <QTextStream>

namespace
{
QStringList
removeEmpty( QStringList&& list )
{
    list.removeAll( QString() );
    return list;
}
}  // namespace

SetKeyboardLayoutJob::SetKeyboardLayoutJob( const QString& model,
                                            const QString& layout,
                                            const QString& variant,
                                            const AdditionalLayoutInfo& additionalLayoutInfo,
                                            const QString& xOrgConfFileName,
                                            const QString& convertedKeymapPath,
                                            bool writeEtcDefaultKeyboard,
                                            bool skipIfNoRoot )
    : Calamares::Job()
    , m_model( model )
    , m_layout( layout )
    , m_variant( variant )
    , m_additionalLayoutInfo( additionalLayoutInfo )
    , m_xOrgConfFileName( xOrgConfFileName )
    , m_convertedKeymapPath( convertedKeymapPath )
    , m_writeEtcDefaultKeyboard( writeEtcDefaultKeyboard )
    , m_skipIfNoRoot( skipIfNoRoot )
{
}


QString
SetKeyboardLayoutJob::prettyName() const
{
    return tr( "Setting keyboard model to %1, layout as %2-%3…", "@status, %1 model, %2 layout, %3 variant" )
        .arg( m_model )
        .arg( m_layout )
        .arg( m_variant );
}


QString
SetKeyboardLayoutJob::findConvertedKeymap( const QString& convertedKeymapPath ) const
{
    cDebug() << "Looking for converted keymap in" << convertedKeymapPath;

    // No search path supplied, assume the distribution does not provide
    // converted keymaps
    if ( convertedKeymapPath.isEmpty() )
    {
        return QString();
    }

    QDir convertedKeymapDir( convertedKeymapPath );
    QString name = m_variant.isEmpty() ? m_layout : ( m_layout + '-' + m_variant );

    if ( convertedKeymapDir.exists( name + ".map" ) || convertedKeymapDir.exists( name + ".map.gz" ) )
    {
        cDebug() << Logger::SubEntry << "Found converted keymap" << name;
        return name;
    }

    return QString();
}


STATICTEST QString
findLegacyKeymap( const QString& layout, const QString& model, const QString& variant )
{
    cDebug() << "Looking for legacy keymap" << layout << model << variant << "in QRC";

    int bestMatching = 0;
    QString name;

    QFile file( ":/kbd-model-map" );
    if ( !file.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        cDebug() << Logger::SubEntry << "Could not read QRC";
        return QString();
    }

    QTextStream stream( &file );
    while ( !stream.atEnd() )
    {
        QString line = stream.readLine().trimmed();
        if ( line.isEmpty() || line.startsWith( '#' ) )
        {
            continue;
        }

        QStringList mapping = line.split( '\t', SplitSkipEmptyParts );
        if ( mapping.size() < 5 )
        {
            continue;
        }

        int matching = 0;

        // Determine how well matching this entry is
        // We assume here that we have one X11 layout. If the UI changes to
        // allow more than one layout, this should change too.
        if ( layout == mapping[ 1 ] )
        // If we got an exact match, this is best
        {
            matching = 10;
        }
        // Look for an entry whose first layout matches ours
        else if ( mapping[ 1 ].startsWith( layout + ',' ) )
        {
            matching = 5;
        }

        if ( matching > 0 )
        {
            if ( model.isEmpty() || model == mapping[ 2 ] )
            {
                matching++;
            }

            QString mappingVariant = mapping[ 3 ];
            if ( mappingVariant == "-" )
            {
                mappingVariant = QString();
            }
            else if ( mappingVariant.startsWith( ',' ) )
            {
                mappingVariant.remove( 1, 0 );
            }

            if ( variant == mappingVariant )
            {
                matching++;
            }

            // We ignore mapping[4], the xkb options, for now. If we ever
            // allow setting options in the UI, we should match them here.
        }

        // The best matching entry so far, then let's save that
        if ( matching >= qMax( bestMatching, 1 ) )
        {
            cDebug() << Logger::SubEntry << "Found legacy keymap" << mapping[ 0 ] << "with score" << matching;

            if ( matching > bestMatching )
            {
                bestMatching = matching;
                name = mapping[ 0 ];
            }
        }
    }

    return name;
}

QString
SetKeyboardLayoutJob::findLegacyKeymap() const
{
    return ::findLegacyKeymap( m_layout, m_model, m_variant );
}

bool
SetKeyboardLayoutJob::writeVConsoleData( const QString& vconsoleConfPath, const QString& convertedKeymapPath ) const
{
    cDebug() << "Writing vconsole data to" << vconsoleConfPath;

    QString keymap = findConvertedKeymap( convertedKeymapPath );
    if ( keymap.isEmpty() )
    {
        keymap = findLegacyKeymap();
    }
    if ( keymap.isEmpty() )
    {
        cDebug() << "Trying to use X11 layout" << m_layout << "as the virtual console layout";
        keymap = m_layout;
    }

    QStringList existingLines;

    // Read in the existing vconsole.conf, if it exists
    QFile file( vconsoleConfPath );
    if ( file.exists() )
    {
        file.open( QIODevice::ReadOnly | QIODevice::Text );
        QTextStream stream( &file );
        while ( !stream.atEnd() )
        {
            existingLines << stream.readLine();
        }
        file.close();
        if ( stream.status() != QTextStream::Ok )
        {
            cError() << "Could not read lines from" << file.fileName();
            return false;
        }
    }

    // Write out the existing lines and replace the KEYMAP= line
    if ( !file.open( QIODevice::WriteOnly | QIODevice::Text ) )
    {
        cError() << "Could not open" << file.fileName() << "for writing.";
        return false;
    }
    QTextStream stream( &file );
    bool found = false;
    for ( const QString& existingLine : qAsConst( existingLines ) )
    {
        if ( existingLine.trimmed().startsWith( "KEYMAP=" ) )
        {
            stream << "KEYMAP=" << keymap << '\n';
            found = true;
        }
        else
        {
            stream << existingLine << '\n';
        }
    }
    // Add a KEYMAP= line if there wasn't any
    if ( !found )
    {
        stream << "KEYMAP=" << keymap << '\n';
    }
    stream.flush();
    file.close();

    cDebug() << Logger::SubEntry << "Written KEYMAP=" << keymap << "to vconsole.conf" << stream.status();

    return ( stream.status() == QTextStream::Ok );
}


bool
SetKeyboardLayoutJob::writeX11Data( const QString& keyboardConfPath ) const
{
    cDebug() << "Writing X11 configuration to" << keyboardConfPath;

    QFile file( keyboardConfPath );
    if ( !file.open( QIODevice::WriteOnly | QIODevice::Text ) )
    {
        cError() << "Could not open" << file.fileName() << "for writing.";
        return false;
    }
    QTextStream stream( &file );

    stream << "# Read and parsed by systemd-localed. It's probably wise not to edit this file\n"
              "# manually too freely.\n"
              "Section \"InputClass\"\n"
              "        Identifier \"system-keyboard\"\n"
              "        MatchIsKeyboard \"on\"\n";


    const QStringList layouts = removeEmpty( { m_additionalLayoutInfo.additionalLayout, m_layout } );
    const QStringList variants = removeEmpty( { m_additionalLayoutInfo.additionalVariant, m_variant } );
    stream << "        Option \"XkbLayout\" \"" << layouts.join( "," ) << "\"\n";
    stream << "        Option \"XkbVariant\" \"" << variants.join( "," ) << "\"\n";
    if ( !m_additionalLayoutInfo.additionalLayout.isEmpty() )
    {
        stream << "        Option \"XkbOptions\" \"" << m_additionalLayoutInfo.groupSwitcher << "\"\n";
    }

    stream << "EndSection\n";
    stream.flush();

    file.close();

    cDebug() << Logger::SubEntry << "Written XkbLayout" << layouts.join( "," ) << "; XkbModel" << m_model
             << "; XkbVariant" << variants.join( "," ) << "to X.org file" << keyboardConfPath << stream.status();

    return ( stream.status() == QTextStream::Ok );
}


bool
SetKeyboardLayoutJob::writeDefaultKeyboardData( const QString& defaultKeyboardPath ) const
{
    cDebug() << "Writing default keyboard data to" << defaultKeyboardPath;

    QFile file( defaultKeyboardPath );
    if ( !file.open( QIODevice::WriteOnly | QIODevice::Text ) )
    {
        cError() << "Could not open" << defaultKeyboardPath << "for writing";
        return false;
    }
    QTextStream stream( &file );

    const QStringList layouts = removeEmpty( { m_additionalLayoutInfo.additionalLayout, m_layout } );
    const QStringList variants = removeEmpty( { m_additionalLayoutInfo.additionalVariant, m_variant } );
    stream << "# KEYBOARD CONFIGURATION FILE\n\n"
              "# Consult the keyboard(5) manual page.\n\n";

    stream << "XKBMODEL=\"" << m_model << "\"\n";
    stream << "XKBLAYOUT=\"" << layouts.join( "," ) << "\"\n";
    stream << "XKBVARIANT=\"" << variants.join( "," ) << "\"\n";
    if ( !m_additionalLayoutInfo.additionalLayout.isEmpty() )
    {
        stream << "XKBOPTIONS=\"" << m_additionalLayoutInfo.groupSwitcher << "\"\n";
    }
    stream << "BACKSPACE=\"guess\"\n";
    stream.flush();

    file.close();

    cDebug() << Logger::SubEntry << "Written XKBMODEL" << m_model << "; XKBLAYOUT" << layouts.join( "," )
             << "; XKBVARIANT" << variants.join( "," ) << "to /etc/default/keyboard file" << defaultKeyboardPath
             << stream.status();

    return ( stream.status() == QTextStream::Ok );
}


Calamares::JobResult
SetKeyboardLayoutJob::exec()
{
    cDebug() << "Executing SetKeyboardLayoutJob";
    // Read the location of the destination's / in the host file system from
    // the global settings
    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
    QDir destDir( gs->value( "rootMountPoint" ).toString() );

    // Skip this if we are using locale1 and we are configuring the local system,
    // since the service will have already updated these configs for us.
    if ( !( m_skipIfNoRoot && ( destDir.isEmpty() || destDir.isRoot() ) ) )
    {
        // Get the path to the destination's /etc/vconsole.conf
        QString vconsoleConfPath = destDir.absoluteFilePath( "etc/vconsole.conf" );

        // Get the path to the destination's path to the converted key mappings
        QString convertedKeymapPath = m_convertedKeymapPath;
        if ( !convertedKeymapPath.isEmpty() )
        {
            while ( convertedKeymapPath.startsWith( '/' ) )
            {
                convertedKeymapPath.remove( 0, 1 );
            }
            convertedKeymapPath = destDir.absoluteFilePath( convertedKeymapPath );
        }

        if ( !writeVConsoleData( vconsoleConfPath, convertedKeymapPath ) )
        {
            return Calamares::JobResult::error(
                tr( "Failed to write keyboard configuration for the virtual console.", "@error" ),
                tr( "Failed to write to %1", "@error, %1 is virtual console configuration path" )
                    .arg( vconsoleConfPath ) );
        }

        // Get the path to the destination's /etc/X11/xorg.conf.d/00-keyboard.conf
        QString xorgConfDPath;
        QString keyboardConfPath;
        if ( QDir::isAbsolutePath( m_xOrgConfFileName ) )
        {
            keyboardConfPath = m_xOrgConfFileName;
            while ( keyboardConfPath.startsWith( '/' ) )
            {
                keyboardConfPath.remove( 0, 1 );
            }
            keyboardConfPath = destDir.absoluteFilePath( keyboardConfPath );
            xorgConfDPath = QFileInfo( keyboardConfPath ).path();
        }
        else
        {
            xorgConfDPath = destDir.absoluteFilePath( "etc/X11/xorg.conf.d" );
            keyboardConfPath = QDir( xorgConfDPath ).absoluteFilePath( m_xOrgConfFileName );
        }
        destDir.mkpath( xorgConfDPath );

        if ( !writeX11Data( keyboardConfPath ) )
        {
            return Calamares::JobResult::error(
                tr( "Failed to write keyboard configuration for X11.", "@error" ),
                tr( "Failed to write to %1", "@error, %1 is keyboard configuration path" ).arg( keyboardConfPath ) );
        }
    }

    {
        QString defaultKeyboardPath;
        if ( QDir( destDir.absoluteFilePath( "etc/default" ) ).exists() )
        {
            defaultKeyboardPath = destDir.absoluteFilePath( "etc/default/keyboard" );
        }

        if ( !defaultKeyboardPath.isEmpty() && m_writeEtcDefaultKeyboard )
        {
            if ( !writeDefaultKeyboardData( defaultKeyboardPath ) )
            {
                return Calamares::JobResult::error(
                    tr( "Failed to write keyboard configuration to existing /etc/default directory.", "@error" ),
                    tr( "Failed to write to %1", "@error, %1 is default keyboard path" ).arg( defaultKeyboardPath ) );
            }
        }
    }

    return Calamares::JobResult::ok();
}
