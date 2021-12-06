/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *  SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
 *  SPDX-License-Identifier: GPL-3.0-or-later
 *
 */
#include "LOSHJob.h"

#include "LOSHInfo.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"
#include "utils/Permissions.h"
#include "utils/PluginFactory.h"
#include "utils/Variant.h"

#include <QList>
#include <QObject>
#include <QVariantMap>

LOSHJob::LOSHJob( QObject* parent )
    : Calamares::CppJob( parent )
{
}

LOSHJob::~LOSHJob() {}


QString
LOSHJob::prettyName() const
{
    return tr( "Configuring encrypted swap." );
}

STATICTEST QString
get_assignment_part( const QString& line )
{
    static QRegularExpression re( "^[# \\t]*([A-Za-z_]+)[ \\t]*=" );
    auto m = re.match( line );
    if ( m.hasMatch() )
    {
        return m.captured( 1 );
    }
    return QString();
}

/** Writes the config file at @p path
 *
 * NOTE: @p path is relative to the target system, not an absolute path.
 */
STATICTEST void
write_openswap_conf( const QString& path, QStringList& contents, const LOSHInfo& info )
{
    if ( info.isValid() )
    {
        for ( auto& line : contents )
        {
            const QString key = get_assignment_part( line );
            QString replacement = info.replacementFor( key );
            if ( !replacement.isEmpty() )
            {
                line.clear();
                line.append( QStringLiteral( "%1=%2" ).arg( key, replacement ) );
            }
        }
        cDebug() << "Writing" << contents.length() << "line configuration to" << path;
        // \n between each two lines, and a \n at the end
        CalamaresUtils::System::instance()->createTargetFile(
            path, contents.join( '\n' ).append( '\n' ).toUtf8(), CalamaresUtils::System::WriteMode::Overwrite );
    }
    else
    {
        cDebug() << "Will not write an invalid configuration to" << path;
    }
}

Calamares::JobResult
LOSHJob::exec()
{
    const auto* sys = CalamaresUtils::System::instance();
    if ( !sys )
    {
        return Calamares::JobResult::internalError(
            "LuksOpenSwapHook", tr( "No target system available." ), Calamares::JobResult::InvalidConfiguration );
    }

    Calamares::GlobalStorage* gs
        = Calamares::JobQueue::instance() ? Calamares::JobQueue::instance()->globalStorage() : nullptr;
    if ( !gs || gs->value( "rootMountPoint" ).toString().isEmpty() )
    {
        return Calamares::JobResult::internalError(
            "LuksOpenSwapHook", tr( "No rootMountPoint is set." ), Calamares::JobResult::InvalidConfiguration );
    }
    if ( m_configFilePath.isEmpty() )
    {
        return Calamares::JobResult::internalError(
            "LuksOpenSwapHook", tr( "No configFilePath is set." ), Calamares::JobResult::InvalidConfiguration );
    }

    QStringList contents = sys->readTargetFile( m_configFilePath );
    if ( contents.isEmpty() )
    {
        contents << QStringLiteral( "# swap_device=" ) << QStringLiteral( "# crypt_swap_name=" )
                 << QStringLiteral( "# keyfile_device=" ) << QStringLiteral( "# keyfile_filename=" )
                 << QStringLiteral( "# keyfile_device_mount_options" );
    }

    write_openswap_conf( m_configFilePath, contents, LOSHInfo::fromGlobalStorage() );
    return Calamares::JobResult::ok();
}

void
LOSHJob::setConfigurationMap( const QVariantMap& configurationMap )
{
    m_configFilePath = CalamaresUtils::getString(
        configurationMap, QStringLiteral( "configFilePath" ), QStringLiteral( "/etc/openswap.conf" ) );
}

CALAMARES_PLUGIN_FACTORY_DEFINITION( LOSHJobFactory, registerPlugin< LOSHJob >(); )
