/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   SPDX-License-Identifier: GPLv3+
 *   License-Filename: LICENSES/GPLv3+-ImageRegistry
 */

/*
 *   Copyright 2012, Christian Muehlhaeuser <muesli@tomahawk-player.org>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef IMAGE_REGISTRY_H
#define IMAGE_REGISTRY_H

#include <QPixmap>

#include "utils/CalamaresUtilsGui.h"
#include "UiDllMacro.h"

class UIDLLEXPORT ImageRegistry
{
public:
    static ImageRegistry* instance();

    explicit ImageRegistry();

    QIcon icon( const QString& image, CalamaresUtils::ImageMode mode = CalamaresUtils::Original );
    QPixmap pixmap( const QString& image, const QSize& size, CalamaresUtils::ImageMode mode = CalamaresUtils::Original, float opacity = 1.0, QColor tint = QColor( 0, 0, 0, 0 ) );

private:
    qint64 cacheKey( const QSize& size, float opacity, QColor tint );
    void putInCache( const QString& image, const QSize& size, CalamaresUtils::ImageMode mode, float opacity, const QPixmap& pixmap, QColor tint );

    static ImageRegistry* s_instance;
};

#endif // IMAGE_REGISTRY_H
