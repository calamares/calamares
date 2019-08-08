/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017-2018, Adriaan de Groot <groot@kde.org>
 *
 *   Based on KPluginFactory from KCoreAddons, KDE project
 *   Copyright 2007, Matthias Kretz <kretz@kde.org>
 *   Copyright 2007, Bernhard Loos <nhuh.put@web.de>
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

#ifndef UTILS_PLUGINFACTORY_H
#define UTILS_PLUGINFACTORY_H

#include <KF5/KCoreAddons/KPluginFactory>

#define CalamaresPluginFactory_iid "io.calamares.PluginFactory"

#define CALAMARES_PLUGIN_FACTORY_DECLARATION(name) \
    K_PLUGIN_FACTORY_DECLARATION_WITH_BASEFACTORY_SKEL(name,KPluginFactory,Q_PLUGIN_METADATA(IID CalamaresPluginFactory_iid))
#define CALAMARES_PLUGIN_FACTORY_DEFINITION(name, pluginRegistrations) \
    K_PLUGIN_FACTORY_DEFINITION(name, pluginRegistrations )

// Q_DECLARE_INTERFACE( Calamares::PluginFactory, CalamaresPluginFactory_iid )

#endif
