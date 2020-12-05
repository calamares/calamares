/*
 *   SPDX-FileCopyrightText: 2016 Luca Giambonini <almack@chakraos.org>
 *   SPDX-FileCopyrightText: 2016 Lisa Vitolo <shainer@chakraos.org>
 *   SPDX-FileCopyrightText: 2017 Kyle Robbertze  <krobbertze@gmail.com>
 *   SPDX-FileCopyrightText: 2017-2018 2020, Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "NetInstallViewStep.h"

#include "GlobalStorage.h"
#include "JobQueue.h"

#include "utils/Logger.h"
#include "utils/Variant.h"

#include "NetInstallPage.h"

CALAMARES_PLUGIN_FACTORY_DEFINITION( NetInstallViewStepFactory, registerPlugin< NetInstallViewStep >(); )

NetInstallViewStep::NetInstallViewStep( QObject* parent )
    : Calamares::ViewStep( parent )
    , m_widget( new NetInstallPage( &m_config ) )
    , m_sidebarLabel( nullptr )
    , m_nextEnabled( false )
{
    connect( &m_config, &Config::statusReady, this, &NetInstallViewStep::nextIsReady );
}


NetInstallViewStep::~NetInstallViewStep()
{
    if ( m_widget && m_widget->parent() == nullptr )
    {
        m_widget->deleteLater();
    }
    delete m_sidebarLabel;
}


QString
NetInstallViewStep::prettyName() const
{
    return m_sidebarLabel ? m_sidebarLabel->get() : tr( "Package selection" );

#if defined( TABLE_OF_TRANSLATIONS )
    __builtin_unreachable();
    // This is a table of "standard" labels for this module. If you use them
    // in the label: sidebar: section of the config file, the existing
    // translations can be used.
    tr( "Package selection" );
    tr( "Office software" );
    tr( "Office package" );
    tr( "Browser software" );
    tr( "Browser package" );
    tr( "Web browser" );
    tr( "Kernel" );
    tr( "Services" );
    tr( "Login" );
    tr( "Desktop" );
    tr( "Applications" );
    tr( "Communication" );
    tr( "Development" );
    tr( "Office" );
    tr( "Multimedia" );
    tr( "Internet" );
    tr( "Theming" );
    tr( "Gaming" );
    tr( "Utilities" );
#endif
}


QWidget*
NetInstallViewStep::widget()
{
    return m_widget;
}


bool
NetInstallViewStep::isNextEnabled() const
{
    return !m_config.required() || m_nextEnabled;
}


bool
NetInstallViewStep::isBackEnabled() const
{
    return true;
}


bool
NetInstallViewStep::isAtBeginning() const
{
    return true;
}


bool
NetInstallViewStep::isAtEnd() const
{
    return true;
}


Calamares::JobList
NetInstallViewStep::jobs() const
{
    return Calamares::JobList();
}


void
NetInstallViewStep::onActivate()
{
    m_widget->onActivate();
}

void
NetInstallViewStep::onLeave()
{
    auto packages = m_config.model()->getPackages();
    cDebug() << "Netinstall: Processing" << packages.length() << "packages.";

    static const char PACKAGEOP[] = "packageOperations";

    // Check if there's already a PACAKGEOP entry in GS, and if so we'll
    // extend that one (overwriting the value in GS at the end of this method)
    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
    QVariantList packageOperations = gs->contains( PACKAGEOP ) ? gs->value( PACKAGEOP ).toList() : QVariantList();
    cDebug() << Logger::SubEntry << "Existing package operations length" << packageOperations.length();

    // Clear out existing operations for this module, going backwards:
    // Sometimes we remove an item, and we don't want the index to
    // fall off the end of the list.
    bool somethingRemoved = false;
    for ( int index = packageOperations.length() - 1; 0 <= index; index-- )
    {
        const QVariantMap op = packageOperations.at( index ).toMap();
        if ( op.contains( "source" ) && op.value( "source" ).toString() == moduleInstanceKey().toString() )
        {
            cDebug() << Logger::SubEntry << "Removing existing operations for" << moduleInstanceKey();
            packageOperations.removeAt( index );
            somethingRemoved = true;
        }
    }

    // This netinstall module may add two sub-steps to the packageOperations,
    // one for installing and one for try-installing.
    QVariantList installPackages;
    QVariantList tryInstallPackages;

    for ( const auto& package : packages )
    {
        if ( package->isCritical() )
        {
            installPackages.append( package->toOperation() );
        }
        else
        {
            tryInstallPackages.append( package->toOperation() );
        }
    }

    if ( !installPackages.empty() )
    {
        QVariantMap op;
        op.insert( "install", QVariant( installPackages ) );
        op.insert( "source", moduleInstanceKey().toString() );
        packageOperations.append( op );
        cDebug() << Logger::SubEntry << installPackages.length() << "critical packages.";
    }
    if ( !tryInstallPackages.empty() )
    {
        QVariantMap op;
        op.insert( "try_install", QVariant( tryInstallPackages ) );
        op.insert( "source", moduleInstanceKey().toString() );
        packageOperations.append( op );
        cDebug() << Logger::SubEntry << tryInstallPackages.length() << "non-critical packages.";
    }

    if ( somethingRemoved || !packageOperations.isEmpty() )
    {
        gs->insert( PACKAGEOP, packageOperations );
    }
}

void
NetInstallViewStep::nextIsReady()
{
    m_nextEnabled = true;
    emit nextStatusChanged( true );
}

void
NetInstallViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    m_config.setRequired( CalamaresUtils::getBool( configurationMap, "required", false ) );

    QString groupsUrl = CalamaresUtils::getString( configurationMap, "groupsUrl" );
    if ( !groupsUrl.isEmpty() )
    {
        // Keep putting groupsUrl into the global storage,
        // even though it's no longer used for in-module data-passing.
        Calamares::JobQueue::instance()->globalStorage()->insert( "groupsUrl", groupsUrl );
        if ( groupsUrl == QStringLiteral( "local" ) )
        {
            QVariantList l = configurationMap.value( "groups" ).toList();
            m_config.loadGroupList( l );
        }
        else
        {
            m_config.loadGroupList( groupsUrl );
        }
    }

    bool bogus = false;
    auto label = CalamaresUtils::getSubMap( configurationMap, "label", bogus );

    if ( label.contains( "sidebar" ) )
    {
        m_sidebarLabel = new CalamaresUtils::Locale::TranslatedString( label, "sidebar", metaObject()->className() );
    }
    if ( label.contains( "title" ) )
    {
        m_widget->setPageTitle(
            new CalamaresUtils::Locale::TranslatedString( label, "title", metaObject()->className() ) );
    }
}
