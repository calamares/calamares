/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2015-2016, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2019, Adriaan de Groot <groot@kde.org>
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
#include "ui_DebugWindow.h"

#include "VariantModel.h"

#include "Branding.h"
#include "modulesystem/Module.h"
#include "modulesystem/ModuleManager.h"

#include "GlobalStorage.h"
#include "Job.h"
#include "JobQueue.h"
#include "utils/Logger.h"
#include "utils/Retranslator.h"

#ifdef WITH_PYTHONQT
#include "ViewManager.h"
#include "viewpages/PythonQtViewStep.h"

#include <gui/PythonQtScriptingConsole.h>
#endif

#include <QSplitter>
#include <QStringListModel>
#include <QTreeView>
#include <QWidget>

/**
 * @brief crash makes Calamares crash immediately.
 */
static void
crash()
{
    volatile int* a = nullptr;
    *a = 1;
}

/// @brief Print out the widget tree (names) in indented form.
static void
dumpWidgetTree( QDebug& deb, const QWidget* widget, int depth )
{
    if ( !widget )
    {
        return;
    }

    deb << Logger::Continuation;
    for ( int i = 0; i < depth; ++i )
    {
        deb << ' ';
    }
    deb << widget->objectName();

    for ( const auto* w : widget->findChildren< QWidget* >( QString(), Qt::FindDirectChildrenOnly ) )
    {
        dumpWidgetTree( deb, w, depth + 1 );
    }
}

namespace Calamares
{

DebugWindow::DebugWindow()
    : QWidget( nullptr )
    , m_ui( new Ui::DebugWindow )
    , m_globals( JobQueue::instance()->globalStorage()->data() )
    , m_globals_model( std::make_unique< VariantModel >( &m_globals ) )
    , m_module_model( std::make_unique< VariantModel >( &m_module ) )
{
    GlobalStorage* gs = JobQueue::instance()->globalStorage();

    m_ui->setupUi( this );

    m_ui->globalStorageView->setModel( m_globals_model.get() );
    m_ui->globalStorageView->expandAll();

    // Do above when the GS changes, too
    connect( gs, &GlobalStorage::changed, this, [=] {
        m_globals = JobQueue::instance()->globalStorage()->data();
        m_globals_model->reload();
        m_ui->globalStorageView->expandAll();
    } );

    // JobQueue page
    m_ui->jobQueueText->setReadOnly( true );
    connect( JobQueue::instance(), &JobQueue::queueChanged, this, [this]( const JobList& jobs ) {
        QStringList text;
        for ( const auto& job : jobs )
        {
            text.append( job->prettyName() );
        }

        m_ui->jobQueueText->setText( text.join( '\n' ) );
    } );

    // Modules page
    QStringList modulesKeys;
    for ( const auto& m : ModuleManager::instance()->loadedInstanceKeys() )
    {
        modulesKeys << m.toString();
    }

    QStringListModel* modulesModel = new QStringListModel( modulesKeys );
    m_ui->modulesListView->setModel( modulesModel );
    m_ui->modulesListView->setSelectionMode( QAbstractItemView::SingleSelection );

    m_ui->moduleConfigView->setModel( m_module_model.get() );

#ifdef WITH_PYTHONQT
    QPushButton* pythonConsoleButton = new QPushButton;
    pythonConsoleButton->setText( "Attach Python console" );
    m_ui->modulesVerticalLayout->insertWidget( 1, pythonConsoleButton );
    pythonConsoleButton->hide();

    QObject::connect( pythonConsoleButton, &QPushButton::clicked, this, [this, moduleConfigModel] {
        QString moduleName = m_ui->modulesListView->currentIndex().data().toString();
        Module* module = ModuleManager::instance()->moduleInstance( moduleName );
        if ( module->interface() != Module::Interface::PythonQt || module->type() != Module::Type::View )
            return;

        for ( ViewStep* step : ViewManager::instance()->viewSteps() )
        {
            if ( step->moduleInstanceKey() == module->instanceKey() )
            {
                PythonQtViewStep* pqvs = qobject_cast< PythonQtViewStep* >( step );
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
                    QString line = QString( "Module: <font color=\"#008000\"><code>%1</code></font><br/>"
                                            "Python class: <font color=\"#008000\"><code>%2</code></font>" )
                                       .arg( module->instanceKey() )
                                       .arg( console->property( "classname" ).toString() );
                    bottomLabel->setText( line );

                    QPushButton* closeButton = new QPushButton( consoleWindow );
                    closeButton->setText( "&Close" );
                    QObject::connect( closeButton, &QPushButton::clicked, [consoleWindow] { consoleWindow->close(); } );
                    bottomLayout->addWidget( closeButton );
                    bottomLabel->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Preferred );

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

    connect( m_ui->modulesListView->selectionModel(),
             &QItemSelectionModel::selectionChanged,
             this,
             [this
#ifdef WITH_PYTHONQT
              ,
              pythonConsoleButton
#endif
    ] {
                 QString moduleName = m_ui->modulesListView->currentIndex().data().toString();
                 Module* module = ModuleManager::instance()->moduleInstance( moduleName );
                 if ( module )
                 {
                     m_module = module->configurationMap();
                     m_module_model->reload();
                     m_ui->moduleConfigView->expandAll();
                     m_ui->moduleTypeLabel->setText( module->typeString() );
                     m_ui->moduleInterfaceLabel->setText( module->interfaceString() );
#ifdef WITH_PYTHONQT
                     pythonConsoleButton->setVisible( module->interface() == Module::Interface::PythonQt
                                                      && module->type() == Module::Type::View );
#endif
                 }
             } );

    // Tools page
    connect( m_ui->crashButton, &QPushButton::clicked, this, [] { ::crash(); } );
    connect( m_ui->reloadStylesheetButton, &QPushButton::clicked, []() {
        for ( auto* w : qApp->topLevelWidgets() )
        {
            // Needs to match what's set in CalamaresWindow
            if ( w->objectName() == QStringLiteral( "mainApp" ) )
            {
                w->setStyleSheet( Calamares::Branding::instance()->stylesheet() );
            }
        }
    } );
    connect( m_ui->widgetTreeButton, &QPushButton::clicked, []() {
        for ( auto* w : qApp->topLevelWidgets() )
        {
            Logger::CDebug deb;
            dumpWidgetTree( deb, w, 0 );
        }
    } );

    CALAMARES_RETRANSLATE( m_ui->retranslateUi( this ); setWindowTitle( tr( "Debug information" ) ); )
}


void
DebugWindow::closeEvent( QCloseEvent* e )
{
    Q_UNUSED( e )
    emit closed();
}

}  // namespace Calamares
