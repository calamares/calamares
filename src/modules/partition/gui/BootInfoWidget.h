/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2015-2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */


#ifndef BOOTINFOWIDGET_H
#define BOOTINFOWIDGET_H

#include <QWidget>

class QLabel;

class BootInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BootInfoWidget( QWidget* parent = nullptr );

public slots:
    void retranslateUi();

private:
    QLabel* m_bootIcon;
    QLabel* m_bootLabel;
};

#endif  // BOOTINFOWIDGET_H
