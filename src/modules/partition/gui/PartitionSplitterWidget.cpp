/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2016, Teo Mrnjavac <teo@kde.org>
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

#include "core/ColorUtils.h"
#include "core/PartitionIterator.h"
#include "core/KPMHelpers.h"

#include "utils/Logger.h"
#include "utils/CalamaresUtilsGui.h"

#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>

#include <QApplication>
#include <QPainter>
#include <QMouseEvent>
#include <QStyleOption>

static const int VIEW_HEIGHT = qMax( CalamaresUtils::defaultFontHeight() + 8, // wins out with big fonts
                                     int( CalamaresUtils::defaultFontHeight() * 0.6 ) + 22 ); // wins out with small fonts
static const int CORNER_RADIUS = 3;
static const int EXTENDED_PARTITION_MARGIN = qMax( 4, VIEW_HEIGHT / 6 );

PartitionSplitterWidget::PartitionSplitterWidget( QWidget* parent )
    : QWidget( parent )
    , m_itemToResize( PartitionSplitterItem::null() )
    , m_itemToResizeNext( PartitionSplitterItem::null() )
    , m_itemMinSize( 0 )
    , m_itemMaxSize( 0 )
    , m_itemPrefSize( 0 )
    , m_resizing( false )
    , m_resizeHandleX( 0 )
    , HANDLE_SNAP( QApplication::startDragDistance() )
    , m_drawNestedPartitions( false )
{
    setMouseTracking( true );
}


void
PartitionSplitterWidget::init( Device* dev, bool drawNestedPartitions )
{
    m_drawNestedPartitions = drawNestedPartitions;
    QVector< PartitionSplitterItem > allPartitionItems;
    PartitionSplitterItem* extendedPartitionItem = nullptr;
    for ( auto it = PartitionIterator::begin( dev );
          it != PartitionIterator::end( dev ); ++it )
    {
        PartitionSplitterItem newItem = {
            ( *it )->partitionPath(),
            ColorUtils::colorForPartition( *it ),
            KPMHelpers::isPartitionFreeSpace( *it ),
            ( *it )->capacity(),
            PartitionSplitterItem::Normal,
            {}
        };

        // If we don't draw child partitions of a partitions as child partitions, we
        // need to flatten the items tree into an items list
        if ( drawNestedPartitions )
        {
            if ( ( *it )->roles().has( PartitionRole::Logical ) && extendedPartitionItem )
                extendedPartitionItem->children.append( newItem );
            else
            {
                allPartitionItems.append( newItem );
                if ( ( *it )->roles().has( PartitionRole::Extended ) )
                    extendedPartitionItem = &allPartitionItems.last();
            }
        }
        else
        {
            if ( !( *it )->roles().has( PartitionRole::Extended ) )
                allPartitionItems.append( newItem );
        }
    }

    setupItems( allPartitionItems );
}

void
PartitionSplitterWidget::setupItems( const QVector<PartitionSplitterItem>& items )
{
    m_itemToResize = PartitionSplitterItem::null();
    m_itemToResizeNext = PartitionSplitterItem::null();
    m_itemToResizePath.clear();

    m_items.clear();
    m_items = items;
    repaint();
    for ( const PartitionSplitterItem& item : items )
        cDebug() << "PSI added item" << item.itemPath << "size" << item.size;
}


void
PartitionSplitterWidget::setSplitPartition( const QString& path,
                                            qint64 minSize,
                                            qint64 maxSize,
                                            qint64 preferredSize )
{
    cDebug() << Q_FUNC_INFO << "path:" << path
             << "\nminSize:" << minSize
             << "\nmaxSize:" << maxSize
             << "\nprfSize:" << preferredSize;

    if ( m_itemToResize && m_itemToResizeNext )
    {
        cDebug() << "NOTICE: trying to split partition but partition to split is already set.";

        // We need to remove the itemToResizeNext from wherever it is
        for ( int i = 0; i < m_items.count(); ++i )
        {
            if ( m_items[ i ].itemPath == m_itemToResize.itemPath &&
                 m_items[ i ].status == PartitionSplitterItem::Resizing &&
                 i + 1 < m_items.count() )
            {
                m_items[ i ].size = m_items[ i ].size + m_itemToResizeNext.size;
                m_items[ i ].status = PartitionSplitterItem::Normal;
                m_items.removeAt( i + 1 );
                m_itemToResizeNext = PartitionSplitterItem::null();
                break;
            }
            else if ( !m_items[ i ].children.isEmpty() )
            {
                for ( int j = 0; j < m_items[ i ].children.count(); ++j )
                {
                    if ( m_items[ i ].children[ j ].itemPath == m_itemToResize.itemPath &&
                         j + 1 < m_items[ i ].children.count() )
                    {
                        m_items[ i ].children[ j ].size =
                                m_items[ i ].children[ j ].size + m_itemToResizeNext.size;
                        m_items[ i ].children[ j ].status = PartitionSplitterItem::Normal;
                        m_items[ i ].children.removeAt( j + 1 );
                        m_itemToResizeNext = PartitionSplitterItem::null();
                        break;
                    }
                }
                if ( m_itemToResizeNext.isNull() )
                    break;
            }
        }

        m_itemToResize = PartitionSplitterItem::null();
        m_itemToResizePath.clear();
    }

    PartitionSplitterItem itemToResize = _findItem( m_items,
        [ path ]( PartitionSplitterItem& item ) -> bool
    {
        if ( path == item.itemPath )
        {
            item.status = PartitionSplitterItem::Resizing;
            return true;
        }
        return false;
    } );

    if ( itemToResize.isNull() )
        return;
    cDebug() << "itemToResize:" << itemToResize.itemPath;

    m_itemToResize = itemToResize;
    m_itemToResizePath = path;

    if ( preferredSize > maxSize )
        preferredSize = maxSize;

    qint64 newSize = m_itemToResize.size - preferredSize;
    m_itemToResize.size = preferredSize;
    int opCount = _eachItem( m_items,
               [ preferredSize ]( PartitionSplitterItem& item ) -> bool
    {
        if ( item.status == PartitionSplitterItem::Resizing )
        {
            item.size = preferredSize;
            return true;
        }
        return false;
    } );
    cDebug() << "each splitter item opcount:" << opCount;
    m_itemMinSize = minSize;
    m_itemMaxSize = maxSize;
    m_itemPrefSize = preferredSize;

    for ( int i = 0; i < m_items.count(); ++i )
    {
        if ( m_items[ i ].itemPath == itemToResize.itemPath )
        {
            m_items.insert( i+1,
                            { "",
                              QColor( "#c0392b" ),
                              false,
                              newSize,
                              PartitionSplitterItem::ResizingNext,
                              {} } );
            m_itemToResizeNext = m_items[ i+1 ];
            break;
        }
        else if ( !m_items[ i ].children.isEmpty() )
        {
            for ( int j = 0; j < m_items[ i ].children.count(); ++j )
            {
                if ( m_items[ i ].children[ j ].itemPath == itemToResize.itemPath )
                {
                    m_items[ i ].children.insert( j+1,
                                                  { "",
                                                    QColor( "#c0392b" ),
                                                    false,
                                                    newSize,
                                                    PartitionSplitterItem::ResizingNext,
                                                    {} } );
                    m_itemToResizeNext = m_items[ i ].children[ j+1 ];
                    break;
                }
            }
            if ( !m_itemToResizeNext.isNull() )
                break;
        }
    }

    emit partitionResized( m_itemToResize.itemPath,
                           m_itemToResize.size,
                           m_itemToResizeNext.size );

    cDebug() << "Items updated. Status:";
    foreach ( const PartitionSplitterItem& item, m_items )
        cDebug() << "item" << item.itemPath << "size" << item.size << "status:" << item.status;

    cDebug() << "m_itemToResize:    " << !m_itemToResize.isNull() << m_itemToResize.itemPath;
    cDebug() << "m_itemToResizeNext:" << !m_itemToResizeNext.isNull() << m_itemToResizeNext.itemPath;

    repaint();
}


qint64
PartitionSplitterWidget::splitPartitionSize() const
{
    if ( !m_itemToResize )
        return -1;
    return m_itemToResize.size;
}


qint64
PartitionSplitterWidget::newPartitionSize() const
{
    if ( !m_itemToResizeNext )
        return -1;
    return m_itemToResizeNext.size;
}


QSize
PartitionSplitterWidget::sizeHint() const
{
    return QSize( -1, VIEW_HEIGHT );
}


QSize
PartitionSplitterWidget::minimumSizeHint() const
{
    return sizeHint();
}


void
PartitionSplitterWidget::paintEvent( QPaintEvent* event )
{
    Q_UNUSED( event );

    QPainter painter( this );
    painter.fillRect( rect(), palette().window() );
    painter.setRenderHint( QPainter::Antialiasing );

    drawPartitions( &painter, rect(), m_items );
}


void
PartitionSplitterWidget::mousePressEvent( QMouseEvent* event )
{
    if ( m_itemToResize &&
         m_itemToResizeNext &&
         event->button() == Qt::LeftButton )
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
        QString itemPath = m_itemToResize.itemPath;
        for ( auto it = m_items.constBegin();
              it != m_items.constEnd(); ++it )
        {
            if ( it->itemPath == itemPath )
                break;
            else if ( !it->children.isEmpty() )
            {
                bool done = false;
                for ( auto jt = it->children.constBegin();
                      jt != it->children.constEnd(); ++jt )
                {
                    if ( jt->itemPath == itemPath )
                    {
                        done = true;
                        break;
                    }
                    start += jt->size;
                }
                if ( done )
                    break;
            }
            else
                start += it->size;
        }

        qint64 total = 0;
        for ( auto it = m_items.constBegin(); it != m_items.constEnd(); ++it )
        {
            total += it->size;
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
        qint64 oldsize = m_itemToResize.size;

        m_itemToResize.size = qRound64( span * percent );
        m_itemToResizeNext.size -= m_itemToResize.size - oldsize;
        _eachItem( m_items,
                   [ this ]( PartitionSplitterItem& item ) -> bool
        {
            if ( item.status == PartitionSplitterItem::Resizing )
            {
                item.size = m_itemToResize.size;
                return true;
            }
            else if ( item.status == PartitionSplitterItem::ResizingNext )
            {
                item.size = m_itemToResizeNext.size;
                return true;
            }
            return false;
        } );

        repaint();

        emit partitionResized( itemPath,
                               m_itemToResize.size,
                               m_itemToResizeNext.size );
    }
    else
    {
        if ( m_itemToResize && m_itemToResizeNext )
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
    Q_UNUSED( event );

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

    qreal h = VIEW_HEIGHT; // Put the arrow in the center regardless of inner box height
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
    if ( m_itemToResize.size > m_itemMinSize )
    {
        auto arrow = QPainterPath( QPointF( x + -1 * p1.first, p1.second ) );
        for ( auto p : arrow_offsets )
            arrow.lineTo( x + -1 * p.first + 1, p.second );
        painter->drawPath( arrow );
    }

    if ( m_itemToResize.size < m_itemMaxSize )
    {
        auto arrow = QPainterPath( QPointF( x + p1.first, p1.second ) );
        for ( auto p : arrow_offsets )
            arrow.lineTo( x + p.first, p.second );
        painter->drawPath( arrow );
    }

    painter->setRenderHint( QPainter::Antialiasing, false );
    painter->setPen( Qt::black );
    painter->drawLine( x, 0, x, int(h) - 1 );
}


void
PartitionSplitterWidget::drawPartitions( QPainter* painter,
                                         const QRect& rect,
                                         const QVector< PartitionSplitterItem >& itemList )
{
    const int count = itemList.count();
    const int totalWidth = rect.width();

    auto pair = computeItemsVector( itemList );
    QVector< PartitionSplitterItem >& items = pair.first;
    qreal total = pair.second;

    int x = rect.x();
    for ( int row = 0; row < count; ++row )
    {
        const PartitionSplitterItem& item = items[ row ];
        qreal width;
        if ( row < count - 1 )
            width = totalWidth * ( item.size / total );
        else
            // Make sure we fill the last pixel column
            width = rect.right() - x + 1;

        drawSection( painter, rect, x, int(width), item );
        if ( !item.children.isEmpty() )
        {
            QRect subRect(
                x + EXTENDED_PARTITION_MARGIN,
                rect.y() + EXTENDED_PARTITION_MARGIN,
                int(width) - 2 * EXTENDED_PARTITION_MARGIN,
                rect.height() - 2 * EXTENDED_PARTITION_MARGIN
            );
            drawPartitions( painter, subRect, item.children );
        }

        // If an item to resize and the following new item both exist,
        // and this is not the very first partition,
        // and the partition preceding this one is the item to resize...
        if ( m_itemToResize &&
             m_itemToResizeNext &&
             row > 0 &&
             !items[ row - 1 ].isFreeSpace &&
             !items[ row - 1 ].itemPath.isEmpty() &&
             items[ row - 1 ].itemPath == m_itemToResize.itemPath )
        {
            m_resizeHandleX = x;
            drawResizeHandle( painter, rect, m_resizeHandleX );
        }

        x += width;
    }
}


PartitionSplitterItem
PartitionSplitterWidget::_findItem( QVector< PartitionSplitterItem >& items,
                                    std::function< bool ( PartitionSplitterItem& ) > condition ) const
{
    for ( auto it = items.begin(); it != items.end(); ++it)
    {
        if ( condition( *it ) )
            return *it;

        PartitionSplitterItem candidate = _findItem( it->children, condition );
        if ( !candidate.isNull() )
            return candidate;
    }
    return PartitionSplitterItem::null();
}


int
PartitionSplitterWidget::_eachItem( QVector< PartitionSplitterItem >& items,
                                    std::function< bool ( PartitionSplitterItem& ) > operation ) const
{
    int opCount = 0;
    for ( auto it = items.begin(); it != items.end(); ++it)
    {
        if ( operation( *it ) )
            opCount++;

        opCount += _eachItem( it->children, operation );
    }
    return opCount;
}


QPair< QVector< PartitionSplitterItem >, qreal >
PartitionSplitterWidget::computeItemsVector( const QVector< PartitionSplitterItem >& originalItems ) const
{
    QVector< PartitionSplitterItem > items;

    qreal total = 0;
    for ( int row = 0; row < originalItems.count(); ++row )
    {
        if ( originalItems[ row ].children.isEmpty() )
        {
            items += originalItems[ row ];
            total += originalItems[ row ].size;
        }
        else
        {
            PartitionSplitterItem thisItem = originalItems[ row ];
            QPair< QVector< PartitionSplitterItem >, qreal > pair = computeItemsVector( thisItem.children );
            thisItem.children = pair.first;
            thisItem.size = qint64(pair.second);
            items += thisItem;
            total += thisItem.size;
        }
    }

    // The sizes we have are perfect, but now we have to hardcode a minimum size for small
    // partitions and compensate for it in the total.
    qreal adjustedTotal = total;
    for ( int row = 0; row < items.count(); ++row )
    {
        if ( items[ row ].size < 0.01 * total ) // If this item is smaller than 1% of everything,
        {                                       // force its width to 1%.
            adjustedTotal -= items[ row ].size;
            items[ row ].size = qint64(0.01 * total);
            adjustedTotal += items[ row ].size;
        }
    }

    return qMakePair( items, adjustedTotal );
}
