/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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

#ifndef SETTINGS_H
#define SETTINGS_H

#include "UiDllMacro.h"
#include "Typedefs.h"

#include <QObject>
#include <QStringList>


namespace Calamares
{

class UIDLLEXPORT Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings( bool debugMode, QObject *parent = nullptr );

    static Settings* instance();
    //TODO: load from JSON then emit ready

    QStringList modulesSearchPaths() const;

    QStringList modules( Phase phase ) const;

private:
    static Settings* s_instance;

    QStringList m_modulesSearchPaths;

    QStringList m_modulesPrepareList;
    QStringList m_modulesInstallList;
    QStringList m_modulesPostInstallList;
};

}

#endif // SETTINGS_H
