/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
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

#ifndef SCANNINGDIALOG_H
#define SCANNINGDIALOG_H

#include <QDialog>
#include <QFuture>

#include <functional>

class ScanningDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ScanningDialog( const QString& text,
                             const QString& windowTitle,
                             QWidget* parent = nullptr );

    static void run( const QFuture< void >& future,
                     const QString& text,
                     const QString& windowTitle,
                     const std::function< void() >& callback = []{},
                     QWidget* parent = nullptr );

    static void run( const QFuture< void >& future,
                     const std::function< void() >& callback = []{},
                     QWidget* parent = nullptr );

public slots:
    void setVisible( bool visible ) override;

signals:
    void visibilityChanged();
};

#endif // SCANNINGDIALOG_H
