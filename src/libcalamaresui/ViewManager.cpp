/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
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
#include "ExecutionViewStep.h"
#include "JobQueue.h"
#include "utils/Retranslator.h"
#include "Branding.h"
#include "Settings.h"

#include <QApplication>
#include <QBoxLayout>
#include <QMessageBox>
#include <QMetaObject>

namespace Calamares
{

ViewManager* ViewManager::s_instance = nullptr;

ViewManager*
ViewManager::instance()
{
    return s_instance;
}

ViewManager*
ViewManager::instance( QObject* parent )
{
    Q_ASSERT( !s_instance );
    s_instance = new ViewManager( parent );
    return s_instance;
}

ViewManager::ViewManager( QObject* parent )
    : QObject( parent )
    , m_currentStep( 0 )
    , m_widget( new QWidget() )
{
    Q_ASSERT( !s_instance );

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
        m_quit->setToolTip( tr( "Cancel installation without changing the system." ) );
    )

    QBoxLayout* bottomLayout = new QHBoxLayout;
    mainLayout->addLayout( bottomLayout );
    bottomLayout->addStretch();
    bottomLayout->addWidget( m_back );
    bottomLayout->addWidget( m_next );
    bottomLayout->addSpacing( 12 );
    bottomLayout->addWidget( m_quit );

    connect( m_next, &QPushButton::clicked, this, &ViewManager::next );
    connect( m_back, &QPushButton::clicked, this, &ViewManager::back );
    m_back->setEnabled( false );

    connect( m_quit, &QPushButton::clicked,
             this, [this]()
    {
        // If it's NOT the last page of the last step, we ask for confirmation
        if ( !( m_currentStep == m_steps.count() -1 &&
                m_steps.last()->isAtEnd() ) )
        {
            QMessageBox mb( QMessageBox::Question,
                            tr( "Cancel installation?" ),
                            tr( "Do you really want to cancel the current install process?\n"
                                "The installer will quit and all changes will be lost." ),
                            QMessageBox::Yes | QMessageBox::No,
                            m_widget );
            mb.setDefaultButton( QMessageBox::No );
            mb.button( QMessageBox::Yes )->setText( tr( "&Yes" ) );
            mb.button( QMessageBox::No )->setText( tr( "&No" ) );
            int response = mb.exec();
            if ( response == QMessageBox::Yes )
                qApp->quit();
        }
        else // Means we're at the end, no need to confirm.
            qApp->quit();
    } );

    connect( JobQueue::instance(), &JobQueue::failed,
             this, &ViewManager::onInstallationFailed );
    connect( JobQueue::instance(), &JobQueue::finished,
             this, &ViewManager::next );
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
    // If this is the first inserted view step, update status of "Next" button
    if ( m_steps.count() == 1 )
        m_next->setEnabled( step->isNextEnabled() );
}


void
ViewManager::insertViewStep( int before, ViewStep* step )
{
    m_steps.insert( before, step );
    QLayout* layout = step->widget()->layout();
    if ( layout )
        layout->setContentsMargins( 0, 0, 0, 0 );
    m_stack->insertWidget( before, step->widget() );

    connect( step, &ViewStep::enlarge, this, &ViewManager::enlarge );
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

    QMessageBox* msgBox = new QMessageBox();
    msgBox->setIcon( QMessageBox::Critical );
    msgBox->setWindowTitle( tr( "Error" ) );
    msgBox->setText( "<strong>" + tr( "Installation Failed" ) + "</strong>" );
    msgBox->setStandardButtons( QMessageBox::Close );
    msgBox->button( QMessageBox::Close )->setText( tr( "&Close" ) );

    QString text = "<p>" + message + "</p>";
    if ( !details.isEmpty() )
        text += "<p>" + details + "</p>";
    msgBox->setInformativeText( text );

    connect( msgBox, &QMessageBox::buttonClicked, qApp, &QApplication::quit );
    cLog() << "Calamares will quit when the dialog closes.";
    msgBox->show();
}


ViewStepList
ViewManager::viewSteps() const
{
    return m_steps;
}


ViewStep*
ViewManager::currentStep() const
{
    return m_steps.value( m_currentStep );
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
    bool executing = false;
    if ( step->isAtEnd() )
    {
        // Special case when the user clicks next on the very last page in a view phase
        // and right before switching to an execution phase.
        // Depending on Calamares::Settings, we show an "are you sure" prompt or not.
        if ( Calamares::Settings::instance()->showPromptBeforeExecution() &&
                m_currentStep + 1 < m_steps.count() &&
                qobject_cast< ExecutionViewStep* >( m_steps.at( m_currentStep + 1 ) ) )
        {
            int reply =
                QMessageBox::question( m_widget,
                                       tr( "Continue with setup?" ),
                                       tr( "The %1 installer is about to make changes to your "
                                           "disk in order to install %2.<br/><strong>You will not be able "
                                           "to undo these changes.</strong>" )
                                       .arg( *Calamares::Branding::ShortProductName )
                                       .arg( *Calamares::Branding::ShortVersionedName ),
                                       tr( "&Install now" ),
                                       tr( "Go &back" ),
                                       QString(),
                                       0,
                                       1 );
            if ( reply == 1 )
                return;
        }

        m_currentStep++;
        m_stack->setCurrentIndex( m_currentStep );
        step->onLeave();
        m_steps.at( m_currentStep )->onActivate();
        executing = qobject_cast< ExecutionViewStep* >( m_steps.at( m_currentStep ) ) != nullptr;
        emit currentStepChanged();
        if ( executing )
        {
            m_back->setEnabled( false );
            m_next->setEnabled( false );
        }
    }
    else
        step->next();

    m_next->setEnabled( !executing && m_steps.at( m_currentStep )->isNextEnabled() );
    m_back->setEnabled( !executing && m_steps.at( m_currentStep )->isBackEnabled() );

    if ( m_currentStep == m_steps.count() -1 &&
            m_steps.last()->isAtEnd() )
    {
        m_quit->setText( tr( "&Done" ) );
        m_quit->setToolTip( tr( "The installation is complete. Close the installer." ) );
    }
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
        step->back();
    else return;

    m_next->setEnabled( m_steps.at( m_currentStep )->isNextEnabled() );
    m_back->setEnabled( m_steps.at( m_currentStep )->isBackEnabled() );

    if ( m_currentStep == 0 && m_steps.first()->isAtBeginning() )
        m_back->setEnabled( false );

    if ( !( m_currentStep == m_steps.count() -1 &&
            m_steps.last()->isAtEnd() ) )
    {
        m_quit->setText( tr( "&Cancel" ) );
        m_quit->setToolTip( tr( "Cancel installation without changing the system." ) );
    }
}

}
