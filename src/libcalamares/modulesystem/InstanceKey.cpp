/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2018-2019, Adriaan de Groot <groot@kde.org>
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
