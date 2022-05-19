/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2022 Aditya Mehra <Aix.m@outlook.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "PartitionQmlViewStep.h"
#include "Config.h"
#include "ChoicePageQml.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "core/PartUtils.h"
#include "core/PartitionCoreModule.h"

#include <QtConcurrent/QtConcurrent>

CALAMARES_PLUGIN_FACTORY_DEFINITION( PartitionQmlViewStepFactory, registerPlugin< PartitionQmlViewStep >(); )

PartitionQmlViewStep::PartitionQmlViewStep( QObject* parent )
    : Calamares::QmlViewStep( parent )
    , m_config( new Config( this ) )
    , m_core( nullptr )
    , m_choicePage( nullptr )
{
    m_choicePage = new ChoicePageQml(m_config, this);
    m_core = new PartitionCoreModule( this );  // Unusable before init is complete!
    Calamares::QmlViewStep::setContextProperty( "core", m_core );
    Calamares::QmlViewStep::setContextProperty( "choicePage", m_choicePage );
    emit nextStatusChanged( true );
}

QString
PartitionQmlViewStep::prettyName() const
{
    return tr( "Partition" );
}

bool
PartitionQmlViewStep::isNextEnabled() const
{
    return true;
}

bool
PartitionQmlViewStep::isBackEnabled() const
{
    return true;
}

bool
PartitionQmlViewStep::isAtBeginning() const
{
    return true;
}

bool
PartitionQmlViewStep::isAtEnd() const
{
    return true;
}

Calamares::JobList
PartitionQmlViewStep::jobs() const
{
    return m_core->jobs( m_config );
}

void
PartitionQmlViewStep::onActivate()
{
    m_choicePage->init( m_core );
}

void
PartitionQmlViewStep::onLeave()
{
}

QObject*
PartitionQmlViewStep::getConfig()
{
    return m_config;
}

QObject* PartitionQmlViewStep::getCore()
{
    return m_core;
}

void
PartitionQmlViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    m_config->setConfigurationMap( configurationMap );
    Calamares::QmlViewStep::setConfigurationMap( configurationMap );

    m_future = new QFutureWatcher< void >();
    connect( m_future,
             &QFutureWatcher< void >::finished,
             this,
             [ this ]
             {
                 this->m_future->deleteLater();
                 this->m_future = nullptr;
             } );

    QFuture< void > future = QtConcurrent::run( this, &PartitionQmlViewStep::initPartitionCoreModule );
    m_future->setFuture( future );
}

void
PartitionQmlViewStep::initPartitionCoreModule()
{
    Q_ASSERT( m_core );
    m_core->init();
}