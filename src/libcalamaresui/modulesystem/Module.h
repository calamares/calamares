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

#include <Typedefs.h>

#include <QStringList>
#include <QVariant>


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
        Job,
        View
    };

    enum Interface
    {
        QtPlugin,
        Python,
        Process
    };
    virtual ~Module();

    static Module* fromDescriptorFile( const QString& path );

    virtual QString name() const;
    virtual QStringList requiredModules() const;
    virtual QString location() const;
    virtual Type type() const = 0;
    virtual Interface interface() const = 0;

    virtual bool isLoaded() const;

    virtual void loadSelf() = 0;

    virtual QList< job_ptr > jobs() const = 0;

protected:
    explicit Module();
    virtual void initFrom( const YAML::Node& node );
    bool m_loaded;
    QVariantMap m_configurationMap;

private:
    void loadConfigurationFile(); //throws YAML::Exception
    QString m_name;
    Type m_type;
    Interface m_interface;
    QStringList m_requiredModules;
    QString m_directory;

    friend void ::operator>>( const YAML::Node& node, Calamares::Module* m );
};

}

#endif // CALAMARES_MODULE_H
