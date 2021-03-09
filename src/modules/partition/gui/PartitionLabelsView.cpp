/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2015-2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "PartitionLabelsView.h"

#include "core/ColorUtils.h"
#include "core/PartitionModel.h"

#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"
#include "utils/Units.h"

#include <kpmcore/core/device.h>
#include <kpmcore/fs/filesystem.h>

#include <KFormat>

// Qt
#include <QGuiApplication>
#include <QMouseEvent>
#include <QPainter>

using namespace CalamaresUtils::Units;

static const int LAYOUT_MARGIN = 4;
static const int LABEL_PARTITION_SQUARE_MARGIN = qMax( QFontMetrics( CalamaresUtils::defaultFont() ).ascent() - 2, 18 );
static const int LABELS_MARGIN = LABEL_PARTITION_SQUARE_MARGIN;
static const int CORNER_RADIUS = 2;


static QStringList
buildUnknownDisklabelTexts( Device* dev )
{
    QStringList texts = { QObject::tr( "Unpartitioned space or unknown partition table" ),
                          KFormat().formatByteSize( dev->totalLogical() * dev->logicalSize() ) };
    return texts;
}


PartitionLabelsView::PartitionLabelsView( QWidget* parent )
    : QAbstractItemView( parent )
    , m_canBeSelected( []( const QModelIndex& ) { return true; } )
    , m_extendedPartitionHidden( false )
{
    setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Fixed );
    setFrameStyle( QFrame::NoFrame );
    setSelectionBehavior( QAbstractItemView::SelectRows );
    setSelectionMode( QAbstractItemView::SingleSelection );
    this->setObjectName( "partitionLabel" );
    setMouseTracking( true );
}


PartitionLabelsView::~PartitionLabelsView() {}


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
    Q_UNUSED( event )

    QPainter painter( viewport() );
    painter.fillRect( rect(), palette().window() );
    painter.setRenderHint( QPainter::Antialiasing );

    QRect lRect = labelsRect();

    drawLabels( &painter, lRect, QModelIndex() );
}


QRect
PartitionLabelsView::labelsRect() const
{
    return rect().adjusted( 0, LAYOUT_MARGIN, 0, 0 );
}


static void
drawPartitionSquare( QPainter* painter, const QRect& rect, const QBrush& brush )
{
    painter->fillRect( rect.adjusted( 1, 1, -1, -1 ), brush );
    painter->setRenderHint( QPainter::Antialiasing, true );
    painter->setPen( QPalette().shadow().color() );
    painter->translate( .5, .5 );
    painter->drawRoundedRect( rect.adjusted( 0, 0, -1, -1 ), CORNER_RADIUS, CORNER_RADIUS );
    painter->translate( -.5, -.5 );
}


static void
drawSelectionSquare( QPainter* painter, const QRect& rect, const QBrush& brush )
{
    painter->save();
    painter->setPen( QPen( brush.color().darker(), 1 ) );
    QColor highlightColor = QPalette().highlight().color();
    highlightColor = highlightColor.lighter( 500 );
    highlightColor.setAlpha( 120 );
    painter->setBrush( highlightColor );
    painter->translate( .5, .5 );
    painter->drawRoundedRect( rect.adjusted( 0, 0, -1, -1 ), CORNER_RADIUS, CORNER_RADIUS );
    painter->translate( -.5, -.5 );
    painter->restore();
}


QModelIndexList
PartitionLabelsView::getIndexesToDraw( const QModelIndex& parent ) const
{
    QModelIndexList list;

    QAbstractItemModel* modl = model();
    if ( !modl )
    {
        return list;
    }

    for ( int row = 0; row < modl->rowCount( parent ); ++row )
    {
        QModelIndex index = modl->index( row, 0, parent );

        //HACK: horrible special casing follows.
        //      To save vertical space, we choose to hide short instances of free space.
        //      Arbitrary limit: 10MiB.
        const qint64 maxHiddenB = 10_MiB;
        if ( index.data( PartitionModel::IsFreeSpaceRole ).toBool()
             && index.data( PartitionModel::SizeRole ).toLongLong() < maxHiddenB )
        {
            continue;
        }

        if ( !modl->hasChildren( index ) || !m_extendedPartitionHidden )
        {
            list.append( index );
        }

        if ( modl->hasChildren( index ) )
        {
            list.append( getIndexesToDraw( index ) );
        }
    }
    return list;
}


QStringList
PartitionLabelsView::buildTexts( const QModelIndex& index ) const
{
    QString firstLine, secondLine;

    if ( index.data( PartitionModel::IsPartitionNewRole ).toBool() )
    {
        QString label = index.data( PartitionModel::FileSystemLabelRole ).toString();

        if ( !label.isEmpty() )
        {
            firstLine = label;
        }
        else
        {
            QString mountPoint = index.sibling( index.row(), PartitionModel::MountPointColumn ).data().toString();
            if ( mountPoint == "/" )
            {
                firstLine = m_customNewRootLabel.isEmpty() ? tr( "Root" ) : m_customNewRootLabel;
            }
            else if ( mountPoint == "/home" )
            {
                firstLine = tr( "Home" );
            }
            else if ( mountPoint == "/boot" )
            {
                firstLine = tr( "Boot" );
            }
            else if ( mountPoint.contains( "/efi" )
                      && index.data( PartitionModel::FileSystemTypeRole ).toInt() == FileSystem::Fat32 )
            {
                firstLine = tr( "EFI system" );
            }
            else if ( index.data( PartitionModel::FileSystemTypeRole ).toInt() == FileSystem::LinuxSwap )
            {
                firstLine = tr( "Swap" );
            }
            else if ( !mountPoint.isEmpty() )
            {
                firstLine = tr( "New partition for %1" ).arg( mountPoint );
            }
            else
            {
                firstLine = tr( "New partition" );
            }
        }
    }
    else if ( index.data( PartitionModel::OsproberNameRole ).toString().isEmpty() )
    {
        firstLine = index.data().toString();
        if ( firstLine.startsWith( "/dev/" ) )
        {
            firstLine.remove( 0, 5 );  // "/dev/"
        }
    }
    else
    {
        firstLine = index.data( PartitionModel::OsproberNameRole ).toString();
    }

    if ( index.data( PartitionModel::IsFreeSpaceRole ).toBool()
         || index.data( PartitionModel::FileSystemTypeRole ).toInt() == FileSystem::Extended )
    {
        secondLine = index.sibling( index.row(), PartitionModel::SizeColumn ).data().toString();
    }
    else
        //: size[number]  filesystem[name]
        secondLine = tr( "%1  %2" )
                         .arg( index.sibling( index.row(), PartitionModel::SizeColumn ).data().toString() )
                         .arg( index.sibling( index.row(), PartitionModel::FileSystemColumn ).data().toString() );

    return { firstLine, secondLine };
}


void
PartitionLabelsView::drawLabels( QPainter* painter, const QRect& rect, const QModelIndex& parent )
{
    PartitionModel* modl = qobject_cast< PartitionModel* >( model() );
    if ( !modl )
    {
        return;
    }

    const QModelIndexList indexesToDraw = getIndexesToDraw( parent );

    int label_x = rect.x();
    int label_y = rect.y();
    for ( const QModelIndex& index : indexesToDraw )
    {
        QStringList texts = buildTexts( index );

        QSize labelSize = sizeForLabel( texts );

        QColor labelColor = index.data( Qt::DecorationRole ).value< QColor >();

        if ( label_x + labelSize.width() > rect.width() )  //wrap to new line if overflow
        {
            label_x = rect.x();
            label_y += labelSize.height() + labelSize.height() / 4;
        }

        // Draw hover
        if ( selectionMode() != QAbstractItemView::NoSelection &&  // no hover without selection
             m_hoveredIndex.isValid() && index == m_hoveredIndex )
        {
            painter->save();
            QRect labelRect( QPoint( label_x, label_y ), labelSize );
            labelRect.adjust( 0, -LAYOUT_MARGIN, 0, -2 * LAYOUT_MARGIN );
            painter->translate( 0.5, 0.5 );
            QRect hoverRect = labelRect.adjusted( 0, 0, -1, -1 );
            painter->setBrush( QPalette().window().color().lighter( 102 ) );
            painter->setPen( Qt::NoPen );
            painter->drawRoundedRect( hoverRect, CORNER_RADIUS, CORNER_RADIUS );

            painter->translate( -0.5, -0.5 );
            painter->restore();
        }

        // Is this element the selected one?
        bool sel = selectionMode() != QAbstractItemView::NoSelection && index.isValid() && selectionModel()
            && !selectionModel()->selectedIndexes().isEmpty() && selectionModel()->selectedIndexes().first() == index;

        drawLabel( painter, texts, labelColor, QPoint( label_x, label_y ), sel );

        label_x += labelSize.width() + LABELS_MARGIN;
    }

    if ( !modl->rowCount() && !modl->device()->partitionTable() )  // No disklabel or unknown
    {
        QStringList texts = buildUnknownDisklabelTexts( modl->device() );
        QColor labelColor = ColorUtils::unknownDisklabelColor();
        drawLabel( painter, texts, labelColor, QPoint( rect.x(), rect.y() ), false /*can't be selected*/ );
    }
}


QSize
PartitionLabelsView::sizeForAllLabels( int maxLineWidth ) const
{
    PartitionModel* modl = qobject_cast< PartitionModel* >( model() );
    if ( !modl )
    {
        return QSize();
    }

    const QModelIndexList indexesToDraw = getIndexesToDraw( QModelIndex() );

    int lineLength = 0;
    int numLines = 1;
    int singleLabelHeight = 0;
    for ( const QModelIndex& index : indexesToDraw )
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

    if ( !modl->rowCount() && !modl->device()->partitionTable() )  // Unknown or no disklabel
    {
        singleLabelHeight = sizeForLabel( buildUnknownDisklabelTexts( modl->device() ) ).height();
    }

    int totalHeight = numLines * singleLabelHeight + ( numLines - 1 ) * singleLabelHeight / 4;  //spacings

    return QSize( maxLineWidth, totalHeight );
}


QSize
PartitionLabelsView::sizeForLabel( const QStringList& text ) const
{
    int vertOffset = 0;
    int width = 0;
    for ( const QString& textLine : text )
    {
        QSize textSize = fontMetrics().size( Qt::TextSingleLine, textLine );

        vertOffset += textSize.height();
        width = qMax( width, textSize.width() );
    }
    width += LABEL_PARTITION_SQUARE_MARGIN;  //for the color square
    return QSize( width, vertOffset );
}


void
PartitionLabelsView::drawLabel( QPainter* painter,
                                const QStringList& text,
                                const QColor& color,
                                const QPoint& pos,
                                bool selected )
{
    painter->setPen( Qt::black );
    int vertOffset = 0;
    int width = 0;
    for ( const QString& textLine : text )
    {
        QSize textSize = painter->fontMetrics().size( Qt::TextSingleLine, textLine );
        painter->drawText(
            pos.x() + LABEL_PARTITION_SQUARE_MARGIN, pos.y() + vertOffset + textSize.height() / 2, textLine );
        vertOffset += textSize.height();
        painter->setPen( Qt::gray );
        width = qMax( width, textSize.width() );
    }

    QRect partitionSquareRect(
        pos.x(), pos.y() - 3, LABEL_PARTITION_SQUARE_MARGIN - 5, LABEL_PARTITION_SQUARE_MARGIN - 5 );
    drawPartitionSquare( painter, partitionSquareRect, color );

    if ( selected )
    {
        drawSelectionSquare( painter, partitionSquareRect.adjusted( 2, 2, -2, -2 ), color );
    }

    painter->setPen( Qt::black );
}


QModelIndex
PartitionLabelsView::indexAt( const QPoint& point ) const
{
    PartitionModel* modl = qobject_cast< PartitionModel* >( model() );
    if ( !modl )
    {
        return QModelIndex();
    }

    const QModelIndexList indexesToDraw = getIndexesToDraw( QModelIndex() );

    QRect rect = this->rect();
    int label_x = rect.x();
    int label_y = rect.y();
    for ( const QModelIndex& index : indexesToDraw )
    {
        QStringList texts = buildTexts( index );

        QSize labelSize = sizeForLabel( texts );

        if ( label_x + labelSize.width() > rect.width() )  //wrap to new line if overflow
        {
            label_x = rect.x();
            label_y += labelSize.height() + labelSize.height() / 4;
        }

        QRect labelRect( QPoint( label_x, label_y ), labelSize );
        if ( labelRect.contains( point ) )
        {
            return index;
        }

        label_x += labelSize.width() + LABELS_MARGIN;
    }

    return QModelIndex();
}


QRect
PartitionLabelsView::visualRect( const QModelIndex& idx ) const
{
    PartitionModel* modl = qobject_cast< PartitionModel* >( model() );
    if ( !modl )
    {
        return QRect();
    }

    const QModelIndexList indexesToDraw = getIndexesToDraw( QModelIndex() );

    QRect rect = this->rect();
    int label_x = rect.x();
    int label_y = rect.y();
    for ( const QModelIndex& index : indexesToDraw )
    {
        QStringList texts = buildTexts( index );

        QSize labelSize = sizeForLabel( texts );

        if ( label_x + labelSize.width() > rect.width() )  //wrap to new line if overflow
        {
            label_x = rect.x();
            label_y += labelSize.height() + labelSize.height() / 4;
        }

        if ( idx.isValid() && idx == index )
        {
            return QRect( QPoint( label_x, label_y ), labelSize );
        }

        label_x += labelSize.width() + LABELS_MARGIN;
    }

    return QRect();
}


QRegion
PartitionLabelsView::visualRegionForSelection( const QItemSelection& selection ) const
{
    Q_UNUSED( selection )

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
    Q_UNUSED( index )
    Q_UNUSED( hint )
}


void
PartitionLabelsView::setCustomNewRootLabel( const QString& text )
{
    m_customNewRootLabel = text;
    viewport()->repaint();
}


void
PartitionLabelsView::setSelectionModel( QItemSelectionModel* selectionModel )
{
    QAbstractItemView::setSelectionModel( selectionModel );
    connect( selectionModel, &QItemSelectionModel::selectionChanged, this, [=] { viewport()->repaint(); } );
}


void
PartitionLabelsView::setSelectionFilter( SelectionFilter canBeSelected )
{
    m_canBeSelected = canBeSelected;
}


void
PartitionLabelsView::setExtendedPartitionHidden( bool hidden )
{
    m_extendedPartitionHidden = hidden;
}


QModelIndex
PartitionLabelsView::moveCursor( CursorAction cursorAction, Qt::KeyboardModifiers modifiers )
{
    Q_UNUSED( cursorAction )
    Q_UNUSED( modifiers )

    return QModelIndex();
}


bool
PartitionLabelsView::isIndexHidden( const QModelIndex& index ) const
{
    Q_UNUSED( index )

    return false;
}


void
PartitionLabelsView::setSelection( const QRect& rect, QItemSelectionModel::SelectionFlags flags )
{
    QModelIndex eventIndex = indexAt( rect.topLeft() );
    if ( m_canBeSelected( eventIndex ) )
    {
        selectionModel()->select( eventIndex, flags );
    }
}


void
PartitionLabelsView::mouseMoveEvent( QMouseEvent* event )
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
        if ( m_hoveredIndex.isValid() && !m_canBeSelected( m_hoveredIndex ) )
        {
            QGuiApplication::setOverrideCursor( Qt::ForbiddenCursor );
        }
        else
        {
            QGuiApplication::restoreOverrideCursor();
        }

        viewport()->repaint();
    }
}


void
PartitionLabelsView::leaveEvent( QEvent* event )
{
    Q_UNUSED( event )

    QGuiApplication::restoreOverrideCursor();
    if ( m_hoveredIndex.isValid() )
    {
        m_hoveredIndex = QModelIndex();
        viewport()->repaint();
    }
}


void
PartitionLabelsView::mousePressEvent( QMouseEvent* event )
{
    QModelIndex candidateIndex = indexAt( event->pos() );
    if ( m_canBeSelected( candidateIndex ) )
    {
        QAbstractItemView::mousePressEvent( event );
    }
    else
    {
        event->accept();
    }
}


void
PartitionLabelsView::updateGeometries()
{
    updateGeometry();  //get a new rect() for redrawing all the labels
}
