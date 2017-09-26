/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
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

#ifndef CALAMARESPLUGINFACTORY_H
#define CALAMARESPLUGINFACTORY_H

#include "DllMacro.h"

#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtCore/QStringList>

namespace Calamares
{
class PluginFactoryPrivate;
}

#define CalamaresPluginFactory_iid "io.calamares.PluginFactory"

#define CALAMARES_PLUGIN_FACTORY_DECLARATION_WITH_BASEFACTORY_SKEL(name, baseFactory, ...) \
    class name : public Calamares::PluginFactory \
    { \
        Q_OBJECT \
        Q_INTERFACES(Calamares::PluginFactory) \
        __VA_ARGS__ \
    public: \
        explicit name(); \
        ~name(); \
    private: \
        void init(); \
    };

#define CALAMARES_PLUGIN_FACTORY_DECLARATION_WITH_BASEFACTORY(name, baseFactory) \
    CALAMARES_PLUGIN_FACTORY_DECLARATION_WITH_BASEFACTORY_SKEL(name, baseFactory, Q_PLUGIN_METADATA(IID CalamaresPluginFactory_iid))

#define CALAMARES_PLUGIN_FACTORY_DEFINITION_WITH_BASEFACTORY(name, baseFactory, pluginRegistrations) \
    name::name() \
    { \
        pluginRegistrations \
    } \
    name::~name() {}

#define CALAMARES_PLUGIN_FACTORY_WITH_BASEFACTORY(name, baseFactory, pluginRegistrations) \
    CALAMARES_PLUGIN_FACTORY_DECLARATION_WITH_BASEFACTORY(name, baseFactory) \
    CALAMARES_PLUGIN_FACTORY_DEFINITION_WITH_BASEFACTORY(name, baseFactory, pluginRegistrations)

#define CALAMARES_PLUGIN_FACTORY_DECLARATION(name) CALAMARES_PLUGIN_FACTORY_DECLARATION_WITH_BASEFACTORY(name, Calamares::PluginFactory)
#define CALAMARES_PLUGIN_FACTORY_DEFINITION(name, pluginRegistrations) CALAMARES_PLUGIN_FACTORY_DEFINITION_WITH_BASEFACTORY(name, Calamares::PluginFactory, pluginRegistrations)

/**
 * \relates PluginFactory
 *
 * Create a PluginFactory subclass and export it as the root plugin object.
 *
 * \param name The name of the PluginFactory derived class.
 *
 * \param pluginRegistrations Code to be inserted into the constructor of the
 * class. Usually a series of registerPlugin() calls.
 *
 * Example:
 * \code
 * #include <PluginFactory.h>
 * #include <plugininterface.h>
 *
 * class MyPlugin : public PluginInterface
 * {
 * public:
 *     MyPlugin(QObject *parent, const QVariantList &args)
 *         : PluginInterface(parent)
 *     {}
 * };
 *
 * CALAMARES_PLUGIN_FACTORY(MyPluginFactory,
 *                  registerPlugin<MyPlugin>();
 *                 )
 *
 * #include <myplugin.moc>
 * \endcode
 *
 * \see CALAMARES_PLUGIN_FACTORY_DECLARATION
 * \see CALAMARES_PLUGIN_FACTORY_DEFINITION
 */
#define CALAMARES_PLUGIN_FACTORY(name, pluginRegistrations) CALAMARES_PLUGIN_FACTORY_WITH_BASEFACTORY(name, Calamares::PluginFactory, pluginRegistrations)

/**
 * \relates PluginFactory
 *
 * CALAMARES_PLUGIN_FACTORY_DECLARATION declares the PluginFactory subclass. This macro
 * can be used in a header file.
 *
 * \param name The name of the PluginFactory derived class.
 *
 * \see CALAMARES_PLUGIN_FACTORY
 * \see CALAMARES_PLUGIN_FACTORY_DEFINITION
 */
#define CALAMARES_PLUGIN_FACTORY_DECLARATION(name) CALAMARES_PLUGIN_FACTORY_DECLARATION_WITH_BASEFACTORY(name, Calamares::PluginFactory)

/**
 * \relates PluginFactory
 * CALAMARES_PLUGIN_FACTORY_DEFINITION defines the PluginFactory subclass. This macro
 * can <b>not</b> be used in a header file.
 *
 * \param name The name of the PluginFactory derived class.
 *
 * \param pluginRegistrations Code to be inserted into the constructor of the
 * class. Usually a series of registerPlugin() calls.
 *
 * \see CALAMARES_PLUGIN_FACTORY
 * \see CALAMARES_PLUGIN_FACTORY_DECLARATION
 */
#define CALAMARES_PLUGIN_FACTORY_DEFINITION(name, pluginRegistrations) CALAMARES_PLUGIN_FACTORY_DEFINITION_WITH_BASEFACTORY(name, Calamares::PluginFactory, pluginRegistrations)

namespace Calamares
{

/**
 * \class PluginFactory PluginFactory.h <PluginFactory.h>
 *
 * PluginFactory provides a convenient way to provide factory-style plugins.
 * Qt plugins provide a singleton object, but a common pattern is for plugins
 * to generate as many objects of a particular type as the application requires.
 * By using PluginFactory, you can avoid implementing the factory pattern
 * yourself.
 *
 * PluginFactory also allows plugins to provide multiple different object
 * types, indexed by keywords.
 *
 * The objects created by PluginFactory must inherit QObject, and must have a
 * standard constructor pattern:
 * \li if the object is a KPart::Part, it must be of the form
 * \code
 * T(QWidget *parentWidget, QObject *parent, const QVariantList &args)
 * \endcode
 * \li if it is a QWidget, it must be of the form
 * \code
 * T(QWidget *parent, const QVariantList &args)
 * \endcode
 * \li otherwise it must be of the form
 * \code
 * T(QObject *parent, const QVariantList &args)
 * \endcode
 *
 * You should typically use either CALAMARES_PLUGIN_FACTORY() or
 * CALAMARES_PLUGIN_FACTORY_WITH_JSON() in your plugin code to create the factory.  The
 * typical pattern is
 *
 * \code
 * #include <PluginFactory.h>
 * #include <plugininterface.h>
 *
 * class MyPlugin : public PluginInterface
 * {
 * public:
 *     MyPlugin(QObject *parent, const QVariantList &args)
 *         : PluginInterface(parent)
 *     {}
 * };
 *
 * CALAMARES_PLUGIN_FACTORY(MyPluginFactory,
 *                  registerPlugin<MyPlugin>();
 *                 )
 * #include <myplugin.moc>
 * \endcode
 *
 * If you want to load a library use KPluginLoader.
 * The application that wants to instantiate plugin classes can do the following:
 * \code
 * PluginFactory *factory = KPluginLoader("libraryname").factory();
 * if (factory) {
 *     PluginInterface *p1 = factory->create<PluginInterface>(parent);
 *     OtherInterface *p2  = factory->create<OtherInterface>(parent);
 *     NextInterface *p3   = factory->create<NextInterface>("keyword1", parent);
 *     NextInterface *p3   = factory->create<NextInterface>("keyword2", parent);
 * }
 * \endcode
 *
 * \author Matthias Kretz <kretz\@kde.org>
 * \author Bernhard Loos <nhuh.put\@web.de>
 */
class DLLEXPORT PluginFactory : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE( PluginFactory )
public:
    /**
     * This constructor creates a factory for a plugin.
     */
    explicit PluginFactory();

    /**
     * This destroys the PluginFactory.
     */
    virtual ~PluginFactory();

    /**
     * Use this method to create an object. It will try to create an object which inherits
     * \p T. If it has multiple choices, you will get a fatal error (kFatal()), so be careful
     * to request a unique interface or use keywords.
     *
     * \tparam T The interface for which an object should be created. The object will inherit \p T.
     * \param parent The parent of the object. If \p parent is a widget type, it will also passed
     *               to the parentWidget argument of the CreateInstanceFunction for the object.
     * \returns A pointer to the created object is returned, or 0 if an error occurred.
     */
    template<typename T>
    T* create( QObject* parent = nullptr );

    /**
     * Use this method to create an object. It will try to create an object which inherits
     * \p T and was registered with \p keyword.
     *
     * \tparam T The interface for which an object should be created. The object will inherit \p T.
     * \param keyword The keyword of the object.
     * \param parent The parent of the object. If \p parent is a widget type, it will also passed
     *               to the parentWidget argument of the CreateInstanceFunction for the object.
     * \returns A pointer to the created object is returned, or 0 if an error occurred.
     */
    template<typename T>
    T* create( const QString& keyword, QObject* parent = nullptr );

Q_SIGNALS:
    void objectCreated( QObject* object );

protected:
    /**
     * Function pointer type to a function that instantiates a plugin.
     */
    typedef QObject* ( *CreateInstanceFunction )( QWidget*, QObject* );

    /**
     * This is used to detect the arguments need for the constructor of plugin classes.
     * You can inherit it, if you want to add new classes and still keep support for the old ones.
     */
    template<class impl>
    struct InheritanceChecker
    {
        CreateInstanceFunction createInstanceFunction( QWidget* )
        {
            return &createInstance<impl, QWidget>;
        }
        CreateInstanceFunction createInstanceFunction( ... )
        {
            return &createInstance<impl, QObject>;
        }
    };

    explicit PluginFactory( PluginFactoryPrivate& dd );

    /**
     * Registers a plugin with the factory. Call this function from the constructor of the
     * PluginFactory subclass to make the create function able to instantiate the plugin when asked
     * for an interface the plugin implements.
     *
     * \tparam T the name of the plugin class
     *
     * \param keyword An optional keyword as unique identifier for the plugin. This allows you to
     * put more than one plugin with the same interface into the same library using the same
     * factory. X-KDE-PluginKeyword is a convenient way to specify the keyword in a desktop file.
     *
     * \param instanceFunction A function pointer to a function that creates an instance of the
     * plugin. The default function that will be used depends on the type of interface. If the
     * interface inherits from
     * \li \c KParts::Part the function will call
     * \code
     * new T(QWidget *parentWidget, QObject *parent)
     * \endcode
     * \li \c QWidget the function will call
     * \code
     * new T(QWidget *parent)
     * \endcode
     * \li else the function will call
     * \code
     * new T(QObject *parent)
     * \endcode
     */
    template<class T>
    void registerPlugin( const QString& keyword = QString(),
                         CreateInstanceFunction instanceFunction
                         = InheritanceChecker<T>().createInstanceFunction( reinterpret_cast<T*>( 0 ) ) )
    {
        doRegisterPlugin( keyword, &T::staticMetaObject, instanceFunction );
    }

    PluginFactoryPrivate* const d_ptr;

    /**
     * This function is called when the factory asked to create an Object.
     *
     * You may reimplement it to provide a very flexible factory. This is especially useful to
     * provide generic factories for plugins implemeted using a scripting language.
     *
     * \param iface The staticMetaObject::className() string identifying the plugin interface that
     * was requested. E.g. for KCModule plugins this string will be "KCModule".
     * \param parentWidget Only used if the requested plugin is a KPart.
     * \param parent The parent object for the plugin object.
     * \param keyword A string that uniquely identifies the plugin. If a KService is used this
     * keyword is read from the X-KDE-PluginKeyword entry in the .desktop file.
     */
    virtual QObject* create( const char* iface, QWidget* parentWidget, QObject* parent, const QString& keyword );

    template<class impl, class ParentType>
    static QObject* createInstance( QWidget* parentWidget, QObject* parent )
    {
        Q_UNUSED( parentWidget );
        ParentType* p = nullptr;
        if ( parent )
        {
            p = qobject_cast<ParentType*>( parent );
            Q_ASSERT( p );
        }
        return new impl( p );
    }

private:
    void doRegisterPlugin( const QString& keyword, const QMetaObject* metaObject, CreateInstanceFunction instanceFunction );
};

template<typename T>
inline T* PluginFactory::create( QObject* parent )
{
    QObject* o = create( T::staticMetaObject.className(),
                         parent && parent->isWidgetType() ? reinterpret_cast<QWidget*>( parent ) : nullptr,
                         parent,
                         QString() );

    T* t = qobject_cast<T*>( o );
    if ( !t )
        delete o;
    return t;
}

template<typename T>
inline T* PluginFactory::create( const QString& keyword, QObject* parent )
{
    QObject* o = create( T::staticMetaObject.className(),
                         parent && parent->isWidgetType() ? reinterpret_cast<QWidget*>( parent ) : nullptr,
                         parent,
                         keyword );

    T* t = qobject_cast<T*>( o );
    if ( !t )
        delete o;
    return t;
}

}

Q_DECLARE_INTERFACE( Calamares::PluginFactory, CalamaresPluginFactory_iid )

#endif // CALAMARESPLUGINFACTORY_H
