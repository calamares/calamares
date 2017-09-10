/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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
#include "JobQueue.h"
#include "modulesystem/Module.h"
#include "modulesystem/ModuleManager.h"
#include "Settings.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"
#include "utils/Retranslator.h"
#include "ViewManager.h"

#include <QDir>
#include <QLabel>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QtQuickWidgets/QQuickWidget>
#include <QQmlEngine>


namespace Calamares
{

ExecutionViewStep::ExecutionViewStep( QObject* parent )
    : ViewStep( parent )
    , m_widget( new QWidget )
{
    m_progressBar = new QProgressBar;
    m_progressBar->setMaximum( 10000 );
    m_label = new QLabel;
    QVBoxLayout* layout = new QVBoxLayout( m_widget );
    QVBoxLayout* innerLayout = new QVBoxLayout;

    m_slideShow = new QQuickWidget;
    layout->addWidget( m_slideShow );
    CalamaresUtils::unmarginLayout( layout );

    layout->addLayout( innerLayout );
    m_slideShow->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    m_slideShow->setResizeMode( QQuickWidget::SizeRootObjectToView );

    m_slideShow->engine()->addImportPath( CalamaresUtils::qmlModulesDir().absolutePath() );

    innerLayout->addSpacing( CalamaresUtils::defaultFontHeight() / 2 );
    innerLayout->addWidget( m_progressBar );
    innerLayout->addWidget( m_label );

    cDebug() << "QML import paths:" << m_slideShow->engine()->importPathList();

    connect( JobQueue::instance(), &JobQueue::progress,
             this, &ExecutionViewStep::updateFromJobQueue );
}


QString
ExecutionViewStep::prettyName() const
{
    return tr( "Install" );
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
ExecutionViewStep::onActivate()
{
    CALAMARES_RETRANSLATE_WIDGET( m_widget,
        if ( !Calamares::Branding::instance()->slideshowPath().isEmpty() )
            m_slideShow->setSource( QUrl::fromLocalFile( Calamares::Branding::instance()
                                                         ->slideshowPath() ) );
    )


    JobQueue* queue = JobQueue::instance();
    foreach ( const QString& instanceKey, m_jobInstanceKeys )
    {
        Calamares::Module* module = Calamares::ModuleManager::instance()
                                    ->moduleInstance( instanceKey );
        if ( module )
            queue->enqueue( module->jobs() );
    }

    queue->start();
}


QList< Calamares::job_ptr >
ExecutionViewStep::jobs() const
{
    return QList< Calamares::job_ptr >();
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
