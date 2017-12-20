/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2015, Teo Mrnjavac <teo@kde.org>
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

#ifndef CALAMARESPLUGINFACTORY_P_H
#define CALAMARESPLUGINFACTORY_P_H

#include "PluginFactory.h"

#include <QtCore/QHash>

namespace Calamares
{

class PluginFactoryPrivate
{
    Q_DECLARE_PUBLIC(PluginFactory)
protected:
    typedef QPair<const QMetaObject *, PluginFactory::CreateInstanceFunction> Plugin;

    PluginFactoryPrivate()
        : catalogInitialized( false )
        , q_ptr( nullptr )
    {}
    ~PluginFactoryPrivate() {}

    QHash<QString, Plugin> createInstanceHash;
    QString catalogName;
    bool catalogInitialized;

    PluginFactory *q_ptr;
};

}

#endif // CALAMARESPLUGINFACTORY_P_H
