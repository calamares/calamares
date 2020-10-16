/* === This file is part of Calamares - <https://github.com/calamares> ===
 * 
 *   SPDX-FileCopyrightText: 2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017-2018 Adriaan de Groot <groot@kde.org>
 * 
 *   Based on KPluginFactory from KCoreAddons, KDE project
 *   SPDX-FileCopyrightText: 2007 Matthias Kretz <kretz@kde.org>
 *   SPDX-FileCopyrightText: 2007 Bernhard Loos <nhuh.put@web.de>
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
 *
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *   License-Filename: LICENSE
 *
 */

#ifndef UTILS_PLUGINFACTORY_H
#define UTILS_PLUGINFACTORY_H

#include <KPluginFactory>

#define CalamaresPluginFactory_iid "io.calamares.PluginFactory"

/** @brief Plugin factory for Calamares
 *
 * Try to re-use KPluginFactory as much as possible (since the
 * old code for PluginFactory was a fork of an old version of
 * exactly that).
 *
 * The current createInstance() method passes more arguments
 * to the job and viewstep constructors than we want; chasing
 * that change means modifying each Calamares module. This class
 * implements a version of createInstance() with fewer arguments
 * and overloads registerPlugin() to use that.
 */
class CalamaresPluginFactory : public KPluginFactory
{
    Q_OBJECT
public:
    explicit CalamaresPluginFactory()
        : KPluginFactory()
    {
    }
    ~CalamaresPluginFactory() override;

    /** @brief Create an object from the factory.
     *
     * Ignores all the @p args since they are not used. Calls
     * Calamares constructors for the Jobs and ViewSteps.
     */
    template < class impl, class ParentType >
    static QObject* createInstance( QWidget* parentWidget, QObject* parent, const QVariantList& args )
    {
        Q_UNUSED( parentWidget )
        Q_UNUSED( args )
        ParentType* p = nullptr;
        if ( parent )
        {
            p = qobject_cast< ParentType* >( parent );
            Q_ASSERT( p );
        }
        return new impl( p );
    }

    /** @brief register a plugin
     *
     * The Calamares version doesn't accept keywords, and uses
     * the Calamares createInstance() version which ignores
     * the QVariantList of arguments.
     */
    template < class T >
    void registerPlugin()
    {
        KPluginFactory::registerPlugin< T >( QString(), &createInstance< T, QObject > );
    }
};

/** @brief declare a Calamares Plugin Factory
 *
 * This would be defined as K_PLUGIN_FACTORY_DECLARATION_WITH_BASEFACTORY,
 * except that does not actually use the base factory class that is
 * passed in.
 */
#define CALAMARES_PLUGIN_FACTORY_DECLARATION( name ) \
    class name : public CalamaresPluginFactory \
    { \
        Q_OBJECT \
        Q_INTERFACES( KPluginFactory ) \
        Q_PLUGIN_METADATA( IID CalamaresPluginFactory_iid ) \
    public: \
        explicit name(); \
        ~name(); \
    };
#define CALAMARES_PLUGIN_FACTORY_DEFINITION( name, pluginRegistrations ) \
    K_PLUGIN_FACTORY_DEFINITION_WITH_BASEFACTORY( name, CalamaresPluginFactory, pluginRegistrations )

#endif
