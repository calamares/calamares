/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

/** @brief Loading items from AppStream database.
 *
 * Only used if AppStreamQt is found, implements PackageItem::fromAppStream().
 */
#include "ItemAppStream.h"

#include "locale/TranslationsModel.h"
#include "utils/Logger.h"
#include "utils/Variant.h"

/// @brief Return number of pixels in a size, for < ordering purposes
static inline quint64
sizeOrder( const QSize& size )
{
    return static_cast< quint64 >( size.width() ) * static_cast< quint64 >( size.height() );
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
fromComponent( AppStream::Pool& pool, AppStream::Component& component )
{
#if HAVE_APPSTREAM_VERSION == 0
    auto setActiveLocale = [ &component ]( const QString& locale ) { component.setActiveLocale( locale ); };
#else
    auto setActiveLocale = [ &pool ]( const QString& locale ) { pool.setLocale( locale ); };
#endif

    QVariantMap map;
    map.insert( "id", component.id() );
    map.insert( "package", component.packageNames().join( "," ) );

    // Assume that the pool has loaded "ALL" locales, but it might be set
    // to any of them; get the en_US locale as "untranslated" and then
    // loop over Calamares locales (since there is no way to query for
    // available locales in the Component) to see if there's anything else.
    setActiveLocale( QStringLiteral( "en_US" ) );
    QString en_name = component.name();
    QString en_description = component.description();
    map.insert( "name", en_name );
    map.insert( "description", en_description );

    for ( const QString& locale : Calamares::Locale::availableTranslations()->localeIds() )
    {
        setActiveLocale( locale );
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

#if HAVE_APPSTREAM_VERSION == 0
    auto screenshots = component.screenshots();
#else
    auto screenshots = component.screenshotsAll();
#endif
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
    QString appstreamId = Calamares::getString( item_map, "appstream" );
    if ( appstreamId.isEmpty() )
    {
        cWarning() << "Can't load AppStream without a suitable appstreamId.";
        return PackageItem();
    }
    cDebug() << "Loading AppStream data for" << appstreamId;

#if HAVE_APPSTREAM_VERSION == 0
    auto itemList = pool.componentsById( appstreamId );
#else
    auto itemList = pool.componentsById( appstreamId ).toList();
#endif
    if ( itemList.count() < 1 )
    {
        cWarning() << "No AppStream data for" << appstreamId;
        return PackageItem();
    }
    if ( itemList.count() > 1 )
    {
        cDebug() << "Multiple AppStream data for" << appstreamId << "using first.";
    }

    auto r = fromComponent( pool, itemList.first() );
    if ( r.isValid() )
    {
        QString id = Calamares::getString( item_map, "id" );
        QString screenshotPath = Calamares::getString( item_map, "screenshot" );
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
