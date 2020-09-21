/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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

    void setSplitPartition( const QString& path, qint64 minSize, qint64 maxSize, qint64 preferredSize );

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

    void drawPartitions( QPainter* painter, const QRect& rect, const QVector< PartitionSplitterItem >& itemList );
    void drawSection( QPainter* painter, const QRect& rect_, int x, int width, const PartitionSplitterItem& item );
    void drawResizeHandle( QPainter* painter, const QRect& rect_, int x );

    PartitionSplitterItem _findItem( QVector< PartitionSplitterItem >& items,
                                     std::function< bool( PartitionSplitterItem& ) > condition ) const;

    int _eachItem( QVector< PartitionSplitterItem >& items,
                   std::function< bool( PartitionSplitterItem& ) > operation ) const;

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

#endif  // PARTITIONSPLITTERWIDGET_H
