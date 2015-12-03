/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
 *   Copyright 2015, Teo Mrnjavac <teo@kde.org>
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
#include "gui/PartitionBarsView.h"

#include <core/PartitionModel.h>
#include <core/ColorUtils.h>

#include <kpmcore/core/device.h>

#include "utils/CalamaresUtilsGui.h"


// Qt
#include <QDebug>
#include <QPainter>


static const int VIEW_HEIGHT = CalamaresUtils::defaultFontHeight() + 8;
static const int CORNER_RADIUS = 3;
static const int EXTENDED_PARTITION_MARGIN = 4;


PartitionBarsView::PartitionBarsView( QWidget* parent )
    : QAbstractItemView( parent )
{
    setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Fixed );
    setFrameStyle( QFrame::NoFrame );
}


PartitionBarsView::~PartitionBarsView()
{
}


QSize
PartitionBarsView::minimumSizeHint() const
{
    return sizeHint();
}


QSize
PartitionBarsView::sizeHint() const
{
    return QSize( -1, VIEW_HEIGHT );
}


void
PartitionBarsView::paintEvent( QPaintEvent* event )
{
    QPainter painter( viewport() );
    painter.fillRect( rect(), palette().window() );
    painter.setRenderHint( QPainter::Antialiasing );

    QRect partitionsRect = rect();
    partitionsRect.setHeight( VIEW_HEIGHT );

    painter.save();
    drawPartitions( &painter, partitionsRect, QModelIndex() );
    painter.restore();
}


static void
drawSection( QPainter* painter, const QRect& rect_, int x, int width, const QModelIndex& index )
{
    QColor color = index.isValid() ?
                   index.data( Qt::DecorationRole ).value< QColor >() :
                   ColorUtils::unknownDisklabelColor();
    bool isFreeSpace = index.isValid() ?
                       index.data( PartitionModel::IsFreeSpaceRole ).toBool() :
                       true;

    QRect rect = rect_;
    const int y = rect.y();
    const int height = rect.height();
    const int radius = qMax( 1, CORNER_RADIUS - ( VIEW_HEIGHT - height ) / 2 );
    painter->setClipRect( x, y, width, height );
    painter->translate( 0.5, 0.5 );

    rect.adjust( 0, 0, -1, -1 );
    const QColor borderColor = color.darker();
    painter->setPen( borderColor );
    painter->setBrush( color );
    painter->drawRoundedRect( rect, radius, radius );

    // Draw shade
    if ( !isFreeSpace )
        rect.adjust( 2, 2, -2, -2 );

    QLinearGradient gradient( 0, 0, 0, height / 2 );

    qreal c = isFreeSpace ? 0 : 1;
    gradient.setColorAt( 0, QColor::fromRgbF( c, c, c, 0.3 ) );
    gradient.setColorAt( 1, QColor::fromRgbF( c, c, c, 0 ) );

    painter->setPen( Qt::NoPen );
    painter->setBrush( gradient );
    painter->drawRoundedRect( rect, radius, radius );

    painter->translate( -0.5, -0.5 );
}


void
PartitionBarsView::drawPartitions( QPainter* painter, const QRect& rect, const QModelIndex& parent )
{
    PartitionModel* modl = qobject_cast< PartitionModel* >( model() );
    if ( !modl )
        return;
    const int count = modl->rowCount( parent );
    const int totalWidth = rect.width();
    qDebug() << "count:" << count << "totalWidth:" << totalWidth;
    struct Item
    {
        qreal size;
        QModelIndex index;
    };
    QVector< Item > items( count );
    qreal total = 0;
    for ( int row = 0; row < count; ++row )
    {
        QModelIndex index = modl->index( row, 0, parent );
        qreal size = index.data( PartitionModel::SizeRole ).toLongLong();
        total += size;
        items[ row ] = { size, index };
    }

    int x = rect.x();
    for ( int row = 0; row < count; ++row )
    {
        const auto& item = items[ row ];
        int width;
        if ( row < count - 1 )
            width = totalWidth * ( item.size / total );
        else
            // Make sure we fill the last pixel column
            width = rect.right() - x + 1;

        drawSection( painter, rect, x, width, item.index );
        if ( modl->hasChildren( item.index ) )
        {
            QRect subRect(
                x + EXTENDED_PARTITION_MARGIN,
                rect.y() + EXTENDED_PARTITION_MARGIN,
                width - 2 * EXTENDED_PARTITION_MARGIN,
                rect.height() - 2 * EXTENDED_PARTITION_MARGIN
            );
            drawPartitions( painter, subRect, item.index );
        }
        x += width;
    }

    if ( !count &&
         !modl->device()->partitionTable() ) // No disklabel or unknown
    {
        int width = rect.right() - rect.x() + 1;
        drawSection( painter, rect, rect.x(), width, QModelIndex() );
    }
}


QModelIndex
PartitionBarsView::indexAt( const QPoint& point ) const
{
    return QModelIndex();
}


QRect
PartitionBarsView::visualRect( const QModelIndex& index ) const
{
    return QRect();
}


QRegion
PartitionBarsView::visualRegionForSelection( const QItemSelection& selection ) const
{
    return QRegion();
}


int
PartitionBarsView::horizontalOffset() const
{
    return 0;
}


int
PartitionBarsView::verticalOffset() const
{
    return 0;
}


void
PartitionBarsView::scrollTo( const QModelIndex& index, ScrollHint hint )
{
}


QModelIndex
PartitionBarsView::moveCursor( CursorAction cursorAction, Qt::KeyboardModifiers modifiers )
{
    return QModelIndex();
}


bool
PartitionBarsView::isIndexHidden( const QModelIndex& index ) const
{
    return false;
}


void
PartitionBarsView::setSelection( const QRect& rect, QItemSelectionModel::SelectionFlags flags )
{
}


void
PartitionBarsView::updateGeometries()
{
    updateGeometry(); //get a new rect() for redrawing all the labels
}
