/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2012 Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   SPDX-FileCopyrightText: 2019, Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include "ImageRegistry.h"

#include <QHash>
#include <QIcon>
#include <QPainter>
#include <QSvgRenderer>

static QHash< QString, QHash< int, QHash< qint64, QPixmap > > > s_cache;


ImageRegistry*
ImageRegistry::instance()
{
    static ImageRegistry* s_instance = new ImageRegistry();
    return s_instance;
}


ImageRegistry::ImageRegistry() {}


QIcon
ImageRegistry::icon( const QString& image, CalamaresUtils::ImageMode mode )
{
    return pixmap( image, CalamaresUtils::defaultIconSize(), mode );
}


qint64
ImageRegistry::cacheKey( const QSize& size )
{
    return size.width() * 100 + size.height() * 10;
}


QPixmap
ImageRegistry::pixmap( const QString& image, const QSize& size, CalamaresUtils::ImageMode mode )
{
    Q_ASSERT( !( size.width() < 0 || size.height() < 0 ) );
    if ( size.width() < 0 || size.height() < 0 )
    {
        return QPixmap();
    }

    QHash< qint64, QPixmap > subsubcache;
    QHash< int, QHash< qint64, QPixmap > > subcache;

    if ( s_cache.contains( image ) )
    {
        subcache = s_cache.value( image );

        if ( subcache.contains( mode ) )
        {
            subsubcache = subcache.value( mode );

            const qint64 ck = cacheKey( size );
            if ( subsubcache.contains( ck ) )
            {
                return subsubcache.value( ck );
            }
        }
    }

    // Image not found in cache. Let's load it.
    QPixmap pixmap;
    if ( image.toLower().endsWith( ".svg" ) )
    {
        QSvgRenderer svgRenderer( image );
        QPixmap p( size.isNull() || size.height() == 0 || size.width() == 0 ? svgRenderer.defaultSize() : size );
        p.fill( Qt::transparent );

        QPainter pixPainter( &p );
        svgRenderer.render( &pixPainter );
        pixPainter.end();

        pixmap = p;
    }
    else
    {
        pixmap = QPixmap( image );
    }

    if ( !pixmap.isNull() )
    {
        if ( !size.isNull() && pixmap.size() != size )
        {
            if ( size.width() == 0 )
            {
                pixmap = pixmap.scaledToHeight( size.height(), Qt::SmoothTransformation );
            }
            else if ( size.height() == 0 )
            {
                pixmap = pixmap.scaledToWidth( size.width(), Qt::SmoothTransformation );
            }
            else
            {
                pixmap = pixmap.scaled( size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
            }
        }

        putInCache( image, size, mode, pixmap );
    }

    return pixmap;
}


void
ImageRegistry::putInCache( const QString& image,
                           const QSize& size,
                           CalamaresUtils::ImageMode mode,
                           const QPixmap& pixmap )
{
    QHash< qint64, QPixmap > subsubcache;
    QHash< int, QHash< qint64, QPixmap > > subcache;

    if ( s_cache.contains( image ) )
    {
        subcache = s_cache.value( image );
        if ( subcache.contains( mode ) )
        {
            subsubcache = subcache.value( mode );
        }
    }

    subsubcache.insert( cacheKey( size ), pixmap );
    subcache.insert( mode, subsubcache );
    s_cache.insert( image, subcache );
}
