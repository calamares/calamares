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

#ifndef CALAMARES_MODULE_H
#define CALAMARES_MODULE_H

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

void operator>>( const YAML::Node& node, Calamares::Module* m );

namespace Calamares
{

class UIDLLEXPORT Module
{
public:
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
    virtual ~Module();

    static Module* fromConfigFile( const QString& path );

    virtual QString name();
    virtual QStringList requiredModules();
    virtual QString location();
    virtual Type type() = 0;
    virtual Interface interface() = 0;

    virtual bool isLoaded();

    virtual void loadSelf() = 0;

protected:
    explicit Module();
    virtual void initFrom( const YAML::Node& node );
    bool m_loaded;

private:
    QString m_name;
    Type m_type;
    Interface m_interface;
    QStringList m_requiredModules;
    QString m_directory;

    friend void ::operator>>( const YAML::Node& node, Calamares::Module* m );
};

}

#endif // CALAMARES_MODULE_H
