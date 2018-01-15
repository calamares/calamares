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

#ifndef COMMANDLIST_H
#define COMMANDLIST_H

#include "Job.h"

#include <QStringList>
#include <QVariant>

namespace CalamaresUtils
{

class CommandList : protected QStringList
{
public:
    CommandList( bool doChroot = true );
    CommandList( const QVariant& v, bool doChroot = true );
    ~CommandList();

    bool doChroot() const
    {
        return m_doChroot;
    }

    Calamares::JobResult run( const QObject* parent );

    using QStringList::isEmpty;
    using QStringList::count;
    using QStringList::cbegin;
    using QStringList::cend;
    using QStringList::const_iterator;

private:
    bool m_doChroot;
} ;

}  // namespace
#endif // COMMANDLIST_H
