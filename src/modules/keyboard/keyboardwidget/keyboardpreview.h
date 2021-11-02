/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2007 Free Software Foundation, Inc.
 *   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Portions from the Manjaro Installation Framework
 *   by Roland Singer <roland@manjaro.org>
 *   Copyright (C) 2007 Free Software Foundation, Inc.
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef KEYBOARDPREVIEW_H
#define KEYBOARDPREVIEW_H

#include <QColor>
#include <QFont>
#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include <QPixmap>
#include <QRectF>
#include <QString>
#include <QStringList>
#include <QWidget>


class KeyBoardPreview : public QWidget
{
    Q_OBJECT
public:
    explicit KeyBoardPreview( QWidget* parent = nullptr );

    void setLayout( QString layout );
    void setVariant( QString variant );

private:
    enum KB_TYPE
    {
        KB_104,
        KB_105,
        KB_106
    };

    struct KB
    {
        bool kb_extended_return;
        QList< QList< int > > keys;
    };

    struct Code
    {
        QString plain, shift, ctrl, alt;
    };

    QString layout, variant;
    QFont lowerFont, upperFont;
    KB *kb, kbList[ 3 ];
    QList< Code > codes;
    int space, usable_width, key_w;

    void loadInfo();
    bool loadCodes();
    QString regular_text( int index );
    QString shift_text( int index );
    QString ctrl_text( int index );
    QString alt_text( int index );
    QString fromUnicodeString( QString raw );

protected:
    void paintEvent( QPaintEvent* event ) override;
    void resizeEvent( QResizeEvent* event ) override;
};

#endif  // KEYBOARDPREVIEW_H
