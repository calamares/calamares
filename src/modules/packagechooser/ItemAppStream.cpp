/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019, Adriaan de Groot <groot@kde.org>
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

/** @brief Loading items from AppData XML files.
 *
 * Only used if QtXML is found, implements PackageItem::fromAppData().
 */
#include "PackageModel.h"

#include "utils/Logger.h"
#include "utils/Variant.h"

#include <AppStreamQt/pool.h>

static PackageItem
fromComponent( const AppStream::Component& component )
{
    cDebug() << "Loaded" << component.id();

    QVariantMap map;
    map.insert( "id", component.id() );
    map.insert( "name", component.name() );
    map.insert( "description", component.description() );
    // map.insert( "screenshot", component.screenshots() );
    return PackageItem( map );
}

PackageItem
PackageItem::fromAppStream( const QVariantMap& item_map )
{
    QString appstreamId = CalamaresUtils::getString( item_map, "appstream" );
    if ( appstreamId.isEmpty() )
    {
        cWarning() << "Can't load AppStream without a suitable appstreamId.";
        return PackageItem();
    }
    cDebug() << "Loading AppStream data for" << appstreamId;

    AppStream::Pool pool;
    if ( !pool.load() )
    {
        cWarning() << "AppStream load failed" << pool.lastError();
        return PackageItem();
    }

    auto itemList = pool.componentsById( appstreamId );
    if ( itemList.count() < 1 )
    {
        cWarning() << "No AppStream data for" << appstreamId;
        return PackageItem();
    }
    if ( itemList.count() > 1 )
    {
        cDebug() << "Multiple AppStream data for" << appstreamId << "using first.";
    }

    auto r = fromComponent( itemList.first() );
    if ( r.isValid() )
    {
        QString id = CalamaresUtils::getString( item_map, "id" );
        QString screenshotPath = CalamaresUtils::getString( item_map, "screenshot" );
        if ( !id.isEmpty() )
        {
            r.id = id;
        }
        if ( !screenshotPath.isEmpty() )
        {
            r.screenshot = screenshotPath;
        }
    }
    return r;
}
