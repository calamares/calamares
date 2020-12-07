/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef FIXEDASPECTRATIOLABEL_H
#define FIXEDASPECTRATIOLABEL_H

#include <QLabel>
#include <QPixmap>

class FixedAspectRatioLabel : public QLabel
{
    Q_OBJECT
public:
    explicit FixedAspectRatioLabel( QWidget* parent = nullptr );
    ~FixedAspectRatioLabel() override;

public slots:
    void setPixmap( const QPixmap& pixmap );
    void resizeEvent( QResizeEvent* event ) override;

private:
    QPixmap m_pixmap;
};

#endif  // FIXEDASPECTRATIOLABEL_H
