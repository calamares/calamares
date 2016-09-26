/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2016, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2014, Kevin Kofler <kevin.kofler@chello.at>
 *
 *   Portions from systemd (localed.c):
 *   Copyright 2011 Lennart Poettering
 *   Copyright 2013 Kay Sievers
 *   (originally under LGPLv2.1+, used under the LGPL to GPL conversion clause)
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

#include <SetKeyboardLayoutJob.h>

#include "JobQueue.h"
#include "GlobalStorage.h"
#include "utils/Logger.h"
#include "utils/CalamaresUtilsSystem.h"

#include <QDir>
#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <QSettings>


SetKeyboardLayoutJob::SetKeyboardLayoutJob( const QString& model,
                                            const QString& layout,
                                            const QString& variant,
                                            const QString& xOrgConfFileName,
                                            const QString& convertedKeymapPath,
                                            bool writeEtcDefaultKeyboard)
    : Calamares::Job()
    , m_model( model )
    , m_layout( layout )
    , m_variant( variant )
    , m_xOrgConfFileName( xOrgConfFileName )
    , m_convertedKeymapPath( convertedKeymapPath )
    , m_writeEtcDefaultKeyboard( writeEtcDefaultKeyboard )
{
}


QString
SetKeyboardLayoutJob::prettyName() const
{
    return tr( "Set keyboard model to %1, layout to %2-%3" ).arg( m_model )
                                                            .arg( m_layout )
                                                            .arg( m_variant );
}


QString
SetKeyboardLayoutJob::findConvertedKeymap( const QString& convertedKeymapPath ) const
{
    // No search path supplied, assume the distribution does not provide
    // converted keymaps
    if ( convertedKeymapPath.isEmpty() )
        return QString();

    QDir convertedKeymapDir( convertedKeymapPath );
    QString name = m_variant.isEmpty() ? m_layout : ( m_layout + '-' + m_variant );

    if ( convertedKeymapDir.exists( name + ".map" )
         || convertedKeymapDir.exists( name + ".map.gz" ) )
    {
        cDebug() << "Found converted keymap" << name;

        return name;
    }

    return QString();
}


QString
SetKeyboardLayoutJob::findLegacyKeymap() const
{
    int bestMatching = 0;
    QString name;

    QFile file( ":/kbd-model-map" );
    file.open( QIODevice::ReadOnly | QIODevice::Text );
    QTextStream stream( &file );
    while ( !stream.atEnd() )
    {
        QString line = stream.readLine().trimmed();
        if ( line.isEmpty() || line.startsWith( '#' ) )
            continue;

        QStringList mapping = line.split( '\t', QString::SkipEmptyParts );
        if ( mapping.size() < 5 )
            continue;

        int matching = 0;

        // Determine how well matching this entry is
        // We assume here that we have one X11 layout. If the UI changes to
        // allow more than one layout, this should change too.
        if ( m_layout == mapping[1] )
            // If we got an exact match, this is best
            matching = 10;
        // Look for an entry whose first layout matches ours
        else if ( mapping[1].startsWith( m_layout + ',' ) )
            matching = 5;

        if ( matching > 0 )
        {
            if ( m_model.isEmpty() || m_model == mapping[2] )
                matching++;

            QString mappingVariant = mapping[3];
            if ( mappingVariant == "-" )
                mappingVariant = QString();
            else if ( mappingVariant.startsWith( ',' ) )
                mappingVariant.remove( 1, 0 );

            if ( m_variant == mappingVariant )
                matching++;

            // We ignore mapping[4], the xkb options, for now. If we ever
            // allow setting options in the UI, we should match them here.
        }

        // The best matching entry so far, then let's save that
        if ( matching >= qMax( bestMatching, 1 ) )
        {
            cDebug() << "Found legacy keymap" << mapping[0]
                     << "with score" << matching;

            if ( matching > bestMatching )
            {
                bestMatching = matching;
                name = mapping[0];
            }
        }
    }

    return name;
}


bool
SetKeyboardLayoutJob::writeVConsoleData( const QString& vconsoleConfPath,
                                         const QString& convertedKeymapPath ) const
{
    QString keymap = findConvertedKeymap( convertedKeymapPath );
    if ( keymap.isEmpty() )
        keymap = findLegacyKeymap();
    if ( keymap.isEmpty() )
    {
        cDebug() << "Trying to use X11 layout" << m_layout
                 << "as the virtual console layout";
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
            existingLines << stream.readLine();
        file.close();
        if ( stream.status() != QTextStream::Ok )
            return false;
    }

    // Write out the existing lines and replace the KEYMAP= line
    file.open( QIODevice::WriteOnly | QIODevice::Text );
    QTextStream stream( &file );
    bool found = false;
    foreach ( const QString& existingLine, existingLines )
    {
        if ( existingLine.trimmed().startsWith( "KEYMAP=" ) )
        {
            stream << "KEYMAP=" << keymap << '\n';
            found = true;
        }
        else
            stream << existingLine << '\n';
    }
    // Add a KEYMAP= line if there wasn't any
    if ( !found )
        stream << "KEYMAP=" << keymap << '\n';
    stream.flush();
    file.close();

    cDebug() << "Written KEYMAP=" << keymap << "to vconsole.conf";

    return ( stream.status() == QTextStream::Ok );
}


bool
SetKeyboardLayoutJob::writeX11Data( const QString& keyboardConfPath ) const
{
    QFile file( keyboardConfPath );
    file.open( QIODevice::WriteOnly | QIODevice::Text );
    QTextStream stream( &file );

    stream << "# Read and parsed by systemd-localed. It's probably wise not to edit this file\n"
              "# manually too freely.\n"
              "Section \"InputClass\"\n"
              "        Identifier \"system-keyboard\"\n"
              "        MatchIsKeyboard \"on\"\n";

    if ( !m_layout.isEmpty() )
        stream << "        Option \"XkbLayout\" \"" << m_layout << "\"\n";

    if ( !m_model.isEmpty() )
        stream << "        Option \"XkbModel\" \"" << m_model << "\"\n";

    if ( !m_variant.isEmpty() )
        stream << "        Option \"XkbVariant\" \"" << m_variant << "\"\n";

    stream << "EndSection\n";
    stream.flush();

    file.close();

    cDebug() << "Written XkbLayout" << m_layout <<
                "; XkbModel" << m_model <<
                "; XkbVariant" << m_variant << "to X.org file" << keyboardConfPath;

    return ( stream.status() == QTextStream::Ok );
}


bool
SetKeyboardLayoutJob::writeDefaultKeyboardData( const QString& defaultKeyboardPath ) const
{
    QFile file( defaultKeyboardPath );
    file.open( QIODevice::WriteOnly | QIODevice::Text );
    QTextStream stream( &file );

    stream << "# KEYBOARD CONFIGURATION FILE\n\n"
              "# Consult the keyboard(5) manual page.\n\n";

    stream << "XKBMODEL=\"" << m_model << "\"\n";
    stream << "XKBLAYOUT=\"" << m_layout << "\"\n";
    stream << "XKBVARIANT=\"" << m_variant << "\"\n";
    stream << "XKBOPTIONS=\"\"\n\n";
    stream << "BACKSPACE=\"guess\"\n";
    stream.flush();

    file.close();

    cDebug() << "Written XKBMODEL" << m_model <<
                "; XKBLAYOUT" << m_layout <<
                "; XKBVARIANT" << m_variant <<
                "to /etc/default/keyboard file" << defaultKeyboardPath;

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

    // Get the path to the destination's /etc/vconsole.conf
    QString vconsoleConfPath = destDir.absoluteFilePath( "etc/vconsole.conf" );

    // Get the path to the destination's /etc/X11/xorg.conf.d/00-keyboard.conf
    QString xorgConfDPath;
    QString keyboardConfPath;
    if ( QDir::isAbsolutePath( m_xOrgConfFileName ) )
    {
        keyboardConfPath = m_xOrgConfFileName;
        while ( keyboardConfPath.startsWith( '/' ) )
            keyboardConfPath.remove( 0, 1 );
        keyboardConfPath = destDir.absoluteFilePath( keyboardConfPath );
        xorgConfDPath = QFileInfo( keyboardConfPath ).path();
    }
    else
    {
        xorgConfDPath = destDir.absoluteFilePath( "etc/X11/xorg.conf.d" );
        keyboardConfPath = QDir( xorgConfDPath )
                               .absoluteFilePath( m_xOrgConfFileName );
    }
    destDir.mkpath( xorgConfDPath );

    QString defaultKeyboardPath;
    if ( QDir( destDir.absoluteFilePath( "etc/default" ) ).exists() )
    {
        defaultKeyboardPath = destDir.absoluteFilePath( "etc/default/keyboard" );
    }

    // Get the path to the destination's path to the converted key mappings
    QString convertedKeymapPath = m_convertedKeymapPath;
    if ( !convertedKeymapPath.isEmpty() )
    {
        while ( convertedKeymapPath.startsWith( '/' ) )
            convertedKeymapPath.remove( 0, 1 );
        convertedKeymapPath = destDir.absoluteFilePath( convertedKeymapPath );
    }

    if ( !writeVConsoleData( vconsoleConfPath, convertedKeymapPath ) )
        return Calamares::JobResult::error( tr( "Failed to write keyboard configuration for the virtual console." ),
                                            tr( "Failed to write to %1" ).arg( vconsoleConfPath ) );

    if ( !writeX11Data( keyboardConfPath ) )
        return Calamares::JobResult::error( tr( "Failed to write keyboard configuration for X11." ),
                                            tr( "Failed to write to %1" ).arg( keyboardConfPath ) );

    if ( !defaultKeyboardPath.isEmpty() && m_writeEtcDefaultKeyboard )
    {
        if ( !writeDefaultKeyboardData( defaultKeyboardPath ) )
            return Calamares::JobResult::error( tr( "Failed to write keyboard configuration to existing /etc/default directory." ),
                                                tr( "Failed to write to %1" ).arg( keyboardConfPath ) );
    }

    return Calamares::JobResult::ok();
}
