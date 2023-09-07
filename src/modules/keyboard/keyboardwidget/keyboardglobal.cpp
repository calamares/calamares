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

#include <QByteArray>
#include <QFile>
#include <QRegularExpression>

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

        // Here we are in the model section, otherwise we would continue or break.
        // Sample model lines:
        //
        // ! model
        //   pc86            Generic 86-key PC
        //   pc101           Generic 101-key PC
        //
        QRegularExpression rx( "^\\s+(\\S+)\\s+(\\w.*)\n$" );
        QRegularExpressionMatch m;

        // insert into the model map
        if ( QString( line ).indexOf( rx, 0, &m ) != -1 )
        {
            const QString modelDescription = m.captured( 2 );
            const QString model = m.captured( 1 );
            models.insert( modelDescription, model );
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

        // Sample layout lines:
        //
        // ! layout
        //   us              English (US)
        //   af              Afghani
        QRegularExpression rx( "^\\s+(\\S+)\\s+(\\w.*)\n$" );
        QRegularExpressionMatch m;

        // insert into the layout map
        if ( QString( line ).indexOf( rx, 0, &m ) != -1 )
        {
            KeyboardGlobal::KeyboardInfo info;
            info.description = m.captured( 2 );
            info.variants.insert( QObject::tr( "Default" ), "" );
            layouts.insert( m.captured( 1 ), info );
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

        // Sample variant lines:
        //
        // ! variant
        //   chr             us: Cherokee
        //   haw             us: Hawaiian
        //   ps              af: Pashto
        //   uz              af: Uzbek (Afghanistan)
        QRegularExpression rx( "^\\s+(\\S+)\\s+(\\S+): (\\w.*)\n$" );
        QRegularExpressionMatch m;

        // insert into the variants multimap, if the pattern matches
        if ( QString( line ).indexOf( rx, 0, &m ) != -1 )
        {
            const QString variantKey = m.captured( 1 );
            const QString baseLayout = m.captured( 2 );
            const QString description = m.captured( 3 );
            if ( layouts.find( baseLayout ) != layouts.end() )
            {
                // in this case we found an entry in the multimap, and add the values to the multimap
                layouts.find( baseLayout ).value().variants.insert( description, variantKey );
            }
            else
            {
                // create a new map in the multimap - the value was not found.
                KeyboardGlobal::KeyboardInfo info;
                info.description = baseLayout;
                info.variants.insert( QObject::tr( "Default" ), "" );
                info.variants.insert( description, variantKey );
                layouts.insert( baseLayout, info );
            }
        }
    }

    return layouts;
}

static KeyboardGlobal::GroupsMap
parseKeyboardGroupsSwitchers( const char* filepath )
{
    KeyboardGlobal::GroupsMap models;

    QFile fh( filepath );
    fh.open( QIODevice::ReadOnly );

    if ( !fh.isOpen() )
    {
        cDebug() << "X11 Keyboard model definitions not found!";
        return models;
    }

    QRegularExpression rx;
    rx.setPattern( "^\\s+grp:(\\S+)\\s+(\\w.*)\n$" );

    bool optionSectionFound = findSection( fh, "! option" );
    // read the file until the end or until we break the loop
    while ( optionSectionFound && !fh.atEnd() )
    {
        QByteArray line = fh.readLine();

        // check if we start a new section
        if ( line.startsWith( '!' ) )
        {
            break;
        }

        // here we are in the option section - find all "grp:" options

        // insert into the model map
        QRegularExpressionMatch match = rx.match( line );
        if ( match.hasMatch() )
        {
            QString modelDesc = match.captured( 2 );
            QString model = match.captured( 1 );
            models.insert( modelDesc, model );
        }
    }

    return models;
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

KeyboardGlobal::GroupsMap
KeyboardGlobal::getKeyboardGroups()
{
    return parseKeyboardGroupsSwitchers( XKB_FILE );
}
