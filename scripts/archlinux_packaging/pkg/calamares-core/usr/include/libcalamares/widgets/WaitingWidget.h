/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef WAITINGWIDGET_H
#define WAITINGWIDGET_H

#include <QWidget>

class QLabel;

class WaitingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WaitingWidget( const QString& text, QWidget* parent = nullptr );

    void setText( const QString& text );

private:
    QLabel* m_waitingLabel;
};

#endif  // WAITINGWIDGET_H
