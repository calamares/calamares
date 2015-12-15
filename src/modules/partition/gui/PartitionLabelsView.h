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

#ifndef PARTITIONLABELSVIEW_H
#define PARTITIONLABELSVIEW_H

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
public:
    explicit PartitionLabelsView( QWidget* parent = nullptr );
    virtual ~PartitionLabelsView();

    QSize minimumSizeHint() const override;

    QSize sizeHint() const override;

    void paintEvent( QPaintEvent* event ) override;

    // QAbstractItemView API
    QModelIndex indexAt( const QPoint& point ) const override;
    QRect visualRect( const QModelIndex& index ) const override;
    void scrollTo( const QModelIndex& index, ScrollHint hint = EnsureVisible ) override;

    void setLabelsVisible( bool visible = true );

protected:
    // QAbstractItemView API
    QRegion visualRegionForSelection( const QItemSelection& selection ) const override;
    int horizontalOffset() const override;
    int verticalOffset() const override;
    bool isIndexHidden( const QModelIndex& index ) const override;
    QModelIndex moveCursor( CursorAction cursorAction, Qt::KeyboardModifiers modifiers ) override;
    void setSelection( const QRect& rect, QItemSelectionModel::SelectionFlags flags ) override;

protected slots:
    void updateGeometries() override;

private:
    void drawLabels( QPainter* painter, const QRect& rect, const QModelIndex& parent );
    QSize sizeForAllLabels( int maxLineWidth ) const;
    QSize sizeForLabel( const QStringList& text ) const;
    void drawLabel( QPainter* painter, const QStringList& text, const QColor& color, const QPoint& pos );
    QModelIndexList getIndexesToDraw( const QModelIndex& parent ) const;
    QStringList buildTexts( const QModelIndex& index ) const;
};

#endif // PARTITIONLABELSVIEW_H
