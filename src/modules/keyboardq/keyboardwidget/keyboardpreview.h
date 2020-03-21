/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
 *
 *   Portions from the Manjaro Installation Framework
 *   by Roland Singer <roland@manjaro.org>
 *   Copyright (C) 2007 Free Software Foundation, Inc.
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

#ifndef KEYBOARDPREVIEW_H
#define KEYBOARDPREVIEW_H

#include <QWidget>
#include <QRectF>
#include <QFont>
#include <QPainter>
#include <QPen>
#include <QPainterPath>
#include <QColor>
#include <QPixmap>
#include <QProcess>
#include <QString>
#include <QStringList>


class KeyBoardPreview : public QWidget
{
    Q_OBJECT
public:
    explicit KeyBoardPreview( QWidget* parent = nullptr );
    
    void setLayout(QString layout);
    void setVariant(QString variant);

private:
    enum KB_TYPE { KB_104, KB_105, KB_106 };

    struct KB {
        bool kb_extended_return;
        QList<QList<int> > keys;
    };

    struct Code {
        QString plain, shift, ctrl, alt;
    };

    QString layout, variant;
    QFont lowerFont, upperFont;
    KB* kb, kbList[3];
    QList<Code> codes;
    int space, usable_width, key_w;

    void loadInfo();
    bool loadCodes();
    QString regular_text(int index);
    QString shift_text(int index);
    QString ctrl_text(int index);
    QString alt_text(int index);
    QString fromUnicodeString(QString raw);

protected:
    void paintEvent(QPaintEvent* event);
    void resizeEvent(QResizeEvent* event);

};

#endif // KEYBOARDPREVIEW_H
