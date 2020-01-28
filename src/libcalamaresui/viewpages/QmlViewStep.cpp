/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2020, Adriaan de Groot <groot@kde.org>
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

#include "QmlViewStep.h"

#include "Branding.h"

#include "utils/Dirs.h"
#include "utils/Logger.h"
#include "utils/NamedEnum.h"
#include "utils/Variant.h"
#include "widgets/WaitingWidget.h"

#include <QQmlComponent>
#include <QQmlEngine>
#include <QQuickItem>
#include <QQuickWidget>
#include <QVBoxLayout>
#include <QWidget>

static const NamedEnumTable< Calamares::QmlViewStep::QmlSearch >&
searchNames()
{
    using Search = Calamares::QmlViewStep::QmlSearch;
    // *INDENT-OFF*
    // clang-format off
    static NamedEnumTable< Search > names {
        { QStringLiteral( "both" ), Search::Both },
        { QStringLiteral( "qrc" ), Search::QrcOnly },
        { QStringLiteral( "branding" ), Search::BrandingOnly }
    };
    // *INDENT-ON*
    // clang-format on

    return names;
}

namespace Calamares
{

QmlViewStep::QmlViewStep( const QString& name, QObject* parent )
    : ViewStep( parent )
    , m_name( name )
    , m_widget( new QWidget )
    , m_spinner( new WaitingWidget( tr( "Loading ..." ) ) )
    , m_qmlWidget( new QQuickWidget )
{
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
    return tr( "QML Step <i>%1</i>." ).arg( m_name );
}


}  // namespace Calamares

bool
Calamares::QmlViewStep::isAtBeginning() const
{
    return true;
}

bool
Calamares::QmlViewStep::isAtEnd() const
{
    return true;
}
bool
Calamares::QmlViewStep::isBackEnabled() const
{
    return true;
}

bool
Calamares::QmlViewStep::isNextEnabled() const
{
    return true;
}

Calamares::JobList
Calamares::QmlViewStep::jobs() const
{
    return JobList();
}

void
Calamares::QmlViewStep::onActivate()
{
    // TODO: call into QML
}

void
Calamares::QmlViewStep::onLeave()
{
    // TODO: call into QML
}

QWidget*
Calamares::QmlViewStep::widget()
{
    return m_widget;
}

void
Calamares::QmlViewStep::loadComplete()
{
    cDebug() << "QML component" << m_qmlFileName << m_qmlComponent->status();
    if ( m_qmlComponent->status() == QQmlComponent::Error )
    {
        showFailedQml();
    }
    if ( m_qmlComponent->isReady() && !m_qmlObject )
    {
        cDebug() << "QML component complete" << m_qmlFileName;
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
Calamares::QmlViewStep::showQml()
{
    if ( !m_qmlWidget || !m_qmlObject )
    {
        cDebug() << "showQml() called but no QML object";
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
        cDebug() << "showQml() called twice";
    }
}


/** @brief Find a suitable QML file, given the search method and name hints
 *
 * Returns QString() if nothing is found (which would mean the module
 * is badly configured).
 */
QString
searchQmlFile( Calamares::QmlViewStep::QmlSearch method, const QString& configuredName, const QString& moduleName )
{
    using QmlSearch = Calamares::QmlViewStep::QmlSearch;

    cDebug() << "Looking for QML for" << moduleName;
    QStringList candidates;
    if ( configuredName.startsWith( '/' ) )
    {
        candidates << configuredName;
    }
    if ( ( method == QmlSearch::Both ) || ( method == QmlSearch::BrandingOnly ) )
    {
        QString brandDir = Calamares::Branding::instance()->componentDirectory();
        candidates << ( configuredName.isEmpty() ? QString()
                                                 : QStringLiteral( "%1/%2.qml" ).arg( brandDir, configuredName ) )
                   << ( moduleName.isEmpty() ? QString() : QStringLiteral( "%1/%2.qml" ).arg( brandDir, moduleName ) );
    }
    if ( ( method == QmlSearch::Both ) || ( method == QmlSearch::QrcOnly ) )
    {
        candidates << ( configuredName.isEmpty() ? QString() : QStringLiteral( ":/%1.qml" ).arg( configuredName ) )
                   << ( moduleName.isEmpty() ? QString() : QStringLiteral( ":/%1.qml" ).arg( moduleName ) );
    }
    for ( const QString& candidate : candidates )
    {
        if ( candidate.isEmpty() )
        {
            continue;
        }
        cDebug() << Logger::SubEntry << "Looking at QML file" << candidate;
        if ( QFile::exists( candidate ) )
        {
            if ( candidate.startsWith( ':' ) )
            {
                // Inconsistency: QFile only sees the file with :,
                // but QML needs an explicit scheme (of qrc:)
                return QStringLiteral( "qrc" ) + candidate;
            }
            return candidate;
        }
    }
    cDebug() << Logger::SubEntry << "None found.";
    return QString();
}

void
Calamares::QmlViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    bool ok = false;
    m_searchMethod = searchNames().find( CalamaresUtils::getString( configurationMap, "search" ), ok );
    if ( !ok )
    {
        cDebug() << "Bad QML search mode.";
    }

    QString qmlFile = CalamaresUtils::getString( configurationMap, "filename" );
    if ( qmlFile.isEmpty() )
    {
        // TODO use the module instance
    }

    if ( !m_qmlComponent )
    {
        m_qmlFileName = searchQmlFile( m_searchMethod, qmlFile, m_name );

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
        cWarning() << "QML configuration set after component has loaded.";
    }
}

void
Calamares::QmlViewStep::showFailedQml()
{
    cWarning() << "QmlViewStep" << moduleInstanceKey() << "loading failed.";
    m_spinner->setText( prettyName() + ' ' + tr( "Loading failed." ) );
}
