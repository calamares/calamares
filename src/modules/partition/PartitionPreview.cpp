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
#include <PartitionPreview.h>

#include <PartitionModel.h>

// Qt
#include <QDebug>
#include <QPainter>


static const int VIEW_HEIGHT = 40;
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
PartitionPreview::sizeHint() const
{
    return QSize( -1, VIEW_HEIGHT );
}

void
PartitionPreview::paintEvent( QPaintEvent* event )
{
    QPainter painter( viewport() );
    painter.fillRect( rect(), Qt::red );
    drawPartitions( &painter, rect(), QModelIndex() );
}

void
PartitionPreview::drawPartitions( QPainter* painter, const QRect& rect, const QModelIndex& parent )
{
    QAbstractItemModel* modl = model();
    if ( !modl )
        return;
    const int count = modl->rowCount( parent );
    const int totalWidth = rect.width();
    struct Item {
        qreal size;
        QColor color;
        QModelIndex index;
    };
    QVector< Item > items( count );
    qreal total = 0;
    for ( int row = 0; row < count; ++row )
    {
        QModelIndex index = modl->index( row, 0, parent );
        qreal size = index.data( PartitionModel::SizeRole ).toLongLong();
        QColor color = index.data( Qt::DecorationRole ).value< QColor >();
        total += size;
        items[ row ] = { size, color, index };
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

        painter->fillRect( x, rect.y(), width, rect.height(), item.color );
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

