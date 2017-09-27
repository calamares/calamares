/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
 *   Copyright 2015-2016, Teo Mrnjavac <teo@kde.org>
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

#include <utils/CalamaresUtilsGui.h>
#include <utils/Logger.h>


// Qt
#include <QDebug>
#include <QGuiApplication>
#include <QMouseEvent>
#include <QPainter>


static const int VIEW_HEIGHT = qMax( CalamaresUtils::defaultFontHeight() + 8, // wins out with big fonts
                                     int( CalamaresUtils::defaultFontHeight() * 0.6 ) + 22 ); // wins out with small fonts
static constexpr int CORNER_RADIUS = 3;
static const int EXTENDED_PARTITION_MARGIN = qMax( 4, VIEW_HEIGHT / 6 );

// The SELECTION_MARGIN is applied within a hardcoded 2px padding anyway, so
// we start from EXTENDED_PARTITION_MARGIN - 2 in all cases.
// Then we try to ensure the selection rectangle fits exactly between the extended
// rectangle and the outer frame (the "/ 2" part), unless that's not possible, and in
// that case we at least make sure we have a 1px gap between the selection rectangle
// and the extended partition box (the "- 2" part).
// At worst, on low DPI systems, this will mean in order:
// 1px outer rect, 1 px gap, 1px selection rect, 1px gap, 1px extended partition rect.
static const int SELECTION_MARGIN = qMin( ( EXTENDED_PARTITION_MARGIN - 2 ) / 2,
                                          ( EXTENDED_PARTITION_MARGIN - 2 ) - 2 );


PartitionBarsView::PartitionBarsView( QWidget* parent )
    : QAbstractItemView( parent )
    , m_nestedPartitionsMode( NoNestedPartitions )
    , canBeSelected( []( const QModelIndex& ) { return true; } )
    , m_hoveredIndex( QModelIndex() )
{
    setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Fixed );
    setFrameStyle( QFrame::NoFrame );
    setSelectionBehavior( QAbstractItemView::SelectRows );
    setSelectionMode( QAbstractItemView::SingleSelection );

    // Debug
    connect( this, &PartitionBarsView::clicked,
             this, [=]( const QModelIndex& index )
    {
        cDebug() << "Clicked row" << index.row();
    } );
    setMouseTracking( true );
}


PartitionBarsView::~PartitionBarsView()
{
}


void
PartitionBarsView::setNestedPartitionsMode( PartitionBarsView::NestedPartitionsMode mode )
{
    m_nestedPartitionsMode = mode;
    viewport()->repaint();
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


void
PartitionBarsView::drawSection( QPainter* painter, const QRect& rect_, int x, int width, const QModelIndex& index )
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


    if ( selectionMode() != QAbstractItemView::NoSelection && // no hover without selection
         m_hoveredIndex.isValid() &&
         index == m_hoveredIndex )
    {
        if ( canBeSelected( index ) )
            painter->setBrush( color.lighter( 115 ) );
        else
            painter->setBrush( color );
    }
    else
    {
        painter->setBrush( color );
    }

    QColor borderColor = color.darker();

    painter->setPen( borderColor );

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

    if ( selectionMode() != QAbstractItemView::NoSelection &&
         index.isValid() &&
         selectionModel() &&
         !selectionModel()->selectedIndexes().isEmpty() &&
         selectionModel()->selectedIndexes().first() == index )
    {
        painter->setPen( QPen( borderColor, 1 ) );
        QColor highlightColor = QPalette().highlight().color();
        highlightColor = highlightColor.lighter( 500 );
        highlightColor.setAlpha( 120 );
        painter->setBrush( highlightColor );

        QRect selectionRect = rect;
        selectionRect.setX( x + 1 );
        selectionRect.setWidth( width - 3 ); //account for the previous rect.adjust

        if ( rect.x() > selectionRect.x() ) //hack for first item
            selectionRect.adjust( rect.x() - selectionRect.x(), 0, 0, 0 );

        if ( rect.right() < selectionRect.right() ) //hack for last item
            selectionRect.adjust( 0, 0, - ( selectionRect.right() - rect.right() ), 0 );

        selectionRect.adjust( SELECTION_MARGIN,
                              SELECTION_MARGIN,
                              -SELECTION_MARGIN,
                              -SELECTION_MARGIN );

        painter->drawRoundedRect( selectionRect,
                                  radius - 1,
                                  radius - 1 );
    }

    painter->translate( -0.5, -0.5 );
}


void
PartitionBarsView::drawPartitions( QPainter* painter, const QRect& rect, const QModelIndex& parent )
{
    PartitionModel* modl = qobject_cast< PartitionModel* >( model() );
    if ( !modl )
        return;
    const int totalWidth = rect.width();

    auto pair = computeItemsVector( parent );
    QVector< PartitionBarsView::Item >& items = pair.first;
    qreal& total = pair.second;
    int x = rect.x();
    for ( int row = 0; row < items.count(); ++row )
    {
        const auto& item = items[ row ];
        int width;
        if ( row < items.count() - 1 )
            width = totalWidth * ( item.size / total );
        else
            // Make sure we fill the last pixel column
            width = rect.right() - x + 1;

        drawSection( painter, rect, x, width, item.index );

        if ( m_nestedPartitionsMode == DrawNestedPartitions &&
             modl->hasChildren( item.index ) )
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

    if ( !items.count() &&
         !modl->device()->partitionTable() ) // No disklabel or unknown
    {
        int width = rect.right() - rect.x() + 1;
        drawSection( painter, rect, rect.x(), width, QModelIndex() );
    }
}


QModelIndex
PartitionBarsView::indexAt( const QPoint& point ) const
{
    return indexAt( point, rect(), QModelIndex() );
}


QModelIndex
PartitionBarsView::indexAt( const QPoint &point,
                            const QRect &rect,
                            const QModelIndex& parent ) const
{
    PartitionModel* modl = qobject_cast< PartitionModel* >( model() );
    if ( !modl )
        return QModelIndex();
    const int totalWidth = rect.width();

    auto pair = computeItemsVector( parent );
    QVector< PartitionBarsView::Item >& items = pair.first;
    qreal& total = pair.second;
    int x = rect.x();
    for ( int row = 0; row < items.count(); ++row )
    {
        const auto& item = items[ row ];
        int width;
        if ( row < items.count() - 1 )
            width = totalWidth * ( item.size / total );
        else
            // Make sure we fill the last pixel column
            width = rect.right() - x + 1;

        QRect thisItemRect( x, rect.y(), width, rect.height() );
        if ( thisItemRect.contains( point ) )
        {
            if ( m_nestedPartitionsMode == DrawNestedPartitions &&
                 modl->hasChildren( item.index ) )
            {
                QRect subRect(
                    x + EXTENDED_PARTITION_MARGIN,
                    rect.y() + EXTENDED_PARTITION_MARGIN,
                    width - 2 * EXTENDED_PARTITION_MARGIN,
                    rect.height() - 2 * EXTENDED_PARTITION_MARGIN
                );

                if ( subRect.contains( point ) )
                {
                    return indexAt( point, subRect, item.index );
                }
                return item.index;
            }
            else // contains but no children, we win
            {
                return item.index;
            }
        }
        x += width;
    }

    return QModelIndex();
}


QRect
PartitionBarsView::visualRect( const QModelIndex& index ) const
{
    return visualRect( index, rect(), QModelIndex() );
}


QRect
PartitionBarsView::visualRect( const QModelIndex& index,
                               const QRect& rect,
                               const QModelIndex& parent ) const
{
    PartitionModel* modl = qobject_cast< PartitionModel* >( model() );
    if ( !modl )
        return QRect();
    const int totalWidth = rect.width();

    auto pair = computeItemsVector( parent );
    QVector< PartitionBarsView::Item >& items = pair.first;
    qreal& total = pair.second;
    int x = rect.x();
    for ( int row = 0; row < items.count(); ++row )
    {
        const auto& item = items[ row ];
        int width;
        if ( row < items.count() - 1 )
            width = totalWidth * ( item.size / total );
        else
            // Make sure we fill the last pixel column
            width = rect.right() - x + 1;

        QRect thisItemRect( x, rect.y(), width, rect.height() );
        if ( item.index == index )
            return thisItemRect;

        if ( m_nestedPartitionsMode == DrawNestedPartitions &&
             modl->hasChildren( item.index ) &&
             index.parent() == item.index )
        {
            QRect subRect(
                x + EXTENDED_PARTITION_MARGIN,
                rect.y() + EXTENDED_PARTITION_MARGIN,
                width - 2 * EXTENDED_PARTITION_MARGIN,
                rect.height() - 2 * EXTENDED_PARTITION_MARGIN
            );

            QRect candidateVisualRect = visualRect( index, subRect, item.index );
            if ( !candidateVisualRect.isNull() )
                return candidateVisualRect;
        }

        x += width;
    }

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
    Q_UNUSED( index )
    Q_UNUSED( hint )
}


void
PartitionBarsView::setSelectionModel( QItemSelectionModel* selectionModel )
{
    QAbstractItemView::setSelectionModel( selectionModel );
    connect( selectionModel, &QItemSelectionModel::selectionChanged,
             this, [=]
    {
        viewport()->repaint();
    } );
}


void
PartitionBarsView::setSelectionFilter( std::function< bool ( const QModelIndex& ) > canBeSelected )
{
    this->canBeSelected = canBeSelected;
}


QModelIndex
PartitionBarsView::moveCursor( CursorAction, Qt::KeyboardModifiers )
{
    return QModelIndex();
}


bool
PartitionBarsView::isIndexHidden( const QModelIndex& ) const
{
    return false;
}


void
PartitionBarsView::setSelection( const QRect& rect, QItemSelectionModel::SelectionFlags flags )
{
    //HACK: this is an utterly awful workaround, which is unfortunately necessary.
    //      QAbstractItemView::mousePressedEvent calls setSelection, but before that,
    //      for some mental reason, it works under the assumption that every item is a
    //      rectangle. This rectangle is provided by visualRect, and the idea mostly
    //      works, except when the item is an extended partition item, which is of course
    //      a rectangle with a rectangular hole in the middle.
    //      QAbstractItemView::mousePressEvent builds a QRect with x1, y1 in the center
    //      of said visualRect, and x2, y2 in the real QMouseEvent position.
    //      This may very well yield a QRect with negative size, which is meaningless.
    //      Therefore the QRect we get here is totally bogus, and its topLeft is outside
    //      the actual area of the item we need.
    //      What we need are the real coordinates of the QMouseEvent, and the only way to
    //      get them is by fetching the private x2, y2 from the rect.
    //      TL;DR: this sucks, look away. -- Teo 12/2015
    int x1, y1, x2, y2;
    rect.getCoords( &x1, &y1, &x2, &y2 );

    QModelIndex eventIndex = indexAt( QPoint( x2, y2 ) );
    if ( canBeSelected( eventIndex ) )
        selectionModel()->select( eventIndex, flags );

    viewport()->repaint();
}


void
PartitionBarsView::mouseMoveEvent( QMouseEvent* event )
{
    QModelIndex candidateIndex = indexAt( event->pos() );
    QPersistentModelIndex oldHoveredIndex = m_hoveredIndex;
    if ( candidateIndex.isValid() )
    {
        m_hoveredIndex = candidateIndex;
    }
    else
    {
        m_hoveredIndex = QModelIndex();
        QGuiApplication::restoreOverrideCursor();
    }

    if ( oldHoveredIndex != m_hoveredIndex )
    {
        if ( m_hoveredIndex.isValid() && !canBeSelected( m_hoveredIndex ) )
            QGuiApplication::setOverrideCursor( Qt::ForbiddenCursor );
        else
            QGuiApplication::restoreOverrideCursor();

        viewport()->repaint();
    }
}


void
PartitionBarsView::leaveEvent( QEvent* )
{
    QGuiApplication::restoreOverrideCursor();
    if ( m_hoveredIndex.isValid() )
    {
        m_hoveredIndex = QModelIndex();
        viewport()->repaint();
    }
}


void
PartitionBarsView::mousePressEvent( QMouseEvent* event )
{
    QModelIndex candidateIndex = indexAt( event->pos() );
    if ( canBeSelected( candidateIndex ) )
        QAbstractItemView::mousePressEvent( event );
    else
        event->accept();
}


void
PartitionBarsView::updateGeometries()
{
    updateGeometry(); //get a new rect() for redrawing all the labels
}


QPair< QVector< PartitionBarsView::Item >, qreal >
PartitionBarsView::computeItemsVector( const QModelIndex& parent ) const
{
    int count = model()->rowCount( parent );
    QVector< PartitionBarsView::Item > items;

    qreal total = 0;
    for ( int row = 0; row < count; ++row )
    {
        QModelIndex index = model()->index( row, 0, parent );
        if ( m_nestedPartitionsMode == NoNestedPartitions &&
             model()->hasChildren( index ) )
        {
            QPair< QVector< PartitionBarsView::Item >, qreal > childVect =
                    computeItemsVector( index );
            items += childVect.first;
            total += childVect.second;
        }
        else
        {
            qreal size = index.data( PartitionModel::SizeRole ).toLongLong();
            total += size;
            items.append( { size, index } );
        }
    }

    count = items.count();

    // The sizes we have are perfect, but now we have to hardcode a minimum size for small
    // partitions and compensate for it in the total.
    qreal adjustedTotal = total;
    for ( int row = 0; row < count; ++row )
    {
        if ( items[ row ].size < 0.01 * total ) // If this item is smaller than 1% of everything,
        {                                       // force its width to 1%.
            adjustedTotal -= items[ row ].size;
            items[ row ].size = 0.01 * total;
            adjustedTotal += items[ row ].size;
        }
    }

    return qMakePair( items, adjustedTotal );
}

