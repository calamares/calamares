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

#include "Config.h"

#include "utils/Logger.h"
#include "utils/Variant.h"

#include <QUrl>

TrackingStyleConfig::TrackingStyleConfig( QObject* parent )
    : QObject( parent )
{
}

TrackingStyleConfig::~TrackingStyleConfig() { }

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
            cError() << "URL" << urlString << "is not valid; disabling this tracking type.";
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
}

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
}

/** @brief Is @p s a valid machine-tracking style. */
static bool
isValidMachineTrackingStyle( const QString& s )
{
    static QStringList knownStyles { "neon" };
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
}

static bool
isValidUserTrackingStyle( const QString& s )
{
    static QStringList knownStyles { "kde" };
    return knownStyles.contains( s );
}

void
UserTrackingConfig::setConfigurationMap( const QVariantMap& configurationMap )
{
    TrackingStyleConfig::setConfigurationMap( configurationMap );

    m_userTrackingStyle = CalamaresUtils::getString( configurationMap, "style" );
    validate( m_userTrackingStyle, isValidUserTrackingStyle );
}


Config::Config( QObject* parent )
    : QObject( parent )
    , m_installTracking( new InstallTrackingConfig( this ) )
{
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
}

QString
Config::generalPolicy() const
{
    return m_generalPolicy;
}
