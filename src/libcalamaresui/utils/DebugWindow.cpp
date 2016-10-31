/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2015-2016, Teo Mrnjavac <teo@kde.org>
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
#include "utils/CalamaresUtils.h"
#include "utils/Retranslator.h"
#include "utils/qjsonmodel.h"
#include "JobQueue.h"
#include "Job.h"
#include "GlobalStorage.h"
#include "modulesystem/ModuleManager.h"
#include "modulesystem/Module.h"

#ifdef WITH_PYTHONQT
#include <gui/PythonQtScriptingConsole.h>
#include "ViewManager.h"
#include "viewpages/PythonQtViewStep.h"
#endif

#include <QJsonDocument>
#include <QSplitter>
#include <QStringListModel>
#include <QTreeView>

namespace Calamares {

DebugWindow::DebugWindow()
    : QWidget( nullptr )
{
    setupUi( this );

    // GlobalStorage page
    QJsonModel* jsonModel = new QJsonModel( this );

    globalStorageView->setModel( jsonModel );
    GlobalStorage* gs = JobQueue::instance()->globalStorage();

    connect( gs, &GlobalStorage::changed,
             this, [ = ]
    {
        jsonModel->loadJson( QJsonDocument::fromVariant( gs->m ).toJson() );
        globalStorageView->expandAll();
    } );
    jsonModel->loadJson( QJsonDocument::fromVariant( gs->m ).toJson() );
    globalStorageView->expandAll();

    // JobQueue page
    jobQueueText->setReadOnly( true );
    connect( JobQueue::instance(), &JobQueue::queueChanged,
             this, [ this ]( const QList< Calamares::job_ptr >& jobs )
    {
        QStringList text;
        for ( const auto &job : jobs )
        {
            text.append( job->prettyName() );
        }

        jobQueueText->setText( text.join( '\n' ) );
    } );

    // Modules page
    QStringListModel* modulesModel = new QStringListModel( ModuleManager::instance()->loadedInstanceKeys() );
    modulesListView->setModel( modulesModel );
    modulesListView->setSelectionMode( QAbstractItemView::SingleSelection );

    QJsonModel* moduleConfigModel = new QJsonModel( this );
    moduleConfigView->setModel( moduleConfigModel );

#ifdef WITH_PYTHONQT
    QPushButton* pythonConsoleButton = new QPushButton;
    pythonConsoleButton->setText( "Attach Python console" );
    modulesVerticalLayout->insertWidget( 1, pythonConsoleButton );
    pythonConsoleButton->hide();

    QObject::connect( pythonConsoleButton, &QPushButton::clicked,
                      this, [ this, moduleConfigModel ]
    {
        QString moduleName = modulesListView->currentIndex().data().toString();
        Module* module = ModuleManager::instance()->moduleInstance( moduleName );
        if ( module->interface() != Module::PythonQtInterface ||
             module->type() != Module::View )
            return;

        for ( ViewStep* step : ViewManager::instance()->viewSteps() )
        {
            if ( step->moduleInstanceKey() == module->instanceKey() )
            {
                PythonQtViewStep* pqvs =
                    qobject_cast< PythonQtViewStep* >( step );
                if ( pqvs )
                {
                    QWidget* consoleWindow = new QWidget;

                    QWidget* console = pqvs->createScriptingConsole();
                    console->setParent( consoleWindow );

                    QVBoxLayout* layout = new QVBoxLayout;
                    consoleWindow->setLayout( layout );
                    layout->addWidget( console );

                    QHBoxLayout* bottomLayout = new QHBoxLayout;
                    layout->addLayout( bottomLayout );

                    QLabel* bottomLabel = new QLabel( consoleWindow );
                    bottomLayout->addWidget( bottomLabel );
                    QString line =
                        QString( "Module: <font color=\"#008000\"><code>%1</code></font><br/>"
                                 "Python class: <font color=\"#008000\"><code>%2</code></font>" )
                            .arg( module->instanceKey() )
                            .arg( console->property( "classname" ).toString() );
                    bottomLabel->setText( line );

                    QPushButton* closeButton = new QPushButton( consoleWindow );
                    closeButton->setText( "&Close" );
                    QObject::connect( closeButton, &QPushButton::clicked,
                                      [ consoleWindow ]
                    {
                        consoleWindow->close();
                    } );
                    bottomLayout->addWidget( closeButton );
                    bottomLabel->setSizePolicy( QSizePolicy::Expanding,
                                                QSizePolicy::Preferred );

                    consoleWindow->setParent( this );
                    consoleWindow->setWindowFlags( Qt::Window );
                    consoleWindow->setWindowTitle( "Calamares Python console" );
                    consoleWindow->setAttribute( Qt::WA_DeleteOnClose, true );
                    consoleWindow->showNormal();
                    break;
                }
            }
        }
    } );

#endif

    connect( modulesListView->selectionModel(), &QItemSelectionModel::selectionChanged,
             this, [ this, moduleConfigModel
#ifdef WITH_PYTHONQT
             , pythonConsoleButton
#endif
             ]
    {
        QString moduleName = modulesListView->currentIndex().data().toString();
        Module* module = ModuleManager::instance()->moduleInstance( moduleName );
        if ( module )
        {
            moduleConfigModel->loadJson( QJsonDocument::fromVariant( module->configurationMap() ).toJson() );
            moduleConfigView->expandAll();
            moduleTypeLabel->setText( module->typeString() );
            moduleInterfaceLabel->setText( module->interfaceString() );
#ifdef WITH_PYTHONQT
            pythonConsoleButton->setVisible(
                        module->interface() == Module::PythonQtInterface &&
                        module->type() == Module::View );
#endif
        }
    } );

    connect( crashButton, &QPushButton::clicked,
             this, [] {
        CalamaresUtils::crash();
    } );

    CALAMARES_RETRANSLATE(
        retranslateUi( this );
        setWindowTitle( tr( "Debug information" ) );
    )
}


void
DebugWindow::closeEvent( QCloseEvent* e )
{
    Q_UNUSED( e )
    emit closed();
}

} // namespace Calamares
