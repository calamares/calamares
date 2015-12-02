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
#include <gui/PartitionPreview.h>

#include <core/PartitionModel.h>
#include <core/ColorUtils.h>

#include <kpmcore/core/device.h>

#include "utils/CalamaresUtilsGui.h"

#include <KFormat>

// Qt
#include <QDebug>
#include <QPainter>

#include <functional>

static const int VIEW_HEIGHT = CalamaresUtils::defaultFontHeight() + 8;
static const int LAYOUT_MARGIN = 8;
static const int CORNER_RADIUS = 3;
static const int EXTENDED_PARTITION_MARGIN = 4;
static const int LABELS_MARGIN = 40;
static const int LABEL_PARTITION_SQUARE_MARGIN =
        qMax( QFontMetrics( CalamaresUtils::defaultFont() ).ascent() - 2, 18 );

QStringList
buildUnknownDisklabelTexts( Device* dev )
{
    QStringList texts = { QObject::tr( "Unpartitioned space or unknown partition table" ),
                          KFormat().formatByteSize( dev->totalSectors() * dev->logicalSectorSize() ) };
    return texts;
}

PartitionPreview::PartitionPreview( QWidget* parent )
    : m_showLabels( false )
    , QAbstractItemView( parent )
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
    QAbstractItemModel* modl = model();
    if ( m_showLabels && modl )
    {
        return QSize( -1, VIEW_HEIGHT + LAYOUT_MARGIN +
                          sizeForAllLabels( rect().width() ).height() );
    }
    return QSize( -1, VIEW_HEIGHT );
}


void
PartitionPreview::paintEvent( QPaintEvent* event )
{
    QPainter painter( viewport() );
    painter.fillRect( rect(), palette().window() );
    painter.setRenderHint( QPainter::Antialiasing );

    QRect partitionsRect = rect();
    partitionsRect.setHeight( VIEW_HEIGHT );
    QRect labelsRect = rect().adjusted( 0, VIEW_HEIGHT + LAYOUT_MARGIN, 0, 0 );

    painter.save();
    drawPartitions( &painter, partitionsRect, QModelIndex() );
    painter.restore();
    if ( m_showLabels )
        drawLabels( &painter, labelsRect, QModelIndex() );
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
PartitionPreview::drawPartitions( QPainter* painter, const QRect& rect, const QModelIndex& parent )
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


static void
drawPartitionSquare( QPainter* painter, const QRect& rect, const QBrush& brush )
{
    painter->fillRect( rect.adjusted( 1, 1, -1, -1 ), brush );
    painter->setRenderHint( QPainter::Antialiasing, true );
    painter->setPen( QPalette().shadow().color() );
    painter->translate( .5, .5 );
    painter->drawRoundedRect( rect.adjusted( 0, 0, -1, -1 ), 2, 2 );
    painter->translate( -.5, -.5 );
}


QModelIndexList
PartitionPreview::getIndexesToDraw( const QModelIndex& parent ) const
{
    QModelIndexList list;

    QAbstractItemModel* modl = model();
    if ( !modl )
        return list;

    for ( int row = 0; row < modl->rowCount( parent ); ++row )
    {
        QModelIndex index = modl->index( row, 0, parent );
        if ( modl->hasChildren( index ) )
            list.append( getIndexesToDraw( index ) );
        else
            list.append( index );
    }
    return list;
}


void
PartitionPreview::drawLabels( QPainter* painter, const QRect& rect, const QModelIndex& parent )
{
    PartitionModel* modl = qobject_cast< PartitionModel* >( model() );
    if ( !modl )
        return;

    QModelIndexList indexesToDraw = getIndexesToDraw( parent );

    int label_x = rect.x();
    int label_y = rect.y();
    foreach ( const QModelIndex& index, indexesToDraw )
    {
        QStringList texts = { index.data().toString(),
                              index.sibling( index.row(), PartitionModel::SizeColumn ).data().toString() };

        QSize labelSize = sizeForLabel( texts );

        QColor labelColor = index.data( Qt::DecorationRole ).value< QColor >();

        if ( label_x + labelSize.width() > rect.width() ) //wrap to new line if overflow
        {
            label_x = rect.x();
            label_y += labelSize.height();
        }
        drawLabel( painter, texts, labelColor, QPoint( label_x, label_y ) );

        label_x += labelSize.width() + LABELS_MARGIN;
    }

    if ( !modl->rowCount() &&
         !modl->device()->partitionTable() ) // No disklabel or unknown
    {
        QStringList texts = buildUnknownDisklabelTexts( modl->device() );
        QSize labelSize = sizeForLabel( texts );
        QColor labelColor = ColorUtils::unknownDisklabelColor();
        drawLabel( painter, texts, labelColor, QPoint( rect.x(), rect.y() ) );
    }
}


QSize
PartitionPreview::sizeForAllLabels( int maxLineWidth ) const
{
    PartitionModel* modl = qobject_cast< PartitionModel* >( model() );
    if ( !modl )
        return QSize();

    QModelIndexList indexesToDraw = getIndexesToDraw( QModelIndex() );

    int lineLength = 0;
    int numLines = 1;
    int singleLabelHeight = 0;
    foreach ( const QModelIndex& index, indexesToDraw )
    {
        QStringList texts = { index.data().toString(),
                              index.sibling( index.row(),
                                             PartitionModel::SizeColumn )
                                   .data().toString() };
        QSize labelSize = sizeForLabel( texts );

        if ( lineLength + labelSize.width() > maxLineWidth )
        {
            numLines++;
            lineLength = labelSize.width();
        }
        else
        {
            lineLength += LABELS_MARGIN + labelSize.width();
        }

        singleLabelHeight = qMax( singleLabelHeight, labelSize.height() );
    }

    if ( !modl->rowCount() &&
         !modl->device()->partitionTable() ) // Unknown or no disklabel
    {
        singleLabelHeight = sizeForLabel( buildUnknownDisklabelTexts( modl->device() ) )
                            .height();
    }

    int totalHeight = numLines * singleLabelHeight;

    return QSize( maxLineWidth, totalHeight );
}


QSize
PartitionPreview::sizeForLabel( const QStringList& text ) const
{
    int vertOffset = 0;
    int width = 0;
    foreach ( const QString& textLine, text )
    {
        QSize textSize = fontMetrics().size( Qt::TextSingleLine, textLine );
        if ( vertOffset == 0 )
            vertOffset = textSize.height() / 2;
        vertOffset += textSize.height();
        width = qMax( width, textSize.width() );
    }
    width += LABEL_PARTITION_SQUARE_MARGIN; //for the color square
    return QSize( width, vertOffset );
}


void
PartitionPreview::drawLabel( QPainter* painter,
                             const QStringList& text,
                             const QColor& color,
                             const QPoint& pos )
{
    painter->setPen( Qt::black );
    int vertOffset = 0;
    int width = 0;
    foreach ( const QString& textLine, text )
    {
        QSize textSize = painter->fontMetrics().size( Qt::TextSingleLine, textLine );
        painter->drawText( pos.x()+LABEL_PARTITION_SQUARE_MARGIN,
                           pos.y() + vertOffset + textSize.height() / 2,
                           textLine );
        vertOffset += textSize.height();
        painter->setPen( Qt::gray );
        width = qMax( width, textSize.width() );
    }
    drawPartitionSquare( painter, QRect( pos.x(),
                                         pos.y() - 3,
                                         LABEL_PARTITION_SQUARE_MARGIN - 5,
                                         LABEL_PARTITION_SQUARE_MARGIN - 5 ),
                          color );
    painter->setPen( Qt::black );
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


void
PartitionPreview::setLabelsVisible( bool visible )
{
    m_showLabels = visible;
    updateGeometry();
    repaint();
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


void
PartitionPreview::updateGeometries()
{
    updateGeometry(); //get a new rect() for redrawing all the labels
}
