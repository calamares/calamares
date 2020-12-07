/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2012 Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifndef IMAGE_REGISTRY_H
#define IMAGE_REGISTRY_H

#include <QPixmap>

#include "DllMacro.h"
#include "utils/CalamaresUtilsGui.h"

class UIDLLEXPORT ImageRegistry
{
public:
    static ImageRegistry* instance();

    explicit ImageRegistry();

    QIcon icon( const QString& image, CalamaresUtils::ImageMode mode = CalamaresUtils::Original );
    QPixmap
    pixmap( const QString& image, const QSize& size, CalamaresUtils::ImageMode mode = CalamaresUtils::Original );

private:
    qint64 cacheKey( const QSize& size );
    void putInCache( const QString& image, const QSize& size, CalamaresUtils::ImageMode mode, const QPixmap& pixmap );
};

#endif  // IMAGE_REGISTRY_H
