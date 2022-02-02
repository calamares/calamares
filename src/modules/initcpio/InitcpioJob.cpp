/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2022 Evan James <dalto@fastmail.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "InitcpioJob.h"

#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"
#include "utils/UMask.h"
#include "utils/Variant.h"

#include <QDir>
#include <QFile>

InitcpioJob::InitcpioJob( QObject* parent )
    : Calamares::CppJob( parent )
{
}

InitcpioJob::~InitcpioJob() {}


QString
InitcpioJob::prettyName() const
{
    return tr( "Creating initramfs with mkinitcpio." );
}

/** @brief Sets secure permissions on each initramfs
 *
 * Iterates over each initramfs contained directly in the directory @p d.
 * For each initramfs found, the permissions are set to owner read/write only.
 *
 */
void
fixPermissions( const QDir& d )
{
    const auto initramList = d.entryInfoList( { "initramfs*" }, QDir::Files );
    for ( const auto& fi : initramList )
    {
        QFile f( fi.absoluteFilePath() );
        if ( f.exists() )
        {
            cDebug() << "initcpio setting permissions for" << f.fileName();
            f.setPermissions( QFileDevice::ReadOwner | QFileDevice::WriteOwner );
        }
    }
}

Calamares::JobResult
InitcpioJob::exec()
{
    CalamaresUtils::UMask m( CalamaresUtils::UMask::Safe );

    if ( m_unsafe )
    {
        cDebug() << "Skipping mitigations for unsafe initramfs permissions.";
    }
    else
    {
        QDir d( CalamaresUtils::System::instance()->targetPath( "/boot" ) );
        if ( d.exists() )
        {
            fixPermissions( d );
        }
    }

    // If the kernel option isn't set to a specific kernel, run mkinitcpio on all kernels
    QStringList command = { "mkinitcpio" };
    if ( m_kernel.isEmpty() || m_kernel == "all" )
    {
        command.append( "-P" );
    }
    else
    {
        command.append( { "-p", m_kernel } );
    }

    cDebug() << "Updating initramfs with kernel" << m_kernel;
    auto r = CalamaresUtils::System::instance()->targetEnvCommand( command, QString(), QString() /* no timeout , 0 */ );
    return r.explainProcess( "mkinitcpio", std::chrono::seconds( 10 ) /* fake timeout */ );
}

void
InitcpioJob::setConfigurationMap( const QVariantMap& configurationMap )
{
    m_kernel = CalamaresUtils::getString( configurationMap, "kernel" );

    m_unsafe = CalamaresUtils::getBool( configurationMap, "be_unsafe", false );
}

CALAMARES_PLUGIN_FACTORY_DEFINITION( InitcpioJobFactory, registerPlugin< InitcpioJob >(); )
