/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "Config.h"

#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"
#include "utils/Variant.h"

Config::Config( QObject* parent )
    : QObject( parent )
{
}

void
Config::setConfigurationMap( const QVariantMap& configurationMap )
{
    m_lnfPath = CalamaresUtils::getString( configurationMap, "lnftool" );

    if ( m_lnfPath.isEmpty() )
    {
        cWarning() << "no lnftool given for plasmalnf module.";
    }

    m_liveUser = CalamaresUtils::getString( configurationMap, "liveuser" );
}

void
Config::setTheme( const QString& id )
{
    if ( m_themeId == id )
    {
        return;
    }

    m_themeId = id;
    if ( lnfToolPath().isEmpty() )
    {
        cWarning() << "no lnftool given for plasmalnf module.";
    }
    else
    {
        QStringList command;
        if ( !m_liveUser.isEmpty() )
        {
            command << "sudo"
                    << "-E"
                    << "-H"
                    << "-u" << m_liveUser;
        }
        command << lnfToolPath() << "--resetLayout"
                << "--apply" << id;
        auto r = CalamaresUtils::System::instance()->runCommand( command, std::chrono::seconds( 10 ) );

        if ( r.getExitCode() )
        {
            cWarning() << r.explainProcess( command, std::chrono::seconds( 10 ) );
        }
        else
        {
            cDebug() << "Plasma look-and-feel applied" << id;
        }
    }
    emit themeChanged( id );
}
