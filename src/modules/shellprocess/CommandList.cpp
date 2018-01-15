/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2018, Adriaan de Groot <groot@kde.org>
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

#include "CommandList.h"

#include "utils/Logger.h"

#include <QVariantList>

static QStringList get_variant_stringlist(const QVariantList& l)
{
    QStringList retl;
    unsigned int c = 0;
    for ( const auto& v : l )
    {
        if ( v.type() == QVariant::String )
            retl.append( v.toString() );
        else
            cDebug() << "WARNING Bad CommandList element" << c << v.type() << v;
        ++c;
    }
    return retl;
}

CommandList::CommandList( bool doChroot )
    : m_doChroot( doChroot )
{
}

CommandList::CommandList::CommandList( const QVariant& v, bool doChroot )
    : CommandList( doChroot )
{
    if ( v.type() == QVariant::List )
    {
        const auto v_list = v.toList();
        if ( v_list.count() )
        {
            append( get_variant_stringlist( v_list ) );
        }
        else
            cDebug() << "WARNING: Empty CommandList";
    }
    else if ( v.type() == QVariant::String )
    {
        append( v.toString() );
    }
    else
        cDebug() << "WARNING: CommandList does not understand variant" << v.type();
}

CommandList::~CommandList()
{
}
