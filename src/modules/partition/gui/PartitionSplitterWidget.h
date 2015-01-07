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

#ifndef PARTITIONSPLITTERWIDGET_H
#define PARTITIONSPLITTERWIDGET_H

#include <QWidget>


struct PartitionSplitterItem
{
    QString itemPath;
    QColor color;
    bool isFreeSpace;
    qint64 size;

    QList< PartitionSplitterItem > children;
};

class PartitionSplitterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PartitionSplitterWidget( QWidget* parent = nullptr );

    void init( const QList< PartitionSplitterItem >& items );

    void setSplitPartition( const QString& path,
                            qint64 minSize,
                            qint64 maxSize,
                            qint64 preferredSize,
                            const QString& newLabel );

    qint64 splitPartitionSize() const;
    qint64 newPartitionSize() const;

    QSize sizeHint() const override;

signals:
    void partitionResized( const QString&, qint64, qint64 );

protected:
    void paintEvent( QPaintEvent* event ) override;
    void mousePressEvent( QMouseEvent* event ) override;
    void mouseMoveEvent( QMouseEvent* event ) override;
    void mouseReleaseEvent( QMouseEvent* event ) override;

private:
    void drawPartitions( QPainter* painter,
                         const QRect& rect,
                         const QList< PartitionSplitterItem >& items );
    void drawSection( QPainter* painter, const QRect& rect_, int x, int width,
                      const PartitionSplitterItem& item );
    void drawResizeHandle( QPainter* painter,
                           const QRect& rect_,
                           int x );

    template < typename F >
    PartitionSplitterItem* _findItem( QList< PartitionSplitterItem >& items,
                                      F condition );

    QList< PartitionSplitterItem > m_items;
    QString m_itemToResizePath;
    PartitionSplitterItem* m_itemToResize;
    PartitionSplitterItem* m_itemToResizeNext;

    qint64 m_itemMinSize;
    qint64 m_itemMaxSize;
    qint64 m_itemPrefSize;
    bool m_resizing;
    int m_resizeHandleX;

    const int HANDLE_SNAP;
};

#endif // PARTITIONSPLITTERWIDGET_H
