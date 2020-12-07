/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2015-2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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
    ~PartitionBarsView() override;

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
