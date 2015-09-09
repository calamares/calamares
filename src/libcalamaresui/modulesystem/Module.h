/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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


namespace Calamares
{
class Module;
}

void operator>>( const QVariantMap& moduleDescriptor, Calamares::Module* m );

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

    static Module* fromDescriptor( const QVariantMap& moduleDescriptor,
                                   const QString& instanceId,
                                   const QString& configFileName,
                                   const QString& moduleDirectory );

    virtual QString name() const final;
    virtual QString instanceId() const final;
    virtual QString instanceKey() const final;
    virtual QStringList requiredModules() const;
    virtual QString location() const final;
    virtual Type type() const = 0;
    virtual Interface interface() const = 0;

    virtual bool isLoaded() const;

    virtual void loadSelf() = 0;

    virtual QList< job_ptr > jobs() const = 0;

    QVariantMap configurationMap();

protected:
    explicit Module();
    virtual void initFrom( const QVariantMap& moduleDescriptor );
    bool m_loaded;
    QVariantMap m_configurationMap;

private:
    void loadConfigurationFile( const QString& configFileName ); //throws YAML::Exception
    QString m_name;
    QStringList m_requiredModules;
    QString m_directory;
    QString m_instanceId;

    friend void ::operator>>( const QVariantMap& moduleDescriptor,
                              Calamares::Module* m );
};

}

#endif // CALAMARES_MODULE_H
