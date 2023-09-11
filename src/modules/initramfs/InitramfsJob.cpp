/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "InitramfsJob.h"

#include "utils/System.h"
#include "utils/Logger.h"
#include "utils/UMask.h"
#include "utils/Variant.h"

InitramfsJob::InitramfsJob( QObject* parent )
    : Calamares::CppJob( parent )
{
}

InitramfsJob::~InitramfsJob() {}

QString
InitramfsJob::prettyName() const
{
    return tr( "Creating initramfs." );
}

Calamares::JobResult
InitramfsJob::exec()
{
    Calamares::UMask m( Calamares::UMask::Safe );

    cDebug() << "Updating initramfs with kernel" << m_kernel;

    if ( m_unsafe )
    {
        cDebug() << "Skipping mitigations for unsafe initramfs permissions.";
    }
    else
    {
        // First make sure we generate a safe initramfs with suitable permissions.
        static const char confFile[] = "/etc/initramfs-tools/conf.d/calamares-safe-initramfs.conf";
        static const char contents[] = "UMASK=0077\n";
        if ( Calamares::System::instance()->createTargetFile( confFile, QByteArray( contents ) ).failed() )
        {
            cWarning() << Logger::SubEntry << "Could not configure safe UMASK for initramfs.";
            // But continue anyway.
        }
    }

    // And then do the ACTUAL work.
    auto r = Calamares::System::instance()->targetEnvCommand(
        { "update-initramfs", "-k", m_kernel, "-c", "-t" }, QString(), QString() /* no timeout, 0 */ );
    return r.explainProcess( "update-initramfs", std::chrono::seconds( 10 ) /* fake timeout */ );
}

void
InitramfsJob::setConfigurationMap( const QVariantMap& configurationMap )
{
    m_kernel = Calamares::getString( configurationMap, "kernel" );
    if ( m_kernel.isEmpty() )
    {
        m_kernel = QStringLiteral( "all" );
    }
    else if ( m_kernel == "$uname" )
    {
        auto r = Calamares::System::runCommand( Calamares::System::RunLocation::RunInHost,
                                                { "/bin/uname", "-r" },
                                                QString(),
                                                QString(),
                                                std::chrono::seconds( 3 ) );
        if ( r.getExitCode() == 0 )
        {
            m_kernel = r.getOutput();
            cDebug() << "*initramfs* using running kernel" << m_kernel;
        }
        else
        {
            m_kernel = QStringLiteral( "all" );
            cWarning() << "*initramfs* could not determine running kernel, using 'all'." << Logger::Continuation
                       << r.getExitCode() << r.getOutput();
        }
    }

    m_unsafe = Calamares::getBool( configurationMap, "be_unsafe", false );
}

CALAMARES_PLUGIN_FACTORY_DEFINITION( InitramfsJobFactory, registerPlugin< InitramfsJob >(); )
