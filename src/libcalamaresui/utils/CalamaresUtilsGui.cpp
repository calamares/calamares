/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
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

#include "CalamaresUtilsGui.h"

#include "ImageRegistry.h"

#include <QBrush>
#include <QFont>
#include <QFontMetrics>
#include <QLayout>
#include <QPainter>
#include <QPen>
#include <QWidget>

namespace CalamaresUtils
{

static int s_defaultFontSize   = 0;
static int s_defaultFontHeight = 0;



QPixmap
defaultPixmap( ImageType type, ImageMode mode, const QSize& size )
{
    Q_UNUSED( mode );
    QPixmap pixmap;

    switch ( type )
    {
    case Yes:
        pixmap = ImageRegistry::instance()->pixmap( RESPATH "images/yes.svgz", size );
        break;

    case No:
        pixmap = ImageRegistry::instance()->pixmap( RESPATH "images/no.svgz", size );
        break;

    case Information:
        pixmap = ImageRegistry::instance()->pixmap( RESPATH "images/information.svgz", size );
        break;

    case Fail:
        pixmap = ImageRegistry::instance()->pixmap( RESPATH "images/fail.svgz", size );
        break;

    case Bugs:
        pixmap = ImageRegistry::instance()->pixmap( RESPATH "images/bugs.svg", size );
        break;

    case Help:
        pixmap = ImageRegistry::instance()->pixmap( RESPATH "images/help.svg", size );
        break;

    case Release:
        pixmap = ImageRegistry::instance()->pixmap( RESPATH "images/release.svg", size );
        break;

    case PartitionDisk:
        pixmap = ImageRegistry::instance()->pixmap( RESPATH "images/partition-disk.svg", size );
        break;

    case PartitionPartition:
        pixmap = ImageRegistry::instance()->pixmap( RESPATH "images/partition-partition.svg", size );
        break;

    case PartitionAlongside:
        pixmap = ImageRegistry::instance()->pixmap( RESPATH "images/partition-alongside.svg", size );
        break;

    case PartitionEraseAuto:
        pixmap = ImageRegistry::instance()->pixmap( RESPATH "images/partition-erase-auto.svg", size );
        break;

    case PartitionManual:
        pixmap = ImageRegistry::instance()->pixmap( RESPATH "images/partition-manual.svg", size );
        break;

    case PartitionReplaceOs:
        pixmap = ImageRegistry::instance()->pixmap( RESPATH "images/partition-replace-os.svg", size );
        break;

    case PartitionTable:
        pixmap = ImageRegistry::instance()->pixmap( RESPATH "images/partition-table.svg", size );
        break;

    case BootEnvironment:
        pixmap = ImageRegistry::instance()->pixmap( RESPATH "images/boot-environment.svg", size );
        break;

    case Squid:
        pixmap = ImageRegistry::instance()->pixmap( RESPATH "images/squid.svg", size );
        break;

    case StatusOk:
        pixmap = ImageRegistry::instance()->pixmap( RESPATH "images/state-ok.svg", size );
        break;

    case StatusWarning:
        pixmap = ImageRegistry::instance()->pixmap( RESPATH "images/state-warning.svg", size );
        break;

    case StatusError:
        pixmap = ImageRegistry::instance()->pixmap( RESPATH "images/state-error.svg", size );
        break;
    }

    if ( pixmap.isNull() )
    {
        Q_ASSERT( false );
        return QPixmap();
    }

    return pixmap;
}


QPixmap
createRoundedImage( const QPixmap& pixmap, const QSize& size, float frameWidthPct )
{
    int height;
    int width;

    if ( !size.isEmpty() )
    {
        height = size.height();
        width = size.width();
    }
    else
    {
        height = pixmap.height();
        width = pixmap.width();
    }

    if ( !height || !width )
        return QPixmap();

    QPixmap scaledAvatar = pixmap.scaled( width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
    if ( frameWidthPct == 0.00f )
        return scaledAvatar;

    QPixmap frame( width, height );
    frame.fill( Qt::transparent );

    QPainter painter( &frame );
    painter.setRenderHint( QPainter::Antialiasing );

    QRect outerRect( 0, 0, width, height );
    QBrush brush( scaledAvatar );
    QPen pen;
    pen.setColor( Qt::transparent );
    pen.setJoinStyle( Qt::RoundJoin );

    painter.setBrush( brush );
    painter.setPen( pen );
    painter.drawRoundedRect( outerRect, qreal(frameWidthPct) * 100.0, qreal(frameWidthPct) * 100.0, Qt::RelativeSize );

/*    painter.setBrush( Qt::transparent );
    painter.setPen( Qt::white );
    painter.drawRoundedRect( outerRect, frameWidthPct, frameWidthPct, Qt::RelativeSize ); */

    return frame;
}


void
unmarginLayout( QLayout* layout )
{
    layout->setContentsMargins( 0, 0, 0, 0 );
    layout->setMargin( 0 );
    layout->setSpacing( 0 );

    for ( int i = 0; i < layout->count(); i++ )
    {
        QLayout* childLayout = layout->itemAt( i )->layout();
        if ( childLayout )
            unmarginLayout( childLayout );
    }
}


int
defaultFontSize()
{
    return s_defaultFontSize;
}


int
defaultFontHeight()
{
    if ( s_defaultFontHeight <= 0 )
    {
        QFont f;
        f.setPointSize( defaultFontSize() );
        s_defaultFontHeight = QFontMetrics( f ).height();
    }

    return s_defaultFontHeight;
}


QFont
defaultFont()
{
    QFont f;
    f.setPointSize( defaultFontSize() );
    return f;
}


void
setDefaultFontSize( int points )
{
    s_defaultFontSize = points;
}


QSize
defaultIconSize()
{
    const int w = int(defaultFontHeight() * 1.6);
    return QSize( w, w );
}


void
clearLayout( QLayout* layout )
{
    while ( QLayoutItem* item = layout->takeAt( 0 ) )
    {
        if ( QWidget* widget = item->widget() )
            widget->deleteLater();

        if ( QLayout* childLayout = item->layout() )
            clearLayout( childLayout );

        delete item;
    }
}


}
