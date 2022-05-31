/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "ScanningDialog.h"

#include "widgets/waitingspinnerwidget.h"

#include <QBoxLayout>
#include <QFutureWatcher>
#include <QLabel>
#include <QtConcurrent/QtConcurrent>


ScanningDialog::ScanningDialog( const QString& text, const QString& windowTitle, QWidget* parent )
    : QDialog( parent )
{
    setModal( true );
    setWindowTitle( windowTitle );

    QHBoxLayout* dialogLayout = new QHBoxLayout;
    setLayout( dialogLayout );

    WaitingSpinnerWidget* spinner = new WaitingSpinnerWidget();
    dialogLayout->addWidget( spinner );
    spinner->start();

    QLabel* rescanningLabel = new QLabel( text, this );
    dialogLayout->addWidget( rescanningLabel );
}


void
ScanningDialog::run( const QFuture< void >& future,
                     const QString& text,
                     const QString& windowTitle,
                     const std::function< void() >& callback,
                     QWidget* parent )
{
    ScanningDialog* theDialog = new ScanningDialog( text, windowTitle, parent );
    theDialog->show();

    QFutureWatcher< void >* watcher = new QFutureWatcher< void >();
    connect( watcher,
             &QFutureWatcher< void >::finished,
             theDialog,
             [ watcher, theDialog, callback ]
             {
                 watcher->deleteLater();
                 theDialog->hide();
                 theDialog->deleteLater();
                 callback();
             } );

    watcher->setFuture( future );
}


void
ScanningDialog::run( const QFuture< void >& future, const std::function< void() >& callback, QWidget* parent )
{
    ScanningDialog::run( future, tr( "Scanning storage devices..." ), tr( "Partitioning" ), callback, parent );
}

void
ScanningDialog::setVisible( bool visible )
{
    QDialog::setVisible( visible );
    Q_EMIT visibilityChanged();
}
