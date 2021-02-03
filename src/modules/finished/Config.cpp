/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "Config.h"

#include "utils/Logger.h"
#include "utils/Variant.h"

const NamedEnumTable< Config::RestartMode >&
restartModes()
{
    using M = Config::RestartMode;
    static const NamedEnumTable< M > table { { "never", M::Never },
                                             { "user-unchecked", M::UserDefaultUnchecked },
                                             { "unchecked", M::UserDefaultUnchecked },
                                             { "user-checked", M::UserDefaultChecked },
                                             { "checked", M::UserDefaultChecked },
                                             { "always", M::Always }

    };
    return table;
}


Config::Config( QObject* parent )
    : QObject( parent )
{
}

void
Config::setConfigurationMap( const QVariantMap& configurationMap )
{
    RestartMode mode = RestartMode::Never;

    QString restartMode = CalamaresUtils::getString( configurationMap, "restartNowMode" );
    if ( restartMode.isEmpty() )
    {
        if ( configurationMap.contains( "restartNowEnabled" ) )
        {
            cWarning() << "Configuring the finished module with deprecated restartNowEnabled settings";
        }

        bool restartNowEnabled = CalamaresUtils::getBool( configurationMap, "restartNowEnabled", false );
        bool restartNowChecked = CalamaresUtils::getBool( configurationMap, "restartNowChecked", false );

        if ( !restartNowEnabled )
        {
            mode = RestartMode::Never;
        }
        else
        {
            mode = restartNowChecked ? RestartMode::UserDefaultChecked : RestartMode::UserDefaultUnchecked;
        }
    }
    else
    {
        bool ok = false;
        mode = restartModes().find( restartMode, ok );
        if ( !ok )
        {
            cWarning() << "Configuring the finished module with bad restartNowMode" << restartMode;
        }
    }

    m_restartNowMode = mode;

    if ( mode != RestartMode::Never )
    {
        QString restartNowCommand = CalamaresUtils::getString( configurationMap, "restartNowCommand" );
        if ( restartNowCommand.isEmpty() )
        {
            restartNowCommand = QStringLiteral( "shutdown -r now" );
        }
        m_restartNowCommand = restartNowCommand;
    }

    m_notifyOnFinished = CalamaresUtils::getBool( configurationMap, "notifyOnFinished", false );
}
