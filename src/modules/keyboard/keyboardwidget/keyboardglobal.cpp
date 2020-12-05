/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2007 Free Software Foundation, Inc.
 *   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Originally from the Manjaro Installation Framework
 *   by Roland Singer <roland@manjaro.org>
 *   Copyright (C) 2007 Free Software Foundation, Inc.
 *
 *   Source by Georg Grabler <ggrabler@gmail.com>
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "keyboardglobal.h"

#include "utils/Logger.h"

#ifdef Q_OS_FREEBSD
static const char XKB_FILE[] = "/usr/local/share/X11/xkb/rules/base.lst";
#else
static const char XKB_FILE[] = "/usr/share/X11/xkb/rules/base.lst";
#endif

// The xkb rules file is made of several "sections". Each section
// starts with a line "! <sectionname>". The static methods here
// handle individual sections.

/** @brief Scans a file for a named section
 *
 * Reads from @p fh incrementally until it finds a section named @p name
 * or hits end-of-file. Returns true if the section is found. The
 * @p name must include the "! " section marker as well.
 */
static bool
findSection( QFile& fh, const char* name )
{
    while ( !fh.atEnd() )
    {
        QByteArray line = fh.readLine();
        if ( line.startsWith( name ) )
        {
            return true;
        }
    }
    return false;
}

static KeyboardGlobal::ModelsMap
parseKeyboardModels( const char* filepath )
{
    KeyboardGlobal::ModelsMap models;

    QFile fh( filepath );
    fh.open( QIODevice::ReadOnly );

    if ( !fh.isOpen() )
    {
        cDebug() << "X11 Keyboard model definitions not found!";
        return models;
    }

    bool modelsFound = findSection( fh, "! model" );
    // read the file until the end or until we break the loop
    while ( modelsFound && !fh.atEnd() )
    {
        QByteArray line = fh.readLine();

        // check if we start a new section
        if ( line.startsWith( '!' ) )
        {
            break;
        }

        // here we are in the model section, otherwise we would continue or break
        QRegExp rx;
        rx.setPattern( "^\\s+(\\S+)\\s+(\\w.*)\n$" );

        // insert into the model map
        if ( rx.indexIn( line ) != -1 )
        {
            QString modelDesc = rx.cap( 2 );
            QString model = rx.cap( 1 );
            models.insert( modelDesc, model );
        }
    }

    return models;
}


KeyboardGlobal::LayoutsMap
parseKeyboardLayouts( const char* filepath )
{
    KeyboardGlobal::LayoutsMap layouts;

    //### Get Layouts ###//

    QFile fh( filepath );
    fh.open( QIODevice::ReadOnly );

    if ( !fh.isOpen() )
    {
        cDebug() << "X11 Keyboard layout definitions not found!";
        return layouts;
    }

    bool layoutsFound = findSection( fh, "! layout" );
    // read the file until the end or we break the loop
    while ( layoutsFound && !fh.atEnd() )
    {
        QByteArray line = fh.readLine();

        if ( line.startsWith( '!' ) )
        {
            break;
        }

        QRegExp rx;
        rx.setPattern( "^\\s+(\\S+)\\s+(\\w.*)\n$" );

        // insert into the layout map
        if ( rx.indexIn( line ) != -1 )
        {
            KeyboardGlobal::KeyboardInfo info;
            info.description = rx.cap( 2 );
            info.variants.insert( QObject::tr( "Default" ), "" );
            layouts.insert( rx.cap( 1 ), info );
        }
    }

    fh.reset();


    //### Get Variants ###//

    bool variantsFound = findSection( fh, "! variant" );
    // read the file until the end or until we break
    while ( variantsFound && !fh.atEnd() )
    {
        QByteArray line = fh.readLine();

        if ( line.startsWith( '!' ) )
        {
            break;
        }

        QRegExp rx;
        rx.setPattern( "^\\s+(\\S+)\\s+(\\S+): (\\w.*)\n$" );

        // insert into the variants multimap, if the pattern matches
        if ( rx.indexIn( line ) != -1 )
        {
            if ( layouts.find( rx.cap( 2 ) ) != layouts.end() )
            {
                // in this case we found an entry in the multimap, and add the values to the multimap
                layouts.find( rx.cap( 2 ) ).value().variants.insert( rx.cap( 3 ), rx.cap( 1 ) );
            }
            else
            {
                // create a new map in the multimap - the value was not found.
                KeyboardGlobal::KeyboardInfo info;
                info.description = rx.cap( 2 );
                info.variants.insert( QObject::tr( "Default" ), "" );
                info.variants.insert( rx.cap( 3 ), rx.cap( 1 ) );
                layouts.insert( rx.cap( 2 ), info );
            }
        }
    }

    return layouts;
}


KeyboardGlobal::LayoutsMap
KeyboardGlobal::getKeyboardLayouts()
{
    return parseKeyboardLayouts( XKB_FILE );
}


KeyboardGlobal::ModelsMap
KeyboardGlobal::getKeyboardModels()
{
    return parseKeyboardModels( XKB_FILE );
}
