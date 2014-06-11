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

#ifndef GREETINGPAGEPLUGIN_H
#define GREETINGPAGEPLUGIN_H

#include <QObject>

#include "viewpages/PagePlugin.h"
#include "PluginDllMacro.h"

class PLUGINDLLEXPORT GreetingPagePlugin : public Calamares::PagePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA( IID "calamares.PagePlugin/1.0" )
                       //FILE "module.json" )
    Q_INTERFACES( Calamares::PagePlugin )
public:
    explicit GreetingPagePlugin(QObject *parent = 0);


};

#endif // GREETINGPAGEPLUGIN_H
