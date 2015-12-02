/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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

#ifndef CALAMARESUTILSGUI_H
#define CALAMARESUTILSGUI_H

#include "utils/CalamaresUtils.h"
#include "UiDllMacro.h"

#include <QPixmap>
#include <QSize>

class QLayout;

namespace CalamaresUtils
{
enum ImageType : int
{
    Yes,
    No,
    Information,
    Fail,
    Bugs,
    Help,
    Release,
    PartitionDisk,
    PartitionPartition,
    PartitionAlongside,
    PartitionEraseAuto,
    PartitionManual,
    PartitionReplaceOs,
    PartitionTable,
    BootEnvironment,
    Squid
};

enum ImageMode
{
    Original,
    CoverInCase,
    Grid,
    DropShadow,
    RoundedCorners
};

UIDLLEXPORT QPixmap defaultPixmap( ImageType type, ImageMode mode = CalamaresUtils::Original, const QSize& size = QSize( 0, 0 ) );
UIDLLEXPORT QPixmap createRoundedImage( const QPixmap& avatar, const QSize& size, float frameWidthPct = 0.20 );

UIDLLEXPORT void unmarginLayout( QLayout* layout );
UIDLLEXPORT void clearLayout( QLayout* layout );

UIDLLEXPORT void setDefaultFontSize( int points );
UIDLLEXPORT int defaultFontSize();
UIDLLEXPORT int defaultFontHeight();
UIDLLEXPORT QFont defaultFont();
UIDLLEXPORT QSize defaultIconSize();

}

#endif // CALAMARESUTILSGUI_H
