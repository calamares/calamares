/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2015-2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "DebugWindow.h"
#include "ui_DebugWindow.h"

#include "Branding.h"
#include "GlobalStorage.h"
#include "Job.h"
#include "JobQueue.h"
#include "Settings.h"
#include "VariantModel.h"
#include "modulesystem/Module.h"
#include "modulesystem/ModuleManager.h"
#include "utils/Logger.h"
#include "utils/Paste.h"
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
    deb << widget->metaObject()->className() << widget->objectName();

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
    connect( JobQueue::instance(), &JobQueue::queueChanged, this, [this]( const QStringList& jobs ) {
        m_ui->jobQueueText->setText( jobs.join( '\n' ) );
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
                 Module* module
                     = ModuleManager::instance()->moduleInstance( ModuleSystem::InstanceKey::fromString( moduleName ) );
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

    // Send Log button only if it would be useful
    m_ui->sendLogButton->setVisible( CalamaresUtils::Paste::isEnabled() );
    connect( m_ui->sendLogButton, &QPushButton::clicked, [this]() { CalamaresUtils::Paste::doLogUploadUI( this ); } );

    CALAMARES_RETRANSLATE( m_ui->retranslateUi( this ); setWindowTitle( tr( "Debug information" ) ); );
}


void
DebugWindow::closeEvent( QCloseEvent* e )
{
    Q_UNUSED( e )
    emit closed();
}


DebugWindowManager::DebugWindowManager( QObject* parent )
    : QObject( parent )
{
}


bool
DebugWindowManager::enabled() const
{
    const auto* s = Settings::instance();
    return ( Logger::logLevel() >= Logger::LOGVERBOSE ) || ( s ? s->debugMode() : false );
}


void
DebugWindowManager::show( bool visible )
{
    if ( !enabled() )
    {
        visible = false;
    }
    if ( m_visible == visible )
    {
        return;
    }

    if ( visible )
    {
        m_debugWindow = new Calamares::DebugWindow();
        m_debugWindow->show();
        connect( m_debugWindow.data(), &Calamares::DebugWindow::closed, this, [=]() {
            m_debugWindow->deleteLater();
            m_visible = false;
            emit visibleChanged( false );
        } );
        m_visible = true;
        emit visibleChanged( true );
    }
    else
    {
        if ( m_debugWindow )
        {
            m_debugWindow->deleteLater();
        }
        m_visible = false;
        emit visibleChanged( false );
    }
}

void
DebugWindowManager::toggle()
{
    show( !m_visible );
}


}  // namespace Calamares
