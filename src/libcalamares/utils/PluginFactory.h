/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017-2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#ifndef UTILS_PLUGINFACTORY_H
#define UTILS_PLUGINFACTORY_H

#include <QObject>

#define CalamaresPluginFactory_iid "io.calamares.PluginFactory"

/** @brief Plugin factory for Calamares
 *
 * A Calamares plugin contains just one kind of plugin -- either
 * a job, or a viewstep -- so the factory is straightforward.
 * It gets a single CreateInstanceFunction and calls that;
 * the function is set when registerPlugin() is called in a subclass.
 *
 */
class CalamaresPluginFactory : public QObject
{
    Q_OBJECT
public:
    explicit CalamaresPluginFactory() {}
    ~CalamaresPluginFactory() override;

    typedef QObject* ( *CreateInstanceFunction )( QObject* );

    template < class T >
    T* create( QObject* parent = nullptr )
    {
        auto* op = fn ? fn( parent ) : nullptr;
        if ( !op )
        {
            return nullptr;
        }
        T* tp = qobject_cast< T* >( op );
        if ( !tp )
        {
            delete op;
        }
        return tp;
    }

protected:
    CreateInstanceFunction fn = nullptr;
};

/** @brief declare a Calamares Plugin Factory
 *
 * There should be one declaration -- generally alongside the
 * class definition for the Job or ViewStep that the plugin is
 * going to provide, in the header -- and one definition -- in
 * the corresponding implementation.
 */
#define CALAMARES_PLUGIN_FACTORY_DECLARATION( name ) \
    class name : public CalamaresPluginFactory \
    { \
        Q_OBJECT \
        Q_INTERFACES( CalamaresPluginFactory ) \
        Q_PLUGIN_METADATA( IID CalamaresPluginFactory_iid ) \
    public: \
        explicit name(); \
        ~name() override; \
        template < class T > \
        static QObject* createInstance( QObject* parent ) \
        { \
            return new T( parent ); \
        } \
        template < class T > \
        void registerPlugin() \
        { \
            fn = createInstance< T >; \
        } \
    };

/** @brief Define a Calamares Plugin Factory
 *
 * This should be done exactly once, generally in the translation
 * unit containing the definitions for the main class of the plugin,
 * either the Job or the ViewStep definitions.
 *
 * The @p name must match the name used in the declaration, while
 * @p pluginRegistrations should be a single call to `registerPlugin<T>()`
 * where `T` is the type (subclass of Job or ViewStep) defined by the
 * plugin, eg.
 *
 * ```
 * CALAMARES_PLUGIN_FACTORY_DEFINITION( MyPlugin, registerPlugin<MyPluginJob>() )
 * ```
 *
 * Leaving out the `()` will lead to generally-weird compiler warnings.
 */
#define CALAMARES_PLUGIN_FACTORY_DEFINITION( name, pluginRegistrations ) \
    name::name() \
        : CalamaresPluginFactory() \
    { \
        pluginRegistrations; \
    } \
    name::~name() {}

Q_DECLARE_INTERFACE( CalamaresPluginFactory, CalamaresPluginFactory_iid )

#endif
