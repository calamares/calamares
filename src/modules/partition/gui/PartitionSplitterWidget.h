/* === This file is part of Calamares - <https://github.com/calamares> ===
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

#ifndef PARTITIONSPLITTERWIDGET_H
#define PARTITIONSPLITTERWIDGET_H

#include <QWidget>

#include <functional>

class Device;

struct PartitionSplitterItem
{
    enum Status
    {
        Normal = 0,
        Resizing,
        ResizingNext
    };

    QString itemPath;
    QColor color;
    bool isFreeSpace;
    qint64 size;
    Status status;

    using ChildVector = QVector< PartitionSplitterItem >;
    ChildVector children;

    static PartitionSplitterItem null() { return { QString(), QColor(), false, 0, Normal, ChildVector() }; }

    bool isNull() const { return itemPath.isEmpty() && size == 0 && status == Normal; }
    operator bool() const { return !isNull(); }
};

class PartitionSplitterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PartitionSplitterWidget( QWidget* parent = nullptr );

    void init( Device* dev, bool drawNestedPartitions );

    void setSplitPartition( const QString& path,
                            qint64 minSize,
                            qint64 maxSize,
                            qint64 preferredSize );

    qint64 splitPartitionSize() const;
    qint64 newPartitionSize() const;

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

signals:
    void partitionResized( const QString&, qint64, qint64 );

protected:
    void paintEvent( QPaintEvent* event ) override;
    void mousePressEvent( QMouseEvent* event ) override;
    void mouseMoveEvent( QMouseEvent* event ) override;
    void mouseReleaseEvent( QMouseEvent* event ) override;

private:
    void setupItems( const QVector< PartitionSplitterItem >& items );

    void drawPartitions( QPainter* painter,
                         const QRect& rect,
                         const QVector< PartitionSplitterItem >& itemList );
    void drawSection( QPainter* painter, const QRect& rect_, int x, int width,
                      const PartitionSplitterItem& item );
    void drawResizeHandle( QPainter* painter,
                           const QRect& rect_,
                           int x );

    PartitionSplitterItem _findItem( QVector< PartitionSplitterItem >& items,
                                     std::function< bool ( PartitionSplitterItem& ) > condition ) const;

    int _eachItem( QVector< PartitionSplitterItem >& items,
                   std::function< bool ( PartitionSplitterItem& ) > operation ) const;

    QPair< QVector< PartitionSplitterItem >, qreal >
    computeItemsVector( const QVector< PartitionSplitterItem >& originalItems ) const;

    QVector< PartitionSplitterItem > m_items;
    QString m_itemToResizePath;
    PartitionSplitterItem m_itemToResize;
    PartitionSplitterItem m_itemToResizeNext;

    qint64 m_itemMinSize;
    qint64 m_itemMaxSize;
    qint64 m_itemPrefSize;
    bool m_resizing;
    int m_resizeHandleX;

    const int HANDLE_SNAP;

    bool m_drawNestedPartitions;
};

#endif // PARTITIONSPLITTERWIDGET_H
