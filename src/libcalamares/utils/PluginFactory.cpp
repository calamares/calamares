/* === This file is part of Calamares - <https://github.com/calamares> ===
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

#include "PluginFactory.h"
#include "PluginFactory_p.h"

#include <QObjectCleanupHandler>
#include <QDebug>

Q_GLOBAL_STATIC( QObjectCleanupHandler, factorycleanup )

namespace Calamares
{

PluginFactory::PluginFactory()
    : pd_ptr( new PluginFactoryPrivate )
{
    pd_ptr->q_ptr = this;

    factorycleanup()->add( this );
}

PluginFactory::PluginFactory( PluginFactoryPrivate& d )
    : pd_ptr( &d )
{
    factorycleanup()->add( this );
}

PluginFactory::~PluginFactory()
{
    delete pd_ptr;
}

void PluginFactory::doRegisterPlugin( const QString& keyword, const QMetaObject* metaObject, CreateInstanceFunction instanceFunction )
{
    Q_ASSERT( metaObject );

    // we allow different interfaces to be registered without keyword
    if ( !keyword.isEmpty() )
    {
        if ( pd_ptr->createInstanceHash.contains( keyword ) )
            qWarning() << "A plugin with the keyword" << keyword << "was already registered. A keyword must be unique!";
        pd_ptr->createInstanceHash.insert( keyword, PluginFactoryPrivate::Plugin( metaObject, instanceFunction ) );
    }
    else
    {
        const QList<PluginFactoryPrivate::Plugin> clashes( pd_ptr->createInstanceHash.values( keyword ) );
        const QMetaObject* superClass = metaObject->superClass();
        if ( superClass )
        {
            for ( const PluginFactoryPrivate::Plugin& plugin : clashes )
            {
                for ( const QMetaObject* otherSuper = plugin.first->superClass(); otherSuper;
                        otherSuper = otherSuper->superClass() )
                {
                    if ( superClass == otherSuper )
                        qWarning() << "Two plugins with the same interface(" << superClass->className() << ") were registered. Use keywords to identify the plugins.";
                }
            }
        }
        for ( const PluginFactoryPrivate::Plugin& plugin : clashes )
        {
            superClass = plugin.first->superClass();
            if ( superClass )
            {
                for ( const QMetaObject* otherSuper = metaObject->superClass(); otherSuper;
                        otherSuper = otherSuper->superClass() )
                {
                    if ( superClass == otherSuper )
                        qWarning() << "Two plugins with the same interface(" << superClass->className() << ") were registered. Use keywords to identify the plugins.";
                }
            }
        }
        pd_ptr->createInstanceHash.insertMulti( keyword, PluginFactoryPrivate::Plugin( metaObject, instanceFunction ) );
    }
}

QObject* PluginFactory::create( const char* iface, QWidget* parentWidget, QObject* parent, const QString& keyword )
{
    QObject* obj = nullptr;

    const QList<PluginFactoryPrivate::Plugin> candidates( pd_ptr->createInstanceHash.values( keyword ) );
    // for !keyword.isEmpty() candidates.count() is 0 or 1

    for ( const PluginFactoryPrivate::Plugin& plugin : candidates )
    {
        for ( const QMetaObject* current = plugin.first; current; current = current->superClass() )
        {
            if ( 0 == qstrcmp( iface, current->className() ) )
            {
                if ( obj )
                    qWarning() << "ambiguous interface requested from a DSO containing more than one plugin";
                obj = plugin.second( parentWidget, parent );
                break;
            }
        }
    }

    if ( obj )
        emit objectCreated( obj );
    return obj;
}

}
