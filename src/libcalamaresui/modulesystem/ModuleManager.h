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

#ifndef MODULELOADER_H
#define MODULELOADER_H

#include "Typedefs.h"

#include <QObject>
#include <QStringList>
#include <QVariantMap>

namespace Calamares
{

class Module;

class ModuleManager : public QObject
{
    Q_OBJECT
public:
    explicit ModuleManager( const QStringList& paths, QObject* parent = nullptr );
    virtual ~ModuleManager();

    static ModuleManager* instance();

    /**
     * @brief init goes through the module search directories and gets a list of
     * modules available for loading, along with their metadata.
     * This information is stored as a map of Module* objects, indexed by name.
     */
    void init();

    QStringList loadedInstanceKeys();
    QVariantMap moduleDescriptor( const QString& name );

    Module* moduleInstance( const QString& instanceKey );

    void loadModules();

signals:
    void initDone();
    void modulesLoaded();

private slots:
    void doInit();

private:
    void checkDependencies();

    QMap< QString, QVariantMap > m_availableDescriptorsByModuleName;
    QMap< QString, QString > m_moduleDirectoriesByModuleName;
    QMap< QString, Module* > m_loadedModulesByInstanceKey;
    QStringList m_paths;

    static ModuleManager* s_instance;
};

}

#endif // MODULELOADER_H
