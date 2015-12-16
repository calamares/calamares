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

#include "PartitionLabelsView.h"

#include <core/PartitionModel.h>
#include <core/ColorUtils.h>

#include <utils/CalamaresUtilsGui.h>
#include <utils/Logger.h>

#include <kpmcore/core/device.h>

#include <KFormat>

// Qt
#include <QPainter>


static const int LAYOUT_MARGIN = 4;
static const int LABEL_PARTITION_SQUARE_MARGIN =
        qMax( QFontMetrics( CalamaresUtils::defaultFont() ).ascent() - 2, 18 );
static const int LABELS_MARGIN = LABEL_PARTITION_SQUARE_MARGIN;


QStringList
buildUnknownDisklabelTexts( Device* dev )
{
    QStringList texts = { QObject::tr( "Unpartitioned space or unknown partition table" ),
                          KFormat().formatByteSize( dev->totalSectors() * dev->logicalSectorSize() ) };
    return texts;
}


PartitionLabelsView::PartitionLabelsView( QWidget* parent )
    : QAbstractItemView( parent )
{
    setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Fixed );
    setFrameStyle( QFrame::NoFrame );
    setSelectionBehavior( QAbstractItemView::SelectRows );
    setSelectionMode( QAbstractItemView::SingleSelection );

    // Debug
    connect( this, &PartitionLabelsView::clicked,
             this, [=]( const QModelIndex& index )
    {
        cDebug() << "Clicked row" << index.row();
    } );
    setMouseTracking( true );
}


PartitionLabelsView::~PartitionLabelsView()
{
}


QSize
PartitionLabelsView::minimumSizeHint() const
{
    return sizeHint();
}



QSize
PartitionLabelsView::sizeHint() const
{
    QAbstractItemModel* modl = model();
    if ( modl )
    {
        return QSize( -1, LAYOUT_MARGIN + sizeForAllLabels( rect().width() ).height() );
    }
    return QSize();
}


void
PartitionLabelsView::paintEvent( QPaintEvent* event )
{
    QPainter painter( viewport() );
    painter.fillRect( rect(), palette().window() );
    painter.setRenderHint( QPainter::Antialiasing );

    QRect labelsRect = rect().adjusted( 0, LAYOUT_MARGIN, 0, 0 );

    drawLabels( &painter, labelsRect, QModelIndex() );
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
PartitionLabelsView::getIndexesToDraw( const QModelIndex& parent ) const
{
    QModelIndexList list;

    QAbstractItemModel* modl = model();
    if ( !modl )
        return list;

    for ( int row = 0; row < modl->rowCount( parent ); ++row )
    {
        QModelIndex index = modl->index( row, 0, parent );
        list.append( index );
        if ( modl->hasChildren( index ) )
            list.append( getIndexesToDraw( index ) );
    }
    return list;
}


QStringList
PartitionLabelsView::buildTexts( const QModelIndex& index ) const
{
    QString firstLine, secondLine;

    if ( index.data( PartitionModel::IsPartitionNewRole ).toBool() )
    {
        QString mountPoint = index.sibling( index.row(),
                                            PartitionModel::MountPointColumn )
                                  .data().toString();
        if ( mountPoint == "/" )
            firstLine = m_customNewRootLabel.isEmpty() ?
                            tr( "Root" ) :
                            m_customNewRootLabel;
        else if ( mountPoint == "/home" )
            firstLine = tr( "Home" );
        else if ( mountPoint == "/boot" )
            firstLine = tr( "Boot" );
        else if ( mountPoint.contains( "/efi" ) &&
                  index.sibling( index.row(),
                                 PartitionModel::FileSystemColumn )
                       .data().toString() == "fat32" )
            firstLine = tr( "EFI system" );
        else if ( index.sibling( index.row(),
                                 PartitionModel::FileSystemColumn )
                       .data().toString() == "linuxswap" )
            firstLine = tr( "Swap" );
        else
            firstLine = tr( "New partition for %1" ).arg( mountPoint );
    }
    else if ( index.data( PartitionModel::OsproberNameRole ).toString().isEmpty() )
        firstLine = index.data().toString();
    else
        firstLine = index.data( PartitionModel::OsproberNameRole ).toString();

    secondLine = tr( "%1  %2" )
                 .arg( index.sibling( index.row(),
                                      PartitionModel::SizeColumn )
                            .data().toString() )
                 .arg( index.sibling( index.row(),
                                      PartitionModel::FileSystemColumn )
                            .data().toString() );

    return { firstLine, secondLine };
}


void
PartitionLabelsView::drawLabels( QPainter* painter,
                                 const QRect& rect,
                                 const QModelIndex& parent )
{
    PartitionModel* modl = qobject_cast< PartitionModel* >( model() );
    if ( !modl )
        return;

    QModelIndexList indexesToDraw = getIndexesToDraw( parent );

    int label_x = rect.x();
    int label_y = rect.y();
    foreach ( const QModelIndex& index, indexesToDraw )
    {
        QStringList texts = buildTexts( index );

        QSize labelSize = sizeForLabel( texts );

        QColor labelColor = index.data( Qt::DecorationRole ).value< QColor >();

        if ( label_x + labelSize.width() > rect.width() ) //wrap to new line if overflow
        {
            label_x = rect.x();
            label_y += labelSize.height() + labelSize.height() / 4;
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
PartitionLabelsView::sizeForAllLabels( int maxLineWidth ) const
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
        QStringList texts = buildTexts( index );

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

    int totalHeight = numLines * singleLabelHeight +
                      ( numLines - 1 ) * singleLabelHeight / 4; //spacings

    return QSize( maxLineWidth, totalHeight );
}


QSize
PartitionLabelsView::sizeForLabel( const QStringList& text ) const
{
    int vertOffset = 0;
    int width = 0;
    foreach ( const QString& textLine, text )
    {
        QSize textSize = fontMetrics().size( Qt::TextSingleLine, textLine );

        vertOffset += textSize.height();
        width = qMax( width, textSize.width() );
    }
    width += LABEL_PARTITION_SQUARE_MARGIN; //for the color square
    return QSize( width, vertOffset );
}


void
PartitionLabelsView::drawLabel( QPainter* painter,
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
PartitionLabelsView::indexAt( const QPoint& point ) const
{
    return QModelIndex();
}


QRect
PartitionLabelsView::visualRect( const QModelIndex& index ) const
{
    return QRect();
}


QRegion
PartitionLabelsView::visualRegionForSelection( const QItemSelection& selection ) const
{
    return QRegion();
}


int
PartitionLabelsView::horizontalOffset() const
{
    return 0;
}


int
PartitionLabelsView::verticalOffset() const
{
    return 0;
}


void
PartitionLabelsView::scrollTo( const QModelIndex& index, ScrollHint hint )
{
}


void
PartitionLabelsView::setCustomNewRootLabel( const QString& text )
{
    m_customNewRootLabel = text;
    viewport()->repaint();
}


QModelIndex
PartitionLabelsView::moveCursor( CursorAction cursorAction, Qt::KeyboardModifiers modifiers )
{
    return QModelIndex();
}


bool
PartitionLabelsView::isIndexHidden( const QModelIndex& index ) const
{
    return false;
}


void
PartitionLabelsView::setSelection( const QRect& rect, QItemSelectionModel::SelectionFlags flags )
{
}


void
PartitionLabelsView::updateGeometries()
{
    updateGeometry(); //get a new rect() for redrawing all the labels
}
