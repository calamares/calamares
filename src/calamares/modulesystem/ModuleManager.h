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

#ifndef MODULELOADER_H
#define MODULELOADER_H

#include "Module.h"

#include <QMap>
#include <QObject>
#include <QStringList>

namespace Calamares
{

class Module;

class ModuleManager : public QObject
{
    Q_OBJECT
public:
    explicit ModuleManager( const QStringList& paths, QObject* parent = nullptr );
    virtual ~ModuleManager();

    void init();

    QStringList availableModules();
    Module* module( const QString& name );

    void loadRequiredModules();

signals:
    void initDone();
    void modulesLoaded();

private slots:
    void doInit();
    void doLoadModules();

private:
    void recursiveLoad( const QString& moduleName );
    void checkDependencies();

    QMap< QString, Module* > m_availableModules;

    QStringList m_paths;

};

}

#endif // MODULELOADER_H
