/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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

#include "PartitionSplitterWidget.h"

#include "utils/Logger.h"

#include <QApplication>
#include <QPainter>
#include <QMouseEvent>
#include <QStyleOption>


static const int VIEW_HEIGHT = 30;
static const int CORNER_RADIUS = 3;
static const int EXTENDED_PARTITION_MARGIN = 4;


PartitionSplitterWidget::PartitionSplitterWidget( QWidget* parent )
    : QWidget( parent )
    , m_resizing( false )
    , m_itemToResize( nullptr )
    , m_itemToResizeNext( nullptr )
    , HANDLE_SNAP( QApplication::startDragDistance() )
{
    setMouseTracking( true );
}


void
PartitionSplitterWidget::init( const QList<PartitionSplitterItem>& items )
{
    m_itemToResize = nullptr;
    m_itemToResizeNext = nullptr;
    m_itemToResizePath.clear();

    m_items.clear();
    m_items = items;
    repaint();
    foreach ( const PartitionSplitterItem& item, items )
        cDebug() << "PSI added item" << item.itemPath << "size" << item.size;
}


void
PartitionSplitterWidget::setSplitPartition( const QString& path,
                                            qint64 minSize,
                                            qint64 maxSize,
                                            qint64 preferredSize,
                                            const QString& newLabel )
{
    cDebug() << Q_FUNC_INFO << "path:" << path
             << "\nminSize:" << minSize
             << "\nmaxSize:" << maxSize
             << "\nprfSize:" << preferredSize;

    if ( m_itemToResize || m_itemToResizeNext || !m_itemToResizePath.isEmpty() )
    {
        cDebug() << "ERROR: trying to split partition but partition to split is already set.";
        return;
    }

    PartitionSplitterItem* itemToResize = _findItem( m_items,
                                                     [ path ]( PartitionSplitterItem& item ) -> bool
    {
        return path == item.itemPath;
    } );

    if ( !itemToResize )
        return;
    cDebug() << "itemToResize:" << itemToResize->itemPath;

    m_itemToResize = itemToResize;
    m_itemToResizePath = path;

    if ( preferredSize > maxSize )
        preferredSize = maxSize;

    qint64 newSize = m_itemToResize->size - preferredSize;
    m_itemToResize->size = preferredSize;
    m_itemMinSize = minSize;
    m_itemMaxSize = maxSize;
    m_itemPrefSize = preferredSize;

    for ( int i = 0; i < m_items.count(); ++i )
    {
        if ( m_items[ i ].itemPath == itemToResize->itemPath )
        {
            m_items.insert( i+1,
                            { "", QColor( "#d667b7" ), false, newSize, {} } );
            m_itemToResizeNext = &( m_items[ i+1 ] );
            break;
        }
        else if ( !m_items[ i ].children.isEmpty() )
        {
            for ( int j = 0; j < m_items[ i ].children.count(); ++j )
            {
                if ( m_items[ i ].children[ j ].itemPath == itemToResize->itemPath )
                {
                    m_items[ i ].children.insert( j+1,
                                                  { "", QColor( "#d667b7" ), false, newSize, {} } );
                    m_itemToResizeNext = &( m_items[ i ].children[ j+1 ] );
                    break;
                }
            }
            if ( m_itemToResizeNext )
                break;
        }
    }
    repaint();

    emit partitionResized( m_itemToResize->itemPath,
                           m_itemToResize->size,
                           m_itemToResizeNext->size );

    cDebug() << "Items updated. Status:";
    foreach ( const PartitionSplitterItem& item, m_items )
        cDebug() << "item" << item.itemPath << "size" << item.size;
}


qint64
PartitionSplitterWidget::splitPartitionSize() const
{
    if ( !m_itemToResize )
        return -1;
    return m_itemToResize->size;
}


qint64
PartitionSplitterWidget::newPartitionSize() const
{
    if ( !m_itemToResizeNext )
        return -1;
    return m_itemToResizeNext->size;
}


QSize
PartitionSplitterWidget::sizeHint() const
{
    return QSize( -1, VIEW_HEIGHT );
}


void
PartitionSplitterWidget::paintEvent( QPaintEvent* event )
{
    QPainter painter( this );
    painter.fillRect( rect(), palette().window() );
    painter.setRenderHint( QPainter::Antialiasing );
    if ( m_itemToResize && m_itemToResizeNext )
        drawPartitions( &painter, rect(), m_items );
}


void
PartitionSplitterWidget::mousePressEvent( QMouseEvent* event )
{
    if ( event->button() == Qt::LeftButton )
    {
        if ( qAbs( event->x() - m_resizeHandleX ) < HANDLE_SNAP )
            m_resizing = true;
    }
}


void
PartitionSplitterWidget::mouseMoveEvent( QMouseEvent* event )
{
    if ( m_resizing )
    {
        qint64 start = 0;
        foreach ( const PartitionSplitterItem& item, m_items )
        {
            if ( item.itemPath == m_itemToResize->itemPath )
                break;
            else if ( !item.children.isEmpty() )
            {
                bool done = false;
                foreach ( const PartitionSplitterItem& child, item.children )
                {
                    if ( child.itemPath == m_itemToResize->itemPath )
                    {
                        done = true;
                        break;
                    }
                    start += child.size;
                }
                if ( done )
                    break;
            }
            else
                start += item.size;
        }

        qint64 total = 0;
        for ( int row = 0; row < m_items.count(); ++row )
        {
            total += m_items[ row ].size;
        }

        int ew = rect().width(); //effective width
        qreal bpp = total / static_cast< qreal >( ew );  //bytes per pixel

        qreal mx = event->x() * bpp - start;

        // make sure we are within resize range
        mx = qBound( static_cast< qreal >( m_itemMinSize ),
                     mx,
                     static_cast< qreal >( m_itemMaxSize ) );

        qint64 span = m_itemPrefSize;
        qreal percent = mx / span;
        qint64 oldsize = m_itemToResize->size;

        m_itemToResize->size = qRound64( span * percent );
        m_itemToResizeNext->size -= m_itemToResize->size - oldsize;

        qint64 t = 0;
        for ( int row = 0; row < m_items.count(); ++row )
        {
            t += m_items[ row ].size;
        }
        Q_ASSERT( t == total );

        repaint();

        emit partitionResized( m_itemToResize->itemPath,
                               m_itemToResize->size,
                               m_itemToResizeNext->size );
    }
    else
    {
        if ( m_itemToResize )
        {
            if ( qAbs( event->x() - m_resizeHandleX ) < HANDLE_SNAP )
                setCursor( Qt::SplitHCursor );
            else if ( cursor().shape() != Qt::ArrowCursor )
                setCursor( Qt::ArrowCursor );
        }
    }
}


void
PartitionSplitterWidget::mouseReleaseEvent( QMouseEvent* event )
{
    m_resizing = false;
}


void
PartitionSplitterWidget::drawSection( QPainter* painter, const QRect& rect_, int x, int width,
                                      const PartitionSplitterItem& item )
{
    QColor color = item.color;
    bool isFreeSpace = item.isFreeSpace;

    QRect rect = rect_;
    const int y = rect.y();
    const int rectHeight = rect.height();
    const int radius = qMax( 1, CORNER_RADIUS - ( height() - rectHeight ) / 2 );
    painter->setClipRect( x, y, width, rectHeight );
    painter->translate( 0.5, 0.5 );

    rect.adjust( 0, 0, -1, -1 );
    const QColor borderColor = color.darker();
    painter->setPen( borderColor );
    painter->setBrush( color );
    painter->drawRoundedRect( rect, radius, radius );

    // Draw shade
    if ( !isFreeSpace )
        rect.adjust( 2, 2, -2, -2 );

    QLinearGradient gradient( 0, 0, 0, rectHeight / 2 );

    qreal c = isFreeSpace ? 0 : 1;
    gradient.setColorAt( 0, QColor::fromRgbF( c, c, c, 0.3 ) );
    gradient.setColorAt( 1, QColor::fromRgbF( c, c, c, 0 ) );

    painter->setPen( Qt::NoPen );
    painter->setBrush( gradient );
    painter->drawRoundedRect( rect, radius, radius );

    painter->translate( -0.5, -0.5 );
}

void
PartitionSplitterWidget::drawResizeHandle( QPainter* painter,
                                           const QRect& rect_,
                                           int x )
{
    if ( !m_itemToResize )
        return;

    painter->setPen( Qt::NoPen );
    painter->setBrush( Qt::black );
    painter->setClipRect( rect_ );

    painter->setRenderHint( QPainter::Antialiasing, true );

    qreal h = rect_.height();
    int scaleFactor = qRound( height() / static_cast< qreal >( VIEW_HEIGHT ) );
    QList< QPair< qreal, qreal > > arrow_offsets = {
        qMakePair( 0, h / 2 - 1 ),
        qMakePair( 4, h / 2 - 1 ),
        qMakePair( 4, h / 2 - 3 ),
        qMakePair( 8, h / 2 ),
        qMakePair( 4, h / 2 + 3 ),
        qMakePair( 4, h / 2 + 1 ),
        qMakePair( 0, h / 2 + 1 )
    };
    for ( int i = 0; i < arrow_offsets.count(); ++i )
    {
        arrow_offsets[ i ] = qMakePair( arrow_offsets[ i ].first * scaleFactor,
                                        ( arrow_offsets[ i ].second - h/2 ) * scaleFactor + h/2 );
    }

    auto p1 = arrow_offsets[ 0 ];
    if ( m_itemToResize->size > m_itemMinSize )
    {
        auto arrow = QPainterPath( QPointF( x + -1 * p1.first, p1.second ) );
        for ( auto p : arrow_offsets )
            arrow.lineTo( x + -1 * p.first + 1, p.second );
        painter->drawPath( arrow );
    }

    if ( m_itemToResize->size < m_itemMaxSize )
    {
        auto arrow = QPainterPath( QPointF( x + p1.first, p1.second ) );
        for ( auto p : arrow_offsets )
            arrow.lineTo( x + p.first, p.second );
        painter->drawPath( arrow );
    }

    painter->setRenderHint( QPainter::Antialiasing, false );
    painter->setPen( Qt::black );
    painter->drawLine( x, 0, x, h - 1 );
}


void
PartitionSplitterWidget::drawPartitions( QPainter* painter,
                                         const QRect& rect,
                                         const QList< PartitionSplitterItem >& items )
{
    const int count = items.count();
    const int totalWidth = rect.width();

    qint64 total = 0;
    for ( int row = 0; row < count; ++row )
    {
        total += items[ row ].size;
    }

    int x = rect.x();
    for ( int row = 0; row < count; ++row )
    {
        const PartitionSplitterItem& item = items[ row ];
        int width;
        if ( row < count - 1 )
            width = totalWidth * ( item.size / static_cast< qreal >( total ) );
        else
            // Make sure we fill the last pixel column
            width = rect.right() - x + 1;

        drawSection( painter, rect, x, width, item );
        if ( !item.children.isEmpty() )
        {
            QRect subRect(
                x + EXTENDED_PARTITION_MARGIN,
                rect.y() + EXTENDED_PARTITION_MARGIN,
                width - 2 * EXTENDED_PARTITION_MARGIN,
                rect.height() - 2 * EXTENDED_PARTITION_MARGIN
            );
            drawPartitions( painter, subRect, item.children );
        }

        if ( item.itemPath == m_itemToResize->itemPath )
            m_resizeHandleX = x + width;

        x += width;
    }
    drawResizeHandle( painter, rect, m_resizeHandleX );
}


template < typename F >
PartitionSplitterItem*
PartitionSplitterWidget::_findItem( QList< PartitionSplitterItem >& items,
                                    F condition )
{
    for ( auto it = items.begin(); it != items.end(); ++it)
    {
        if ( condition( *it ) )
            return &*it;

        PartitionSplitterItem* candidate = _findItem( it->children, condition );
        if ( candidate )
            return candidate;
    }
    return nullptr;
}
