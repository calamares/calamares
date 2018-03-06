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

/**
 * Each command can have an associated timeout in seconds. The timeout
 * defaults to 10 seconds. Provide some convenience naming and construction.
 */
struct CommandLine : public QPair< QString, int >
{
    enum { TimeoutNotSet = -1 };

    /// An invalid command line
    CommandLine()
        : QPair< QString, int >( QString(), TimeoutNotSet )
    {
    }

    CommandLine( const QString& s )
        : QPair< QString, int >( s, TimeoutNotSet )
    {
    }

    CommandLine( const QString& s, int t )
        : QPair< QString, int >( s, t)
    {
    }

    QString command() const
    {
        return first;
    }

    int timeout() const
    {
        return second;
    }

    bool isValid() const
    {
        return !first.isEmpty();
    }
} ;

/** @brief Abbreviation, used internally. */
using CommandList_t = QList< CommandLine >;

/**
 * A list of commands; the list may have its own default timeout
 * for commands (which is then applied to each individual command
 * that doesn't have one of its own).
 */
class CommandList : protected CommandList_t
{
public:
    /** @brief empty command-list with timeout to apply to entries. */
    CommandList( bool doChroot = true, int timeout = 10 );
    CommandList( const QVariant& v, bool doChroot = true, int timeout = 10 );
    ~CommandList();

    bool doChroot() const
    {
        return m_doChroot;
    }

    Calamares::JobResult run();

    using CommandList_t::isEmpty;
    using CommandList_t::count;
    using CommandList_t::cbegin;
    using CommandList_t::cend;
    using CommandList_t::const_iterator;
    using CommandList_t::at;

protected:
    using CommandList_t::append;
    void append( const QString& );

private:
    bool m_doChroot;
    int m_timeout;
} ;

}  // namespace
#endif // COMMANDLIST_H
