/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
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

#include "ScanningDialog.h"

#include "widgets/waitingspinnerwidget.h"

#include <QBoxLayout>
#include <QLabel>
#include <QFutureWatcher>
#include <QtConcurrent/QtConcurrent>


ScanningDialog::ScanningDialog( const QString& text,
                                const QString& windowTitle,
                                QWidget* parent )
    : QDialog( parent )
{
    setModal( true );
    setWindowTitle( windowTitle );

    QHBoxLayout* dialogLayout = new QHBoxLayout;
    setLayout( dialogLayout );

    WaitingSpinnerWidget* spinner = new WaitingSpinnerWidget();
    dialogLayout->addWidget( spinner );
    spinner->start();

    QLabel* rescanningLabel = new QLabel( text,
                                          this );
    dialogLayout->addWidget( rescanningLabel );
}


void
ScanningDialog::run( const QFuture< void >& future,
                     const QString& text,
                     const QString& windowTitle,
                     const std::function< void() >& callback,
                     QWidget* parent )
{
    ScanningDialog* theDialog =
            new ScanningDialog( text,
                                windowTitle,
                                parent );
    theDialog->show();

    QFutureWatcher< void >* watcher = new QFutureWatcher< void >();
    connect( watcher, &QFutureWatcher< void >::finished,
             theDialog, [ watcher, theDialog, callback ]
    {
        watcher->deleteLater();
        theDialog->hide();
        theDialog->deleteLater();
        callback();
    } );

    watcher->setFuture( future );
}


void
ScanningDialog::run( const QFuture< void >& future,
                     const std::function< void() >& callback,
                     QWidget* parent )
{
    ScanningDialog::run( future,
                         tr( "Scanning storage devices..." ),
                         tr( "Partitioning" ),
                         callback,
                         parent );
}

void ScanningDialog::setVisible(bool visible)
{
    QDialog::setVisible( visible );
    emit visibilityChanged();
}
