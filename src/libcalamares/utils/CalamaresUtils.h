/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2013-2016, Teo Mrnjavac <teo@kde.org>
 *
 *   Originally from Tomahawk, portions:
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2010-2011, Leo Franchi <lfranchi@kde.org>
 *   Copyright 2010-2012, Jeff Mitchell <jeff@tomahawk-player.org>
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

#ifndef CALAMARESUTILS_H
#define CALAMARESUTILS_H

#include "DllMacro.h"

#include <QLocale>

#define RESPATH ":/data/"

class QDir;
class QObject;

/**
 * @brief The CalamaresUtils namespace contains utility functions.
 */
namespace CalamaresUtils
{
    DLLEXPORT QDir qmlModulesDir();

    /**
     * @brief appDataDir returns the directory with common application data.
     * Defaults to CMAKE_INSTALL_FULL_DATADIR (usually /usr/share/calamares).
     */
    DLLEXPORT QDir appDataDir();

    /**
     * @brief appLogDir returns the directory for Calamares logs.
     * Defaults to QStandardPaths::CacheLocation (usually ~/.cache/Calamares).
     */
    DLLEXPORT QDir appLogDir();

    /**
     * @brief systemLibDir returns the system's lib directory.
     * Defaults to CMAKE_INSTALL_FULL_LIBDIR (usually /usr/lib64 or /usr/lib).
     */
    DLLEXPORT QDir systemLibDir();

    /**
     * @brief installTranslator changes the application language.
     * @param locale the new locale.
     * @param brandingTranslationsPrefix the branding path prefix, from Calamares::Branding.
     * @param parent the parent QObject.
     */
    DLLEXPORT void installTranslator( const QLocale& locale,
                                      const QString& brandingTranslationsPrefix,
                                      QObject* parent );

    DLLEXPORT QString translatorLocaleName();

    /**
     * Override app data dir. Only for testing purposes.
     */
    DLLEXPORT void setAppDataDir( const QDir& dir );
    DLLEXPORT bool isAppDataDirOverridden();

    DLLEXPORT void setQmlModulesDir( const QDir& dir );

    /**
     * @brief removeDiacritics replaces letters with diacritics and ligatures with
     * alternative forms and digraphs.
     * @param string the string to transform.
     * @return the output string with plain characters.
     */
    DLLEXPORT QString removeDiacritics( const QString& string );

    /**
     * @brief obscure is a bidirectional obfuscation function, from KStringHandler.
     * @param string the input string.
     * @return the obfuscated string.
     */
    DLLEXPORT QString obscure( const QString& string );

    /**
     * @brief crash makes Calamares crash immediately.
     */
    DLLEXPORT void crash();
}

#endif // CALAMARESUTILS_H
