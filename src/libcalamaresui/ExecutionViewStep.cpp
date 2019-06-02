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
#include <QQmlEngine>
#include <QQuickWidget>
#include <QVBoxLayout>

namespace Calamares
{

ExecutionViewStep::ExecutionViewStep( QObject* parent )
    : ViewStep( parent )
    , m_widget( new QWidget )
    , m_progressBar( new QProgressBar )
    , m_label( new QLabel )
    , m_qmlShow( new QQuickWidget )
    , m_qmlShowLoaded( false )
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
    loadQml();

    connect( JobQueue::instance(), &JobQueue::progress, this, &ExecutionViewStep::updateFromJobQueue );

    CALAMARES_RETRANSLATE_WIDGET( m_widget,
        if ( m_qmlShowLoaded )
            m_qmlShow->setSource( QUrl::fromLocalFile( Calamares::Branding::instance()->slideshowPath() ) );
    )
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
ExecutionViewStep::loadQml()
{
    if ( !m_qmlShowLoaded && !Calamares::Branding::instance()->slideshowPath().isEmpty() )
    {
        m_qmlShow->setSource( QUrl::fromLocalFile( Calamares::Branding::instance()->slideshowPath() ) );
        m_qmlShowLoaded = true;
    }
}

void
ExecutionViewStep::onActivate()
{
    loadQml();

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

} // namespace
