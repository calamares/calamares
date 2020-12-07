/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
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

void
fixPermissions( const QDir& d )
{
    for ( const auto& fi : d.entryInfoList( { "initramfs*" }, QDir::Files ) )
    {
        QFile f( fi.absoluteFilePath() );
        if ( f.exists() )
        {
            cDebug() << "initcpio fixing permissions for" << f.fileName();
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

    cDebug() << "Updating initramfs with kernel" << m_kernel;
    auto r = CalamaresUtils::System::instance()->targetEnvCommand(
        { "mkinitcpio", "-p", m_kernel }, QString(), QString() /* no timeout , 0 */ );
    return r.explainProcess( "mkinitcpio", std::chrono::seconds( 10 ) /* fake timeout */ );
}

void
InitcpioJob::setConfigurationMap( const QVariantMap& configurationMap )
{
    m_kernel = CalamaresUtils::getString( configurationMap, "kernel" );
    if ( m_kernel.isEmpty() )
    {
        m_kernel = QStringLiteral( "all" );
    }
    else if ( m_kernel == "$uname" )
    {
        auto r = CalamaresUtils::System::runCommand( CalamaresUtils::System::RunLocation::RunInHost,
                                                     { "/bin/uname", "-r" },
                                                     QString(),
                                                     QString(),
                                                     std::chrono::seconds( 3 ) );
        if ( r.getExitCode() == 0 )
        {
            m_kernel = r.getOutput();
            cDebug() << "*initcpio* using running kernel" << m_kernel;
        }
        else
        {
            cWarning() << "*initcpio* could not determine running kernel, using 'all'." << Logger::Continuation
                       << r.getExitCode() << r.getOutput();
        }
    }

    m_unsafe = CalamaresUtils::getBool( configurationMap, "be_unsafe", false );
}

CALAMARES_PLUGIN_FACTORY_DEFINITION( InitcpioJobFactory, registerPlugin< InitcpioJob >(); )
