/*
 *   SPDX-FileCopyrightText: 2016 Luca Giambonini <almack@chakraos.org>
 *   SPDX-FileCopyrightText: 2016 Lisa Vitolo     <shainer@chakraos.org>
 *   SPDX-FileCopyrightText: 2017 Kyle Robbertze  <krobbertze@gmail.com>
 *   SPDX-FileCopyrightText: 2017-2018 2020, Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2017 Gabriel Craciunescu <crazy@frugalware.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "Config.h"

#include "LoaderQueue.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "network/Manager.h"
#include "packages/Globals.h"
#include "utils/Logger.h"
#include "utils/Retranslator.h"
#include "utils/Variant.h"

#include <QNetworkReply>

Config::Config( QObject* parent )
    : QObject( parent )
    , m_model( new PackageModel( this ) )
{
    CALAMARES_RETRANSLATE_SLOT( &Config::retranslate );
}

Config::~Config() {}

void
Config::retranslate()
{
    emit statusChanged( status() );
    emit sidebarLabelChanged( sidebarLabel() );
    emit titleLabelChanged( titleLabel() );
}


QString
Config::status() const
{
    switch ( m_status )
    {
    case Status::Ok:
        return QString();
    case Status::FailedBadConfiguration:
        return tr( "Network Installation. (Disabled: Incorrect configuration)" );
    case Status::FailedBadData:
        return tr( "Network Installation. (Disabled: Received invalid groups data)" );
    case Status::FailedInternalError:
        return tr( "Network Installation. (Disabled: Internal error)" );
    case Status::FailedNetworkError:
        return tr( "Network Installation. (Disabled: Unable to fetch package lists, check your network connection)" );
    case Status::FailedNoData:
        return tr( "Network Installation. (Disabled: No package list)" );
    }
    __builtin_unreachable();
}


void
Config::setStatus( Status s )
{
    m_status = s;
    emit statusChanged( status() );
}

QString
Config::sidebarLabel() const
{
    return m_sidebarLabel ? m_sidebarLabel->get() : tr( "Package selection" );
}

QString
Config::titleLabel() const
{
    return m_titleLabel ? m_titleLabel->get() : QString();
}


void
Config::loadGroupList( const QVariantList& groupData )
{
    m_model->setupModelData( groupData );
    if ( m_model->rowCount() < 1 )
    {
        cWarning() << "NetInstall groups data was empty.";
        setStatus( Status::FailedNoData );
    }
    else
    {
        setStatus( Status::Ok );
    }
}

void
Config::loadingDone()
{
    if ( m_queue )
    {
        m_queue->deleteLater();
        m_queue = nullptr;
    }
    emit statusReady();
}


void
Config::setConfigurationMap( const QVariantMap& configurationMap )
{
    setRequired( CalamaresUtils::getBool( configurationMap, "required", false ) );

    // Get the translations, if any
    bool bogus = false;
    auto label = CalamaresUtils::getSubMap( configurationMap, "label", bogus );
    // Use a different class name for translation lookup because the
    // .. table of strings lives in NetInstallViewStep.cpp and moving them
    // .. around is annoying for translators.
    static const char className[] = "NetInstallViewStep";

    if ( label.contains( "sidebar" ) )
    {
        m_sidebarLabel = new CalamaresUtils::Locale::TranslatedString( label, "sidebar", className );
    }
    if ( label.contains( "title" ) )
    {
        m_titleLabel = new CalamaresUtils::Locale::TranslatedString( label, "title", className );
    }

    // Lastly, load the groups data
    const QString key = QStringLiteral( "groupsUrl" );
    const auto& groupsUrlVariant = configurationMap.value( key );
    m_queue = new LoaderQueue( this );
    if ( groupsUrlVariant.type() == QVariant::String )
    {
        m_queue->append( SourceItem::makeSourceItem( groupsUrlVariant.toString(), configurationMap ) );
    }
    else if ( groupsUrlVariant.type() == QVariant::List )
    {
        for ( const auto& s : groupsUrlVariant.toStringList() )
        {
            m_queue->append( SourceItem::makeSourceItem( s, configurationMap ) );
        }
    }

    setStatus( required() ? Status::FailedNoData : Status::Ok );
    cDebug() << "Loading netinstall from" << m_queue->count() << "alternate sources.";
    connect( m_queue, &LoaderQueue::done, this, &Config::loadingDone );
    m_queue->load();
}

void
Config::finalizeGlobalStorage( const Calamares::ModuleSystem::InstanceKey& key )
{
    auto packages = model()->getPackages();

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

    CalamaresUtils::Packages::setGSPackageAdditions(
        Calamares::JobQueue::instance()->globalStorage(), key, installPackages, tryInstallPackages );
}
