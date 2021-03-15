/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "QmlViewStep.h"

#include "Branding.h"
#include "ViewManager.h"

#include "utils/Dirs.h"
#include "utils/Logger.h"
#include "utils/NamedEnum.h"
#include "utils/Qml.h"
#include "utils/Variant.h"
#include "widgets/WaitingWidget.h"

#include <QQmlComponent>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQuickItem>
#include <QQuickWidget>
#include <QVBoxLayout>
#include <QWidget>


/// @brief State-change of the QML, for changeQMLState()
enum class QMLAction
{
    Start,
    Stop
};

/** @brief Tells the QML we activated or left it.
 *
 * If @p action is @c QMLAction::Start, calls onActivate in the QML.
 * If @p action is @c QMLAction::Stop, calls onLeave in the QML.
 *
 * Sets *activatedInCalamares* property on the QML as well (to true
 * if @p action is @c QMLAction::Start, false otherwise).
 */
static void
changeQMLState( QMLAction action, QQuickItem* item )
{
    static const char propertyName[] = "activatedInCalamares";

    bool activate = action == QMLAction::Start;
    CalamaresUtils::callQmlFunction( item, activate ? "onActivate" : "onLeave" );

    auto property = item->property( propertyName );
    if ( property.isValid() && ( property.type() == QVariant::Bool ) && ( property.toBool() != activate ) )
    {
        item->setProperty( propertyName, activate );
    }
}

namespace Calamares
{

QmlViewStep::QmlViewStep( QObject* parent )
    : ViewStep( parent )
    , m_widget( new QWidget )
    , m_spinner( new WaitingWidget( tr( "Loading ..." ) ) )
    , m_qmlWidget( new QQuickWidget )
{
    CalamaresUtils::registerQmlModels();

    QVBoxLayout* layout = new QVBoxLayout( m_widget );
    layout->addWidget( m_spinner );

    m_qmlWidget->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    m_qmlWidget->setResizeMode( QQuickWidget::SizeRootObjectToView );
    m_qmlWidget->engine()->addImportPath( CalamaresUtils::qmlModulesDir().absolutePath() );

    // QML Loading starts when the configuration for the module is set.
}

QmlViewStep::~QmlViewStep() {}

QString
QmlViewStep::prettyName() const
{
    // TODO: query the QML itself
    return tr( "QML Step <i>%1</i>." ).arg( moduleInstanceKey().module() );
}


bool
QmlViewStep::isAtBeginning() const
{
    return true;
}

bool
QmlViewStep::isAtEnd() const
{
    return true;
}
bool
QmlViewStep::isBackEnabled() const
{
    return true;
}

bool
QmlViewStep::isNextEnabled() const
{
    return true;
}

Calamares::JobList
QmlViewStep::jobs() const
{
    return JobList();
}

void
QmlViewStep::onActivate()
{
    if ( m_qmlObject )
    {
        changeQMLState( QMLAction::Start, m_qmlObject );
    }
}

void
QmlViewStep::onLeave()
{
    if ( m_qmlObject )
    {
        changeQMLState( QMLAction::Stop, m_qmlObject );
    }
}

QWidget*
QmlViewStep::widget()
{
    return m_widget;
}

QSize
QmlViewStep::widgetMargins( Qt::Orientations panelSides )
{
    // If any panels around it, use the standard, but if all the
    // panels are hidden, like on full-screen with subsumed navigation,
    // then no margins.
    if ( panelSides )
    {
        return ViewStep::widgetMargins( panelSides );
    }
    else
    {
        return QSize( 0, 0 );
    }
}

void
QmlViewStep::loadComplete()
{
    cDebug() << "QML component" << m_qmlFileName << m_qmlComponent->status();
    if ( m_qmlComponent->status() == QQmlComponent::Error )
    {
        showFailedQml();
    }
    if ( m_qmlComponent->isReady() && !m_qmlObject )
    {
        cDebug() << Logger::SubEntry << "QML component complete" << m_qmlFileName << "creating object";
        // Don't do this again
        disconnect( m_qmlComponent, &QQmlComponent::statusChanged, this, &QmlViewStep::loadComplete );

        QObject* o = m_qmlComponent->create();
        m_qmlObject = qobject_cast< QQuickItem* >( o );
        if ( !m_qmlObject )
        {
            cError() << Logger::SubEntry << "Could not create QML from" << m_qmlFileName;
            delete o;
        }
        else
        {
            // setContent() is public API, but not documented publicly.
            // It is marked \internal in the Qt sources, but does exactly
            // what is needed: sets up visual parent by replacing the root
            // item, and handling resizes.
            m_qmlWidget->setContent( QUrl( m_qmlFileName ), m_qmlComponent, m_qmlObject );
            showQml();
        }
    }
}

void
QmlViewStep::showQml()
{
    if ( !m_qmlWidget || !m_qmlObject )
    {
        cWarning() << "showQml() called but no QML object";
        return;
    }
    if ( m_spinner )
    {
        m_widget->layout()->removeWidget( m_spinner );
        m_widget->layout()->addWidget( m_qmlWidget );
        delete m_spinner;
        m_spinner = nullptr;
    }
    else
    {
        cWarning() << "showQml() called twice";
    }

    if ( ViewManager::instance()->currentStep() == this )
    {
        // We're alreay visible! Must have been slow QML loading, and we
        // passed onActivate already.
        changeQMLState( QMLAction::Start, m_qmlObject );
    }
}


void
QmlViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    bool ok = false;
    m_searchMethod
        = CalamaresUtils::qmlSearchNames().find( CalamaresUtils::getString( configurationMap, "qmlSearch" ), ok );
    if ( !ok )
    {
        cWarning() << "Bad QML search mode set for" << moduleInstanceKey();
    }

    QString qmlFile = CalamaresUtils::getString( configurationMap, "qmlFilename" );
    if ( !m_qmlComponent )
    {
        m_qmlFileName = searchQmlFile( m_searchMethod, qmlFile, moduleInstanceKey() );

        QObject* config = this->getConfig();
        if ( config )
        {
            setContextProperty( "config", config );
        }

        cDebug() << "QmlViewStep" << moduleInstanceKey() << "loading" << m_qmlFileName;
        m_qmlComponent = new QQmlComponent(
            m_qmlWidget->engine(), QUrl( m_qmlFileName ), QQmlComponent::CompilationMode::Asynchronous );
        connect( m_qmlComponent, &QQmlComponent::statusChanged, this, &QmlViewStep::loadComplete );
        if ( m_qmlComponent->status() == QQmlComponent::Error )
        {
            showFailedQml();
        }
    }
    else
    {
        cWarning() << "QML configuration set after component" << moduleInstanceKey() << "has loaded.";
    }
}

void
QmlViewStep::showFailedQml()
{
    cWarning() << "QmlViewStep" << moduleInstanceKey() << "loading failed.";
    if ( m_qmlComponent )
    {
        cDebug() << Logger::SubEntry << "QML error:" << m_qmlComponent->errorString();
    }
    m_spinner->setText( prettyName() + ' ' + tr( "Loading failed." ) );
}

QObject*
QmlViewStep::getConfig()
{
    return nullptr;
}

void
QmlViewStep::setContextProperty( const char* name, QObject* property )
{
    m_qmlWidget->engine()->rootContext()->setContextProperty( name, property );
}

}  // namespace Calamares
