/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
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

#include "ViewManager.h"

#include "utils/Logger.h"
#include "viewpages/ViewStep.h"
#include "InstallationViewStep.h"
#include "JobQueue.h"
#include "modulesystem/ModuleManager.h"
#include "utils/Retranslator.h"

#include <QApplication>
#include <QBoxLayout>
#include <QMessageBox>

namespace Calamares
{

ViewManager* ViewManager::s_instance = nullptr;

ViewManager*
ViewManager::instance()
{
    return s_instance;
}

ViewManager::ViewManager( QObject* parent )
    : QObject( parent )
    , m_widget( new QWidget() )
    , m_currentStep( 0 )
    , m_installationViewStep( 0 )
    , m_phase( Prepare )
    , m_finishedStep( 0 )
{
    s_instance = this;
    QBoxLayout* mainLayout = new QVBoxLayout;
    m_widget->setLayout( mainLayout );

    m_stack = new QStackedWidget( m_widget );
    m_stack->setContentsMargins( 0, 0, 0, 0 );
    mainLayout->addWidget( m_stack );

    m_back = new QPushButton( m_widget );
    m_next = new QPushButton( m_widget );
    m_quit = new QPushButton( m_widget );

    CALAMARES_RETRANSLATE(
        m_back->setText( tr( "&Back" ) );
        m_next->setText( tr( "&Next" ) );
        m_quit->setText( tr( "&Cancel" ) );
    )

    QBoxLayout* bottomLayout = new QHBoxLayout;
    mainLayout->addLayout( bottomLayout );
    bottomLayout->addStretch();
    bottomLayout->addWidget( m_back );
    bottomLayout->addWidget( m_next );
    bottomLayout->addSpacing( 12 );
    bottomLayout->addWidget( m_quit );

    connect( m_quit, &QPushButton::clicked,
             this, [this]()
    {
        if ( m_currentStep == m_steps.count() -1 &&
             m_steps.last()->isAtEnd() )
            qApp->quit();
        else
        {
            int response = QMessageBox::question( m_widget,
                            tr( "Cancel installation?" ),
                            tr( "Do you really want to cancel the current install process?\n"
                                "The installer will quit and all changes will be lost." ),
                            QMessageBox::Yes | QMessageBox::No,
                            QMessageBox::No );
            if ( response == QMessageBox::Yes )
                qApp->quit();
        }
    } );
    connect( m_next, &QPushButton::clicked, this, &ViewManager::next );
    connect( m_back, &QPushButton::clicked, this, &ViewManager::back );
    m_back->setEnabled( false );

    m_installationViewStep = new InstallationViewStep( this );
}


ViewManager::~ViewManager()
{
    m_widget->deleteLater();
}


QWidget*
ViewManager::centralWidget()
{
    return m_widget;
}


void
ViewManager::addViewStep( ViewStep* step )
{
    insertViewStep( m_steps.size(), step );

    if ( m_phase == Prepare )
    {
        m_prepareSteps.append( step );
        // If this is the first inserted view step, update status of "Next" button
        if ( m_prepareSteps.count() == 1 )
            m_next->setEnabled( step->isNextEnabled() );
    }
    else if ( m_phase == PostInstall )
    {
        //FIXME: allow multiple postinstall pages
        if ( !m_finishedStep )
            m_finishedStep = step;
    }
}


void
ViewManager::setUpInstallationStep()
{
    if ( m_installationViewStep && !m_steps.contains( m_installationViewStep ) )
    {
        insertViewStep( m_steps.count(), m_installationViewStep );
    }
}


void
ViewManager::insertViewStep( int before, ViewStep* step)
{
    m_steps.insert( before, step );
    QLayout* layout = step->widget()->layout();
    if ( layout )
    {
        layout->setContentsMargins( 0, 0, 0, 0 );
    }
    m_stack->insertWidget( before, step->widget() );

    connect( step, &ViewStep::nextStatusChanged,
             this, [this]( bool status )
    {
        ViewStep* vs = qobject_cast< ViewStep* >( sender() );
        if ( vs )
        {
            if ( vs == m_steps.at( m_currentStep ) )
                m_next->setEnabled( status );
        }
    } );

    m_stack->setCurrentIndex( 0 );
    step->widget()->setFocus();
}


void
ViewManager::onInstallationFailed( const QString& message, const QString& details )
{
    cLog() << "Installation failed:";
    cLog() << "- message:" << message;
    cLog() << "- details:" << details;

    QMessageBox msgBox;
    msgBox.setIcon( QMessageBox::Critical );
    msgBox.setWindowTitle( tr("Error") );
    msgBox.setText( "<strong>" + tr( "Installation Failed" ) + "</strong>" );
    msgBox.setStandardButtons( QMessageBox::Close );

    QString text = "<p>" + message + "</p>";
    if ( !details.isEmpty() )
    {
        text += "<p>" + details + "</p>";
    }
    msgBox.setInformativeText( text );

    msgBox.exec();
    QApplication::quit();
}


QList< ViewStep* >
ViewManager::prepareSteps() const
{
    return m_prepareSteps;
}


ViewStep*
ViewManager::installationStep() const
{
    return m_installationViewStep;
}


ViewStep*
ViewManager::currentStep() const
{
    return m_steps.value( m_currentStep );
}


ViewStep*
ViewManager::finishedStep() const
{
    return m_finishedStep;
}


int
ViewManager::currentStepIndex() const
{
    return m_currentStep;
}


void
ViewManager::next()
{
    ViewStep* step = m_steps.at( m_currentStep );
    bool installing = false;
    if ( step->isAtEnd() )
    {
        m_currentStep++;
        m_stack->setCurrentIndex( m_currentStep );
        step->onLeave();
        m_steps.at( m_currentStep )->onActivate();
        installing = m_steps.at( m_currentStep ) == m_installationViewStep;
        emit currentStepChanged();
        if ( installing )
        {
            emit phaseChangeRequested( Calamares::Install );
            m_phase = Install;
            m_back->setEnabled( false );
            m_next->setEnabled( false );
            connect( Calamares::JobQueue::instance(), &Calamares::JobQueue::finished,
                     this, [this]
            {
                emit phaseChangeRequested( Calamares::PostInstall );
                m_phase = PostInstall;
                m_next->setEnabled( true );
            } );
        }
    }
    else
    {
        step->next();
    }

    m_next->setEnabled( !installing && m_steps.at( m_currentStep )->isNextEnabled() );
    m_back->setEnabled( !installing && m_steps.at( m_currentStep )->isBackEnabled() );

    if ( m_currentStep == m_steps.count() -1 &&
         m_steps.last()->isAtEnd() )
        m_quit->setText( tr( "&Quit" ) );
}


void
ViewManager::back()
{
    ViewStep* step = m_steps.at( m_currentStep );
    if ( step->isAtBeginning() && m_currentStep > 0 )
    {
        m_currentStep--;
        m_stack->setCurrentIndex( m_currentStep );
        step->onLeave();
        m_steps.at( m_currentStep )->onActivate();
        emit currentStepChanged();
    }
    else if ( !step->isAtBeginning() )
    {
        step->back();
    }
    else return;

    m_next->setEnabled( m_steps.at( m_currentStep )->isNextEnabled() );
    m_back->setEnabled( m_steps.at( m_currentStep )->isBackEnabled() );

    if ( m_currentStep == 0 && m_steps.first()->isAtBeginning() )
        m_back->setEnabled( false );

    if ( !( m_currentStep == m_steps.count() -1 &&
            m_steps.last()->isAtEnd() ) )
        m_quit->setText( tr( "&Cancel" ) );
}

}
