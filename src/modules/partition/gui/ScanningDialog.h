/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef SCANNINGDIALOG_H
#define SCANNINGDIALOG_H

#include <QDialog>
#include <QFuture>

#include <functional>

class ScanningDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ScanningDialog( const QString& text, const QString& windowTitle, QWidget* parent = nullptr );

    static void run(
        const QFuture< void >& future,
        const QString& text,
        const QString& windowTitle,
        const std::function< void() >& callback = [] {},
        QWidget* parent = nullptr );

    static void run(
        const QFuture< void >& future,
        const std::function< void() >& callback = [] {},
        QWidget* parent = nullptr );

public slots:
    void setVisible( bool visible ) override;

signals:
    void visibilityChanged();
};

#endif  // SCANNINGDIALOG_H
