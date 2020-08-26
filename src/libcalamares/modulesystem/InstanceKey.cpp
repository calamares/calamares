/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018-2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */
#include "InstanceKey.h"

namespace Calamares
{
namespace ModuleSystem
{

InstanceKey
InstanceKey::fromString( const QString& s )
{
    QStringList moduleEntrySplit = s.split( '@' );
    if ( moduleEntrySplit.length() < 1 || moduleEntrySplit.length() > 2 )
    {
        return InstanceKey();
    }
    // For length 1, first == last
    return InstanceKey( moduleEntrySplit.first(), moduleEntrySplit.last() );
}


QDebug&
operator<<( QDebug& s, const Calamares::ModuleSystem::InstanceKey& i )
{
    return s << i.toString();
}

}  // namespace ModuleSystem
}  // namespace Calamares
