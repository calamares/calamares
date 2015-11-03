/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2013-2015, Teo Mrnjavac <teo@kde.org>
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

namespace CalamaresUtils
{
    DLLEXPORT QDir qmlModulesDir();
    DLLEXPORT QDir appDataDir();
    DLLEXPORT QDir appLogDir();
    DLLEXPORT QDir systemLibDir();
    DLLEXPORT void installTranslator( const QLocale& locale,
                                      const QString& brandingTranslationsPrefix,
                                      QObject* parent );

    /**
     * Override app data dir. Only for testing purposes.
     */
    DLLEXPORT void setAppDataDir( const QDir& dir );
    DLLEXPORT bool isAppDataDirOverridden();

    DLLEXPORT void setQmlModulesDir( const QDir& dir );

    DLLEXPORT QString removeDiacritics( const QString& string );

    DLLEXPORT QString obscure( const QString& string );

    DLLEXPORT void crash();
}

#endif // CALAMARESUTILS_H
