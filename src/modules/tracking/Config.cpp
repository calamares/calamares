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

Config::Config( QObject* parent )
    : QObject( parent )
{
}

void
Config::setConfigurationMap( const QVariantMap& m )
{
    m_generalPolicy = CalamaresUtils::getString( m, "policy" );

    if ( !QUrl( m_generalPolicy ).isValid() )
    {
        m_generalPolicy = QString();
    }

    emit generalPolicyChanged( m_generalPolicy );
}

QString
Config::generalPolicy() const
{
    return m_generalPolicy;
}
