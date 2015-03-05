/* === This file is part of Calamares - <http://github.com/calamares> ===
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

#include "DebugWindow.h"
#include "utils/Retranslator.h"
#include "utils/qjsonmodel.h"
#include "JobQueue.h"
#include "GlobalStorage.h"

#include <QJsonDocument>
#include <QTreeView>

namespace Calamares {

DebugWindow::DebugWindow()
    : QWidget( nullptr )
{

    setupUi( this );

    QJsonModel* jsonModel = new QJsonModel( this );

    globalStorageView->setModel( jsonModel );
    GlobalStorage* gs = JobQueue::instance()->globalStorage();

    connect( gs, &GlobalStorage::changed, [ jsonModel, gs ]
    {
        jsonModel->loadJson( QJsonDocument::fromVariant( gs->m ).toJson() );
    } );
    jsonModel->loadJson( QJsonDocument::fromVariant( gs->m ).toJson() );


    CALAMARES_RETRANSLATE( retranslateUi( this ); )
}


void
DebugWindow::closeEvent( QCloseEvent* e )
{
    Q_UNUSED( e )
    emit closed();
}

} // namespace Calamares
