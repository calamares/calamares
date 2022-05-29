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
#include "CalamaresAbout.h"
#include "CalamaresVersion.h"
#include "GlobalStorage.h"
#include "Job.h"
#include "JobQueue.h"
#include "Settings.h"
#include "VariantModel.h"
#include "modulesystem/Module.h"
#include "modulesystem/ModuleManager.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"
#include "utils/Paste.h"
#include "utils/Retranslator.h"
#include "widgets/TranslationFix.h"

#include <QMessageBox>
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
    connect( gs,
             &GlobalStorage::changed,
             this,
             [ = ]
             {
                 m_globals = JobQueue::instance()->globalStorage()->data();
                 m_globals_model->reload();
                 m_ui->globalStorageView->expandAll();
             } );

    // JobQueue page
    m_ui->jobQueueText->setReadOnly( true );
    connect( JobQueue::instance(),
             &JobQueue::queueChanged,
             this,
             [ this ]( const QStringList& jobs ) { m_ui->jobQueueText->setText( jobs.join( '\n' ) ); } );

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

    connect( m_ui->modulesListView->selectionModel(),
             &QItemSelectionModel::selectionChanged,
             this,
             [this] {
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
                 }
             } );

    // Tools page
    connect( m_ui->crashButton, &QPushButton::clicked, this, [] { ::crash(); } );
    connect( m_ui->reloadStylesheetButton,
             &QPushButton::clicked,
             []()
             {
                 for ( auto* w : qApp->topLevelWidgets() )
                 {
                     // Needs to match what's set in CalamaresWindow
                     if ( w->objectName() == QStringLiteral( "mainApp" ) )
                     {
                         w->setStyleSheet( Calamares::Branding::instance()->stylesheet() );
                     }
                 }
             } );
    connect( m_ui->widgetTreeButton,
             &QPushButton::clicked,
             []()
             {
                 for ( auto* w : qApp->topLevelWidgets() )
                 {
                     Logger::CDebug deb;
                     dumpWidgetTree( deb, w, 0 );
                 }
             } );

    // Send Log button only if it would be useful
    m_ui->sendLogButton->setVisible( CalamaresUtils::Paste::isEnabled() );
    connect( m_ui->sendLogButton, &QPushButton::clicked, [ this ]() { CalamaresUtils::Paste::doLogUploadUI( this ); } );

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
        connect( m_debugWindow.data(),
                 &Calamares::DebugWindow::closed,
                 this,
                 [ = ]()
                 {
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

void
DebugWindowManager::about()
{
    QString title = Calamares::Settings::instance()->isSetupMode()
        ? QCoreApplication::translate( "WelcomePage", "About %1 setup" )
        : QCoreApplication::translate( "WelcomePage", "About %1 installer" );
    QMessageBox mb( QMessageBox::Information,
                    title.arg( CALAMARES_APPLICATION_NAME ),
                    Calamares::aboutString().arg( Calamares::Branding::instance()->versionedName() ),
                    QMessageBox::Ok,
                    nullptr );
    Calamares::fixButtonLabels( &mb );
    mb.setIconPixmap( CalamaresUtils::defaultPixmap(
        CalamaresUtils::Squid,
        CalamaresUtils::Original,
        QSize( CalamaresUtils::defaultFontHeight() * 6, CalamaresUtils::defaultFontHeight() * 6 ) ) );
    QGridLayout* layout = reinterpret_cast< QGridLayout* >( mb.layout() );
    if ( layout )
    {
        layout->setColumnMinimumWidth( 2, CalamaresUtils::defaultFontHeight() * 24 );
    }
    mb.exec();
}

}  // namespace Calamares
