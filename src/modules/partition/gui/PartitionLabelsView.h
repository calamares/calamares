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

#ifndef PARTITIONLABELSVIEW_H
#define PARTITIONLABELSVIEW_H

#include "PartitionViewSelectionFilter.h"

#include <QAbstractItemView>

/**
 * A Qt model view which displays colored labels for partitions.
 *
 * It has been created to be used with a PartitionModel instance, but does not
 * call any PartitionModel-specific methods: it should be usable with other
 * models as long as they provide the same roles PartitionModel provides.
 */
class PartitionLabelsView : public QAbstractItemView
{
    Q_OBJECT
public:
    explicit PartitionLabelsView( QWidget* parent = nullptr );
    ~PartitionLabelsView() override;

    QSize minimumSizeHint() const override;

    QSize sizeHint() const override;

    void paintEvent( QPaintEvent* event ) override;

    // QAbstractItemView API
    QModelIndex indexAt( const QPoint& point ) const override;
    QRect visualRect( const QModelIndex& idx ) const override;
    void scrollTo( const QModelIndex& index, ScrollHint hint = EnsureVisible ) override;

    void setCustomNewRootLabel( const QString& text );

    void setSelectionModel( QItemSelectionModel* selectionModel ) override;

    void setSelectionFilter( SelectionFilter canBeSelected );

    void setExtendedPartitionHidden( bool hidden );

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
    QRect labelsRect() const;
    void drawLabels( QPainter* painter, const QRect& rect, const QModelIndex& parent );
    QSize sizeForAllLabels( int maxLineWidth ) const;
    QSize sizeForLabel( const QStringList& text ) const;
    void drawLabel( QPainter* painter, const QStringList& text, const QColor& color, const QPoint& pos, bool selected );
    QModelIndexList getIndexesToDraw( const QModelIndex& parent ) const;
    QStringList buildTexts( const QModelIndex& index ) const;

    SelectionFilter m_canBeSelected;
    bool m_extendedPartitionHidden;

    QString m_customNewRootLabel;
    QPersistentModelIndex m_hoveredIndex;
};

#endif  // PARTITIONLABELSVIEW_H
