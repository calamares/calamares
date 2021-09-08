/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

/** @brief Loading items from AppData XML files.
 *
 * Only used if QtXML is found, implements PackageItem::fromAppData().
 */
#include "PackageModel.h"

#include "locale/TranslationsModel.h"
#include "utils/Logger.h"
#include "utils/Variant.h"

#include <AppStreamQt/image.h>
#include <AppStreamQt/pool.h>
#include <AppStreamQt/screenshot.h>

/// @brief Return number of pixels in a size, for < ordering purposes
static inline quint64
sizeOrder( const QSize& size )
{
    return size.width() * size.height();
}

/// @brief Sets a screenshot in @p map from @p screenshot, if a usable one is found
static void
setScreenshot( QVariantMap& map, const AppStream::Screenshot& screenshot )
{
    if ( screenshot.images().count() < 1 )
    {
        return;
    }

    // Pick the smallest
    QUrl url;
    quint64 size = sizeOrder( screenshot.images().first().size() );
    for ( const auto& img : screenshot.images() )
    {
        if ( sizeOrder( img.size() ) <= size )
        {
            url = img.url();
        }
    }

    if ( url.isValid() )
    {
        map.insert( "screenshot", url.toString() );
    }
}

/// @brief Interpret an AppStream Component
static PackageItem
fromComponent( AppStream::Component& component )
{
    QVariantMap map;
    map.insert( "id", component.id() );
    map.insert( "package", component.packageNames().join( "," ) );

    // Assume that the pool has loaded "ALL" locales, but it might be set
    // to any of them; get the en_US locale as "untranslated" and then
    // loop over Calamares locales (since there is no way to query for
    // available locales in the Component) to see if there's anything else.
    component.setActiveLocale( QStringLiteral( "en_US" ) );
    QString en_name = component.name();
    QString en_description = component.description();
    map.insert( "name", en_name );
    map.insert( "description", en_description );

    for ( const QString& locale : CalamaresUtils::Locale::availableTranslations()->localeIds() )
    {
        component.setActiveLocale( locale );
        QString name = component.name();
        if ( name != en_name )
        {
            map.insert( QStringLiteral( "name[%1]" ).arg( locale ), name );
        }
        QString description = component.description();
        if ( description != en_description )
        {
            map.insert( QStringLiteral( "description[%1]" ).arg( locale ), description );
        }
    }

    auto screenshots = component.screenshots();
    if ( screenshots.count() > 0 )
    {
        bool done = false;
        for ( const auto& s : screenshots )
        {
            if ( s.isDefault() )
            {
                setScreenshot( map, s );
                done = true;
                break;
            }
        }
        if ( !done )
        {
            setScreenshot( map, screenshots.first() );
        }
    }

    return PackageItem( map );
}

PackageItem
fromAppStream( AppStream::Pool& pool, const QVariantMap& item_map )
{
    QString appstreamId = CalamaresUtils::getString( item_map, "appstream" );
    if ( appstreamId.isEmpty() )
    {
        cWarning() << "Can't load AppStream without a suitable appstreamId.";
        return PackageItem();
    }
    cDebug() << "Loading AppStream data for" << appstreamId;

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
