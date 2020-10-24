/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "Config.h"

#include "TrackingType.h"

#include "utils/Logger.h"
#include "utils/Variant.h"

#include <QUrl>

const NamedEnumTable< TrackingType >&
trackingNames()
{
    // *INDENT-OFF*
    // clang-format off
    static const NamedEnumTable< TrackingType > names {
        { QStringLiteral( "none" ), TrackingType::NoTracking },
        { QStringLiteral( "install" ), TrackingType::InstallTracking },
        { QStringLiteral( "machine" ), TrackingType::MachineTracking },
        { QStringLiteral( "user" ), TrackingType::UserTracking }
    };
    // clang-format on
    // *INDENT-ON*

    return names;
}

TrackingStyleConfig::TrackingStyleConfig( QObject* parent )
    : QObject( parent )
{
}

TrackingStyleConfig::~TrackingStyleConfig() {}

void
TrackingStyleConfig::setTracking( bool enabled )
{
    setTracking( enabled ? EnabledByUser : DisabledByUser );
}

void
TrackingStyleConfig::setTracking( TrackingStyleConfig::TrackingState state )
{
    if ( m_state != TrackingState::DisabledByConfig )
    {
        m_state = state;
    }
    emit trackingChanged();
}

void
TrackingStyleConfig::validate( QString& s, std::function< bool( const QString& ) >&& pred )
{
    if ( !pred( s ) )
    {
        if ( m_state != DisabledByConfig )
        {
            cError() << "Configuration string" << s << "is not valid; disabling this tracking type.";
            m_state = DisabledByConfig;
            emit trackingChanged();
        }
        s = QString();
    }
}

void
TrackingStyleConfig::validateUrl( QString& urlString )
{
    if ( !QUrl( urlString ).isValid() )
    {
        if ( m_state != DisabledByConfig )
        {
            cError() << "URL" << urlString << "is not valid; disabling tracking type" << objectName();
            m_state = DisabledByConfig;
            emit trackingChanged();
        }
        urlString = QString();
    }
}


void
TrackingStyleConfig::setConfigurationMap( const QVariantMap& config )
{
    m_state = CalamaresUtils::getBool( config, "enabled", false ) ? DisabledByUser : DisabledByConfig;
    m_policy = CalamaresUtils::getString( config, "policy" );
    validateUrl( m_policy );
    emit policyChanged( m_policy );
    emit trackingChanged();
}

InstallTrackingConfig::InstallTrackingConfig( QObject* parent )
    : TrackingStyleConfig( parent )
{
    setObjectName( "InstallTrackingConfig" );
}

InstallTrackingConfig::~InstallTrackingConfig() {}

void
InstallTrackingConfig::setConfigurationMap( const QVariantMap& configurationMap )
{
    TrackingStyleConfig::setConfigurationMap( configurationMap );

    m_installTrackingUrl = CalamaresUtils::getString( configurationMap, "url" );
    validateUrl( m_installTrackingUrl );
}

MachineTrackingConfig::MachineTrackingConfig( QObject* parent )
    : TrackingStyleConfig( parent )
{
    setObjectName( "MachineTrackingConfig" );
}

MachineTrackingConfig::~MachineTrackingConfig() {}

/** @brief Is @p s a valid machine-tracking style. */
static bool
isValidMachineTrackingStyle( const QString& s )
{
    static QStringList knownStyles { "updatemanager" };
    return knownStyles.contains( s );
}

void
MachineTrackingConfig::setConfigurationMap( const QVariantMap& configurationMap )
{
    TrackingStyleConfig::setConfigurationMap( configurationMap );

    m_machineTrackingStyle = CalamaresUtils::getString( configurationMap, "style" );
    validate( m_machineTrackingStyle, isValidMachineTrackingStyle );
}


UserTrackingConfig::UserTrackingConfig( QObject* parent )
    : TrackingStyleConfig( parent )
{
    setObjectName( "UserTrackingConfig" );
}

UserTrackingConfig::~UserTrackingConfig() {}

static bool
isValidUserTrackingStyle( const QString& s )
{
    static QStringList knownStyles { "kuserfeedback" };
    return knownStyles.contains( s );
}

void
UserTrackingConfig::setConfigurationMap( const QVariantMap& configurationMap )
{
    TrackingStyleConfig::setConfigurationMap( configurationMap );

    m_userTrackingStyle = CalamaresUtils::getString( configurationMap, "style" );
    validate( m_userTrackingStyle, isValidUserTrackingStyle );

    m_userTrackingAreas = CalamaresUtils::getStringList( configurationMap, "areas" );
}


Config::Config( QObject* parent )
    : QObject( parent )
    , m_installTracking( new InstallTrackingConfig( this ) )
    , m_machineTracking( new MachineTrackingConfig( this ) )
    , m_userTracking( new UserTrackingConfig( this ) )
{
}

static void
enableLevelsBelow( Config* config, TrackingType level )
{
    switch ( level )
    {
    case TrackingType::UserTracking:
        config->userTracking()->setTracking( TrackingStyleConfig::TrackingState::EnabledByUser );
        [[fallthrough]];
    case TrackingType::MachineTracking:
        config->machineTracking()->setTracking( TrackingStyleConfig::TrackingState::EnabledByUser );
        [[fallthrough]];
    case TrackingType::InstallTracking:
        config->installTracking()->setTracking( TrackingStyleConfig::TrackingState::EnabledByUser );
        break;
    case TrackingType::NoTracking:
        config->noTracking( true );
        break;
    }
}

void
Config::setConfigurationMap( const QVariantMap& configurationMap )
{
    m_generalPolicy = CalamaresUtils::getString( configurationMap, "policy" );

    if ( !QUrl( m_generalPolicy ).isValid() )
    {
        m_generalPolicy = QString();
    }
    emit generalPolicyChanged( m_generalPolicy );

    bool success = false;
    auto subconfig = CalamaresUtils::getSubMap( configurationMap, "install", success );
    if ( success )
    {
        m_installTracking->setConfigurationMap( subconfig );
    }

    subconfig = CalamaresUtils::getSubMap( configurationMap, "machine", success );
    if ( success )
    {
        m_machineTracking->setConfigurationMap( subconfig );
    }

    subconfig = CalamaresUtils::getSubMap( configurationMap, "user", success );
    if ( success )
    {
        m_userTracking->setConfigurationMap( subconfig );
    }

    auto level = trackingNames().find( CalamaresUtils::getString( configurationMap, "default" ), success );
    if ( !success )
    {
        cWarning() << "Default tracking level unknown:" << CalamaresUtils::getString( configurationMap, "default" );
        level = TrackingType::NoTracking;
    }
    enableLevelsBelow( this, level );
}

QString
Config::generalPolicy() const
{
    return m_generalPolicy;
}

void
Config::noTracking( bool switchOffAllTracking )
{
    if ( !switchOffAllTracking )
    {
        return;
    }
    m_installTracking->setTracking( TrackingStyleConfig::TrackingState::DisabledByUser );
    m_machineTracking->setTracking( TrackingStyleConfig::TrackingState::DisabledByUser );
    m_userTracking->setTracking( TrackingStyleConfig::TrackingState::DisabledByUser );
}
