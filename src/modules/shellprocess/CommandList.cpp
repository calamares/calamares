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

#include <QVariantList>

class CommandList::Private
{
public:
    Private( const QVariantList& l );
    ~Private();
} ;

CommandList::Private::Private(const QVariantList& l)
{
}

CommandList::Private::~Private()
{
}



CommandList::CommandList()
    : m_d( nullptr )
{
}

CommandList::CommandList::CommandList(const QVariant& v)
    : CommandList()
{
    if ( ( v.type() == QVariant::List ) )
    {
        const auto v_list = v.toList();
        if ( v_list.count() )
        {
            m_d = new Private( v_list );
        }
    }
}

CommandList::~CommandList()
{
    delete m_d;
    m_d = nullptr;  // TODO: UniquePtr
}

bool CommandList::isEmpty() const
{
    if ( !m_d )
        return true;

    return false;  // FIXME: actually count things
}
