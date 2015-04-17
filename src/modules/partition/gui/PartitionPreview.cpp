/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
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
#include <gui/PartitionPreview.h>

#include <core/PartitionModel.h>

// Qt
#include <QDebug>
#include <QPainter>


static const int VIEW_HEIGHT = 30;
static const int CORNER_RADIUS = 3;
static const int EXTENDED_PARTITION_MARGIN = 4;


PartitionPreview::PartitionPreview( QWidget* parent )
    : QAbstractItemView( parent )
{
    setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Fixed );
    setFrameStyle( QFrame::NoFrame );
}


PartitionPreview::~PartitionPreview()
{
}


QSize
PartitionPreview::minimumSizeHint() const
{
    return sizeHint();
}


QSize
PartitionPreview::sizeHint() const
{
    return QSize( -1, VIEW_HEIGHT );
}


void
PartitionPreview::paintEvent( QPaintEvent* event )
{
    QPainter painter( viewport() );
    painter.fillRect( rect(), palette().window() );
    painter.setRenderHint( QPainter::Antialiasing );
    drawPartitions( &painter, rect(), QModelIndex() );
}


static void
drawSection( QPainter* painter, const QRect& rect_, int x, int width, const QModelIndex& index )
{
    QColor color = index.data( Qt::DecorationRole ).value< QColor >();
    bool isFreeSpace = index.data( PartitionModel::IsFreeSpaceRole ).toBool();

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
PartitionPreview::drawPartitions( QPainter* painter, const QRect& rect, const QModelIndex& parent )
{
    QAbstractItemModel* modl = model();
    if ( !modl )
        return;
    const int count = modl->rowCount( parent );
    const int totalWidth = rect.width();
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
}


QModelIndex
PartitionPreview::indexAt( const QPoint& point ) const
{
    return QModelIndex();
}


QRect
PartitionPreview::visualRect( const QModelIndex& index ) const
{
    return QRect();
}


QRegion
PartitionPreview::visualRegionForSelection( const QItemSelection& selection ) const
{
    return QRegion();
}


int
PartitionPreview::horizontalOffset() const
{
    return 0;
}


int
PartitionPreview::verticalOffset() const
{
    return 0;
}


void
PartitionPreview::scrollTo( const QModelIndex& index, ScrollHint hint )
{
}


QModelIndex
PartitionPreview::moveCursor( CursorAction cursorAction, Qt::KeyboardModifiers modifiers )
{
    return QModelIndex();
}


bool
PartitionPreview::isIndexHidden( const QModelIndex& index ) const
{
    return false;
}


void
PartitionPreview::setSelection( const QRect& rect, QItemSelectionModel::SelectionFlags flags )
{
}

