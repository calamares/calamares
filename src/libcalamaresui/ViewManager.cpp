/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019, Dominic Hayes <ferenosdev@outlook.com>
 *   Copyright 2019, Gabriel Craciunescu <crazy@frugalware.org>
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017-2018, 2020, Adriaan de Groot <groot@kde.org>
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

#include "Branding.h"
#include "JobQueue.h"
#include "Settings.h"

#include "utils/Logger.h"
#include "utils/Paste.h"
#include "utils/Retranslator.h"
#include "viewpages/BlankViewStep.h"
#include "viewpages/ExecutionViewStep.h"
#include "viewpages/ViewStep.h"

#include <QApplication>
#include <QBoxLayout>
#include <QFile>
#include <QMessageBox>
#include <QMetaObject>

#define UPDATE_BUTTON_PROPERTY( name, value ) \
    { \
        m_##name = value; \
        emit name##Changed( m_##name ); \
    }

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
    : QAbstractListModel( parent )
    , m_currentStep( -1 )
    , m_widget( new QWidget() )
{
    Q_ASSERT( !s_instance );

    QBoxLayout* mainLayout = new QVBoxLayout;
    m_widget->setObjectName( "viewManager" );
    m_widget->setLayout( mainLayout );

    m_stack = new QStackedWidget( m_widget );
    m_stack->setObjectName( "viewManagerStack" );
    m_stack->setContentsMargins( 0, 0, 0, 0 );
    mainLayout->addWidget( m_stack );

    updateButtonLabels();

    connect( JobQueue::instance(), &JobQueue::failed, this, &ViewManager::onInstallationFailed );
    connect( JobQueue::instance(), &JobQueue::finished, this, &ViewManager::next );

    CALAMARES_RETRANSLATE_SLOT( &ViewManager::updateButtonLabels )
}


ViewManager::~ViewManager()
{
    m_widget->deleteLater();
    s_instance = nullptr;
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
    {
        m_nextEnabled = step->isNextEnabled();
        emit nextEnabledChanged( m_nextEnabled );
    }
}


void
ViewManager::insertViewStep( int before, ViewStep* step )
{
    emit beginInsertRows( QModelIndex(), before, before );
    m_steps.insert( before, step );
    connect( step, &ViewStep::ensureSize, this, &ViewManager::ensureSize );
    connect( step, &ViewStep::nextStatusChanged, this, &ViewManager::updateNextStatus );

    if ( !step->widget() )
    {
        cError() << "ViewStep" << step->moduleInstanceKey() << "has no widget.";
    }

    QLayout* layout = step->widget()->layout();
    if ( layout )
    {
        layout->setContentsMargins( 0, 0, 0, 0 );
    }
    m_stack->insertWidget( before, step->widget() );
    m_stack->setCurrentIndex( 0 );
    step->widget()->setFocus();
    emit endInsertRows();
}


void
ViewManager::onInstallationFailed( const QString& message, const QString& details )
{
    bool shouldOfferWebPaste = false;  // TODO: config var

    cError() << "Installation failed:";
    cDebug() << "- message:" << message;
    cDebug() << "- details:" << details;

    QString heading
        = Calamares::Settings::instance()->isSetupMode() ? tr( "Setup Failed" ) : tr( "Installation Failed" );
    QString pasteMsg = tr( "Would you like to paste the install log to the web?" );
    QString text = "<p>" + message + "</p>";
    if ( !details.isEmpty() )
    {
        text += "<p>" + details + "</p>";
    }
    if ( shouldOfferWebPaste )
    {
        text += "<p>" + pasteMsg + "</p>";
    }

    QMessageBox* msgBox = new QMessageBox();
    msgBox->setIcon( QMessageBox::Critical );
    msgBox->setWindowTitle( tr( "Error" ) );
    msgBox->setText( "<strong>" + heading + "</strong>" );
    msgBox->setInformativeText( text );
    if ( shouldOfferWebPaste )
    {
        msgBox->setStandardButtons( QMessageBox::Yes | QMessageBox::No );
        msgBox->setDefaultButton( QMessageBox::No );
        msgBox->button( QMessageBox::Yes )->setText( tr( "&Yes" ) );
        msgBox->button( QMessageBox::No )->setText( tr( "&No" ) );
    }
    else
    {
        msgBox->setStandardButtons( QMessageBox::Close );
        msgBox->setDefaultButton( QMessageBox::Close );
        msgBox->button( QMessageBox::Close )->setText( tr( "&Close" ) );
    }
    msgBox->show();

    cDebug() << "Calamares will quit when the dialog closes.";
    connect( msgBox, &QMessageBox::buttonClicked, [ msgBox ]( QAbstractButton* button ) {
        if ( msgBox->buttonRole( button ) == QMessageBox::ButtonRole::YesRole )
        {
            // TODO: host and port should be configurable
            QString pasteUrlMsg = CalamaresUtils::sendLogToPastebin( msgBox, QStringLiteral( "termbin.com" ), 9999 );

            QString pasteUrlTitle = tr( "Install Log Paste URL" );
            if ( pasteUrlMsg.isEmpty() )
            {
                pasteUrlMsg = tr( "The upload was unsuccessful. No web-paste was done." );
            }

            // TODO: make the URL clickable, or copy it to the clipboard automatically
            QMessageBox::critical( nullptr, pasteUrlTitle, pasteUrlMsg );
        }
        QApplication::quit();
    } );
}


void
ViewManager::onInitFailed( const QStringList& modules )
{
    // Because this means the installer / setup program is broken by the distributor,
    // don't bother being precise about installer / setup wording.
    QString title( tr( "Calamares Initialization Failed" ) );
    QString description( tr( "%1 can not be installed. Calamares was unable to load all of the configured modules. "
                             "This is a problem with the way Calamares is being used by the distribution." ) );
    QString detailString;

    if ( modules.count() > 0 )
    {
        description.append( tr( "<br/>The following modules could not be loaded:" ) );
        QStringList details;
        details << QLatin1String( "<ul>" );
        for ( const auto& m : modules )
        {
            details << QLatin1String( "<li>" ) << m << QLatin1String( "</li>" );
        }
        details << QLatin1String( "</ul>" );
        detailString = details.join( QString() );
    }

    insertViewStep(
        0,
        new BlankViewStep( title, description.arg( Calamares::Branding::instance()->productName() ), detailString ) );
}

void
ViewManager::onInitComplete()
{
    m_currentStep = 0;

    // Tell the first view that it's been shown.
    if ( m_steps.count() > 0 )
    {
        m_steps.first()->onActivate();
    }
}

void
ViewManager::updateNextStatus( bool status )
{
    ViewStep* vs = qobject_cast< ViewStep* >( sender() );
    if ( vs && currentStepValid() )
    {
        if ( vs == m_steps.at( m_currentStep ) )
        {
            m_nextEnabled = status;
            emit nextEnabledChanged( m_nextEnabled );
        }
    }
}


ViewStepList
ViewManager::viewSteps() const
{
    return m_steps;
}


ViewStep*
ViewManager::currentStep() const
{
    return currentStepValid() ? m_steps.value( m_currentStep ) : nullptr;
}


int
ViewManager::currentStepIndex() const
{
    return m_currentStep;
}

/** @brief Is the given step at @p index an execution step?
 *
 * Returns true if the step is an execution step, false otherwise.
 * Also returns false if the @p index is out of range.
 */
static inline bool
stepIsExecute( const ViewStepList& steps, int index )
{
    return ( 0 <= index ) && ( index < steps.count() )
        && ( qobject_cast< ExecutionViewStep* >( steps.at( index ) ) != nullptr );
}

static inline bool
isAtVeryEnd( const ViewStepList& steps, int index )
{
    // If we have an empty list, then there's no point right now
    // in checking if we're at the end.
    if ( steps.count() == 0 )
    {
        return false;
    }
    // .. and if the index is invalid, ignore it too
    if ( !( ( 0 <= index ) && ( index < steps.count() ) ) )
    {
        return false;
    }
    return ( index >= steps.count() ) || ( index == steps.count() - 1 && steps.last()->isAtEnd() );
}

void
ViewManager::next()
{
    if ( !currentStepValid() )
    {
        return;
    }

    ViewStep* step = m_steps.at( m_currentStep );
    bool executing = false;
    if ( step->isAtEnd() )
    {
        const auto* const settings = Calamares::Settings::instance();

        // Special case when the user clicks next on the very last page in a view phase
        // and right before switching to an execution phase.
        // Depending on Calamares::Settings, we show an "are you sure" prompt or not.
        if ( settings->showPromptBeforeExecution() && stepIsExecute( m_steps, m_currentStep + 1 ) )
        {
            QString title
                = settings->isSetupMode() ? tr( "Continue with setup?" ) : tr( "Continue with installation?" );
            QString question = settings->isSetupMode()
                ? tr( "The %1 setup program is about to make changes to your "
                      "disk in order to set up %2.<br/><strong>You will not be able "
                      "to undo these changes.</strong>" )
                : tr( "The %1 installer is about to make changes to your "
                      "disk in order to install %2.<br/><strong>You will not be able "
                      "to undo these changes.</strong>" );
            QString confirm = settings->isSetupMode() ? tr( "&Set up now" ) : tr( "&Install now" );

            const auto* branding = Calamares::Branding::instance();
            int reply
                = QMessageBox::question( m_widget,
                                         title,
                                         question.arg( branding->shortProductName(), branding->shortVersionedName() ),
                                         confirm,
                                         tr( "Go &back" ),
                                         QString(),
                                         0 /* default first button, i.e. confirm */,
                                         1 /* escape is second button, i.e. cancel */ );
            if ( reply == 1 )
            {
                return;
            }
        }

        m_currentStep++;

        m_stack->setCurrentIndex( m_currentStep );  // Does nothing if out of range
        step->onLeave();

        if ( m_currentStep < m_steps.count() )
        {
            m_steps.at( m_currentStep )->onActivate();
            executing = qobject_cast< ExecutionViewStep* >( m_steps.at( m_currentStep ) ) != nullptr;
            emit currentStepChanged();
        }
        else
        {
            // Reached the end in a weird state (e.g. no finished step after an exec)
            executing = false;
            UPDATE_BUTTON_PROPERTY( nextEnabled, false )
            UPDATE_BUTTON_PROPERTY( backEnabled, false )
        }
        updateCancelEnabled( !settings->disableCancel() && !( executing && settings->disableCancelDuringExec() ) );
    }
    else
    {
        step->next();
    }

    if ( m_currentStep < m_steps.count() )
    {
        UPDATE_BUTTON_PROPERTY( nextEnabled, !executing && m_steps.at( m_currentStep )->isNextEnabled() )
        UPDATE_BUTTON_PROPERTY( backEnabled, !executing && m_steps.at( m_currentStep )->isBackEnabled() )
    }

    updateButtonLabels();
}

void
ViewManager::updateButtonLabels()
{
    const auto* const settings = Calamares::Settings::instance();

    QString nextIsInstallationStep = settings->isSetupMode() ? tr( "&Set up" ) : tr( "&Install" );
    QString quitOnCompleteTooltip = settings->isSetupMode()
        ? tr( "Setup is complete. Close the setup program." )
        : tr( "The installation is complete. Close the installer." );
    QString cancelBeforeInstallationTooltip = settings->isSetupMode()
        ? tr( "Cancel setup without changing the system." )
        : tr( "Cancel installation without changing the system." );

    // If we're going into the execution step / install phase, other message
    if ( stepIsExecute( m_steps, m_currentStep + 1 ) )
    {
        UPDATE_BUTTON_PROPERTY( nextLabel, nextIsInstallationStep )
        UPDATE_BUTTON_PROPERTY( nextIcon, "run-install" )
    }
    else
    {
        UPDATE_BUTTON_PROPERTY( nextLabel, tr( "&Next" ) )
        UPDATE_BUTTON_PROPERTY( nextIcon, "go-next" )
    }

    // Going back is always simple
    UPDATE_BUTTON_PROPERTY( backLabel, tr( "&Back" ) )
    UPDATE_BUTTON_PROPERTY( backIcon, "go-previous" )

    // Cancel button changes label at the end
    if ( isAtVeryEnd( m_steps, m_currentStep ) )
    {
        UPDATE_BUTTON_PROPERTY( quitLabel, tr( "&Done" ) )
        UPDATE_BUTTON_PROPERTY( quitTooltip, quitOnCompleteTooltip )
        UPDATE_BUTTON_PROPERTY( quitVisible, true )
        UPDATE_BUTTON_PROPERTY( quitIcon, "dialog-ok-apply" )
        updateCancelEnabled( true );
        if ( settings->quitAtEnd() )
        {
            quit();
        }
    }
    else
    {
        if ( settings->disableCancel() )
        {
            UPDATE_BUTTON_PROPERTY( quitVisible, false )
        }
        updateCancelEnabled( !settings->disableCancel()
                             && !( stepIsExecute( m_steps, m_currentStep ) && settings->disableCancelDuringExec() ) );

        UPDATE_BUTTON_PROPERTY( quitLabel, tr( "&Cancel" ) )
        UPDATE_BUTTON_PROPERTY( quitTooltip, cancelBeforeInstallationTooltip )
        UPDATE_BUTTON_PROPERTY( quitIcon, "dialog-cancel" )
    }
}

void
ViewManager::back()
{
    if ( !currentStepValid() )
    {
        return;
    }

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
    else
    {
        return;
    }

    UPDATE_BUTTON_PROPERTY( nextEnabled, m_steps.at( m_currentStep )->isNextEnabled() )
    UPDATE_BUTTON_PROPERTY( backEnabled,
                            ( m_currentStep == 0 && m_steps.first()->isAtBeginning() )
                                ? false
                                : m_steps.at( m_currentStep )->isBackEnabled() )

    updateButtonLabels();
}


void
ViewManager::quit()
{
    if ( confirmCancelInstallation() )
    {
        qApp->quit();
    }
}

bool
ViewManager::confirmCancelInstallation()
{
    const auto* const settings = Calamares::Settings::instance();

    // When we're at the very end, then it's always OK to exit.
    if ( isAtVeryEnd( m_steps, m_currentStep ) )
    {
        return true;
    }

    // Not at the very end, cancel/quit might be disabled
    if ( settings->disableCancel() )
    {
        return false;
    }
    if ( settings->disableCancelDuringExec() && stepIsExecute( m_steps, m_currentStep ) )
    {
        return false;
    }

    // Otherwise, confirm cancel/quit.
    QString title = settings->isSetupMode() ? tr( "Cancel setup?" ) : tr( "Cancel installation?" );
    QString question = settings->isSetupMode() ? tr( "Do you really want to cancel the current setup process?\n"
                                                     "The setup program will quit and all changes will be lost." )
                                               : tr( "Do you really want to cancel the current install process?\n"
                                                     "The installer will quit and all changes will be lost." );
    QMessageBox mb( QMessageBox::Question, title, question, QMessageBox::Yes | QMessageBox::No, m_widget );
    mb.setDefaultButton( QMessageBox::No );
    mb.button( QMessageBox::Yes )->setText( tr( "&Yes" ) );
    mb.button( QMessageBox::No )->setText( tr( "&No" ) );
    int response = mb.exec();
    return response == QMessageBox::Yes;
}

void
ViewManager::updateCancelEnabled( bool enabled )
{
    UPDATE_BUTTON_PROPERTY( quitEnabled, enabled )
    emit cancelEnabled( enabled );
}

QVariant
ViewManager::data( const QModelIndex& index, int role ) const
{
    if ( !index.isValid() )
    {
        return QVariant();
    }

    if ( ( index.row() < 0 ) || ( index.row() >= m_steps.length() ) )
    {
        return QVariant();
    }

    const auto* step = m_steps.at( index.row() );
    if ( !step )
    {
        return QVariant();
    }

    switch ( role )
    {
    case Qt::DisplayRole:
        return step->prettyName();
    case Qt::ToolTipRole:
        if ( Calamares::Settings::instance()->debugMode() )
        {
            auto key = step->moduleInstanceKey();
            QString toolTip( "<b>Debug information</b>" );
            toolTip.append( "<br/>Type:\tViewStep" );
            toolTip.append( QString( "<br/>Pretty:\t%1" ).arg( step->prettyName() ) );
            toolTip.append( QString( "<br/>Status:\t%1" ).arg( step->prettyStatus() ) );
            toolTip.append(
                QString( "<br/>Source:\t%1" ).arg( key.isValid() ? key.toString() : QStringLiteral( "built-in" ) ) );
            return toolTip;
        }
        else
        {
            return QVariant();
        }
    case ProgressTreeItemCurrentIndex:
        return m_currentStep;
    default:
        return QVariant();
    }
}


int
ViewManager::rowCount( const QModelIndex& parent ) const
{
    if ( parent.column() > 0 )
    {
        return 0;
    }
    return m_steps.length();
}

}  // namespace Calamares
