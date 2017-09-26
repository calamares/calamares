/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
 *   Copyright 2015-2016, Teo Mrnjavac <teo@kde.org>
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
#ifndef PARTITIONPREVIEW_H
#define PARTITIONPREVIEW_H

#include "PartitionViewSelectionFilter.h"

#include <QAbstractItemView>


/**
 * A Qt model view which displays the partitions inside a device as a colored bar.
 *
 * It has been created to be used with a PartitionModel instance, but does not
 * call any PartitionModel-specific methods: it should be usable with other
 * models as long as they provide the same roles PartitionModel provides.
 */
class PartitionBarsView : public QAbstractItemView
{
    Q_OBJECT
public:
    enum NestedPartitionsMode
    {
        NoNestedPartitions = 0,
        DrawNestedPartitions
    };

    explicit PartitionBarsView( QWidget* parent = nullptr );
    virtual ~PartitionBarsView() override;

    void setNestedPartitionsMode( NestedPartitionsMode mode );

    QSize minimumSizeHint() const override;

    QSize sizeHint() const override;

    void paintEvent( QPaintEvent* event ) override;

    // QAbstractItemView API
    QModelIndex indexAt( const QPoint& point ) const override;
    QRect visualRect( const QModelIndex& index ) const override;
    void scrollTo( const QModelIndex& index, ScrollHint hint = EnsureVisible ) override;

    void setSelectionModel( QItemSelectionModel* selectionModel ) override;

    void setSelectionFilter( SelectionFilter canBeSelected );

protected:
    // QAbstractItemView API
    QRegion visualRegionForSelection( const QItemSelection& selection ) const override;
    int horizontalOffset() const override;
    int verticalOffset() const override;
    bool isIndexHidden( const QModelIndex& index ) const override;
    QModelIndex moveCursor( CursorAction cursorAction, Qt::KeyboardModifiers modifiers ) override;
    void setSelection( const QRect& rect, QItemSelectionModel::SelectionFlags flags ) override;

    void mouseMoveEvent( QMouseEvent* event ) override;
    void leaveEvent( QEvent* event ) override;
    void mousePressEvent( QMouseEvent* event ) override;

protected slots:
    void updateGeometries() override;

private:
    void drawPartitions( QPainter* painter, const QRect& rect, const QModelIndex& parent );
    void drawSection( QPainter* painter, const QRect& rect_, int x, int width, const QModelIndex& index );
    QModelIndex indexAt( const QPoint& point, const QRect& rect, const QModelIndex& parent ) const;
    QRect visualRect( const QModelIndex& index, const QRect& rect, const QModelIndex& parent ) const;

    NestedPartitionsMode m_nestedPartitionsMode;

    SelectionFilter canBeSelected;

    struct Item
    {
        qreal size;
        QModelIndex index;
    };
    inline QPair< QVector< Item >, qreal > computeItemsVector( const QModelIndex& parent ) const;
    QPersistentModelIndex m_hoveredIndex;
};

#endif /* PARTITIONPREVIEW_H */
