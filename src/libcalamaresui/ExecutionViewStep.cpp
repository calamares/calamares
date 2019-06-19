/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2018, Adriaan de Groot <groot@kde.org>
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

#include <ExecutionViewStep.h>

#include "Branding.h"
#include "Job.h"
#include "JobQueue.h"
#include "modulesystem/Module.h"
#include "modulesystem/ModuleManager.h"
#include "Settings.h"
#include "ViewManager.h"

#include "utils/CalamaresUtilsGui.h"
#include "utils/Dirs.h"
#include "utils/Logger.h"
#include "utils/Retranslator.h"

#include <QDir>
#include <QLabel>
#include <QProgressBar>
#include <QQmlComponent>
#include <QQmlEngine>
#include <QQuickItem>
#include <QQuickWidget>
#include <QVBoxLayout>

/** @brief Calls the QML method @p method()
 *
 * Pass in only the name of the method (e.g. onActivate). This function
 * checks if the method exists (with no arguments) before trying to
 * call it, so that no warnings are printed due to missing methods.
 *
 * If there is a return value from the QML method, it is logged (but not otherwise used).
 */
static void
callQMLFunction( QQuickItem* qmlObject, const char* method )
{
    QByteArray methodSignature( method );
    methodSignature.append( "()" );

    if ( qmlObject && qmlObject->metaObject()->indexOfMethod( methodSignature )  >= 0 )
    {
        QVariant returnValue;
        QMetaObject::invokeMethod( qmlObject, method, Q_RETURN_ARG( QVariant, returnValue ) );
        if ( !returnValue.isNull() )
        {
            cDebug() << "QML" << methodSignature << "returned" << returnValue;
        }
    }
    else if ( qmlObject )
    {
        cDebug() << "QML" << methodSignature << "is missing.";
    }
}

namespace Calamares
{

ExecutionViewStep::ExecutionViewStep( QObject* parent )
    : ViewStep( parent )
    , m_widget( new QWidget )
    , m_progressBar( new QProgressBar )
    , m_label( new QLabel )
    , m_qmlShow( new QQuickWidget )
    , m_qmlComponent( nullptr )
    , m_qmlObject( nullptr )
{
    QVBoxLayout* layout = new QVBoxLayout( m_widget );
    QVBoxLayout* innerLayout = new QVBoxLayout;

    m_progressBar->setMaximum( 10000 );

    m_qmlShow->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    m_qmlShow->setResizeMode( QQuickWidget::SizeRootObjectToView );
    m_qmlShow->engine()->addImportPath( CalamaresUtils::qmlModulesDir().absolutePath() );

    layout->addWidget( m_qmlShow );
    CalamaresUtils::unmarginLayout( layout );
    layout->addLayout( innerLayout );

    innerLayout->addSpacing( CalamaresUtils::defaultFontHeight() / 2 );
    innerLayout->addWidget( m_progressBar );
    innerLayout->addWidget( m_label );

    cDebug() << "QML import paths:" << Logger::DebugList( m_qmlShow->engine()->importPathList() );
    if ( Branding::instance()->slideshowAPI() == 2 )
    {
        cDebug() << "QML load on startup, API 2.";
        loadQmlV2();
    }

    connect( JobQueue::instance(), &JobQueue::progress, this, &ExecutionViewStep::updateFromJobQueue );
#if QT_VERSION >= QT_VERSION_CHECK( 5, 10, 0 )
    CALAMARES_RETRANSLATE( m_qmlShow->engine()->retranslate(); )
#endif
}


QString
ExecutionViewStep::prettyName() const
{
    return Calamares::Settings::instance()->isSetupMode()
        ? tr( "Set up" )
        : tr( "Install" );
}


QWidget*
ExecutionViewStep::widget()
{
    return m_widget;
}


void
ExecutionViewStep::next()
{
}


void
ExecutionViewStep::back()
{
}


bool
ExecutionViewStep::isNextEnabled() const
{
    return false;
}


bool
ExecutionViewStep::isBackEnabled() const
{
    return false;
}


bool
ExecutionViewStep::isAtBeginning() const
{
    return true;
}


bool
ExecutionViewStep::isAtEnd() const
{
    return true;
}

void
ExecutionViewStep::loadQmlV2()
{
    if ( !m_qmlComponent && !Calamares::Branding::instance()->slideshowPath().isEmpty() )
    {
        m_qmlComponent = new QQmlComponent( m_qmlShow->engine(),
                                            QUrl::fromLocalFile( Calamares::Branding::instance()->slideshowPath() ),
                                            QQmlComponent::CompilationMode::Asynchronous
                                          );
        connect( m_qmlComponent, &QQmlComponent::statusChanged, this, &ExecutionViewStep::loadQmlV2Complete );
    }
}

void
ExecutionViewStep::loadQmlV2Complete()
{
    if ( m_qmlComponent && m_qmlComponent->isReady() && !m_qmlObject )
    {
        cDebug() << "QML loading complete, API 2";
        // Don't do this again
        disconnect( m_qmlComponent, &QQmlComponent::statusChanged, this, &ExecutionViewStep::loadQmlV2Complete );

        QObject* o = m_qmlComponent->create();
        m_qmlObject = qobject_cast< QQuickItem* >( o );
        if ( !m_qmlObject )
            delete o;
        else
        {
            // setContent() is public API, but not documented publicly.
            // It is marked \internal in the Qt sources, but does exactly
            // what is needed: sets up visual parent by replacing the root
            // item, and handling resizes.
            m_qmlShow->setContent( QUrl::fromLocalFile( Calamares::Branding::instance()->slideshowPath() ), m_qmlComponent, m_qmlObject );
            if ( ViewManager::instance()->currentStep() == this )
            {
                // We're alreay visible! Must have been slow QML loading, and we
                // passed onActivate already.
                callQMLFunction( m_qmlObject, "onActivate" );
            }
        }
    }
}

void
ExecutionViewStep::onActivate()
{
    if ( Branding::instance()->slideshowAPI() == 2 )
    {
        // The QML was already loaded in the constructor, need to start it
        callQMLFunction( m_qmlObject, "onActivate" );
    }
    else if ( !Calamares::Branding::instance()->slideshowPath().isEmpty() )
    {
        // API version 1 assumes onCompleted is the trigger
        m_qmlShow->setSource( QUrl::fromLocalFile( Calamares::Branding::instance()->slideshowPath() ) );
    }

    JobQueue* queue = JobQueue::instance();
    foreach ( const QString& instanceKey, m_jobInstanceKeys )
    {
        Calamares::Module* module = Calamares::ModuleManager::instance()->moduleInstance( instanceKey );
        if ( module )
        {
            auto jl = module->jobs();
            if ( module->isEmergency() )
            {
                for( auto& j : jl )
                    j->setEmergency( true );
            }
            queue->enqueue( jl );
        }
    }

    queue->start();
}


JobList
ExecutionViewStep::jobs() const
{
    return JobList();
}


void
ExecutionViewStep::appendJobModuleInstanceKey( const QString& instanceKey )
{
    m_jobInstanceKeys.append( instanceKey );
}


void
ExecutionViewStep::updateFromJobQueue( qreal percent, const QString& message )
{
    m_progressBar->setValue( int( percent * m_progressBar->maximum() ) );
    m_label->setText( message );
}

void
ExecutionViewStep::onLeave()
{
    // API version 2 is explicitly stopped; version 1 keeps running
    if ( Branding::instance()->slideshowAPI() == 2 )
    {
        callQMLFunction( m_qmlObject, "onLeave" );
        delete m_qmlObject;
        m_qmlObject = nullptr;
    }
}

} // namespace
