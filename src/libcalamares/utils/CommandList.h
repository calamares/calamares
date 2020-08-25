/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#ifndef UTILS_COMMANDLIST_H
#define UTILS_COMMANDLIST_H

#include "Job.h"

#include <QStringList>
#include <QVariant>

#include <chrono>

namespace CalamaresUtils
{

/**
 * Each command can have an associated timeout in seconds. The timeout
 * defaults to 10 seconds. Provide some convenience naming and construction.
 */
struct CommandLine : public QPair< QString, std::chrono::seconds >
{
    static inline constexpr std::chrono::seconds TimeoutNotSet() { return std::chrono::seconds( -1 ); }

    /// An invalid command line
    CommandLine()
        : QPair( QString(), TimeoutNotSet() )
    {
    }

    CommandLine( const QString& s )
        : QPair( s, TimeoutNotSet() )
    {
    }

    CommandLine( const QString& s, std::chrono::seconds t )
        : QPair( s, t )
    {
    }

    QString command() const { return first; }

    std::chrono::seconds timeout() const { return second; }

    bool isValid() const { return !first.isEmpty(); }
};

/** @brief Abbreviation, used internally. */
using CommandList_t = QList< CommandLine >;

/**
 * A list of commands; the list may have its own default timeout
 * for commands (which is then applied to each individual command
 * that doesn't have one of its own).
 *
 * Documentation for the format of commands can be found in
 * `shellprocess.conf`.
 */
class CommandList : protected CommandList_t
{
public:
    /** @brief empty command-list with timeout to apply to entries. */
    CommandList( bool doChroot = true, std::chrono::seconds timeout = std::chrono::seconds( 10 ) );
    CommandList( const QVariant& v, bool doChroot = true, std::chrono::seconds timeout = std::chrono::seconds( 10 ) );
    ~CommandList();

    bool doChroot() const { return m_doChroot; }

    Calamares::JobResult run();

    using CommandList_t::at;
    using CommandList_t::cbegin;
    using CommandList_t::cend;
    using CommandList_t::const_iterator;
    using CommandList_t::count;
    using CommandList_t::isEmpty;

protected:
    using CommandList_t::append;
    void append( const QString& );

private:
    bool m_doChroot;
    std::chrono::seconds m_timeout;
};

}  // namespace CalamaresUtils
#endif
