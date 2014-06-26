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

#ifndef CALAMARESMODULE_H
#define CALAMARESMODULE_H

#include "UiDllMacro.h"

#include <QStringList>


namespace YAML
{
class Node;
}

namespace Calamares
{
class Module;
}

void operator>>( const YAML::Node& node, Calamares::Module& m );

namespace Calamares
{

class UIDLLEXPORT Module
{
public:
    static Module* fromConfigFile( const QString& path );

    QString name();
    QStringList requiredModules();

    enum Type
    {
        Core,
        View
    };

    enum Interface
    {
        QtPlugin,
        Python,
        Process
    };
private:
    QString m_name;
    Type m_type;
    Interface m_interface;
    QStringList m_requiredModules;

    friend void ::operator>>( const YAML::Node& node, Calamares::Module& m );
};

}

#endif // CALAMARESMODULE_H
