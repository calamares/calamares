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

#include "DllMacro.h"
#include "Job.h"

#include <QStringList>
#include <QVariant>

#include <chrono>
#include <optional>
#include <utility>

class KMacroExpanderBase;

namespace Calamares
{
/**
 * Each command can have an associated timeout in seconds. The timeout
 * defaults to 10 seconds. Provide some convenience naming and construction.
 */
class CommandLine
{
public:
    static inline constexpr std::chrono::seconds TimeoutNotSet() { return std::chrono::seconds( -1 ); }

    /// An invalid command line
    CommandLine() = default;

    CommandLine( const QString& s )
        : m_command( s )
    {
    }

    CommandLine( const QString& s, std::chrono::seconds t )
        : m_command( s )
        , m_timeout( t )
    {
    }

    CommandLine( const QString& s, const QStringList& env, std::chrono::seconds t )
        : m_command( s )
        , m_environment( env )
        , m_timeout( t )
    {
    }

    /** @brief Constructs a CommandLine from a map with keys
     *
     * Relevant keys are *command*, *environment* and *timeout*.
     */
    CommandLine( const QVariantMap& m );

    QString command() const { return m_command; }
    [[nodiscard]] QStringList environment() const { return m_environment; }
    std::chrono::seconds timeout() const { return m_timeout; }
    bool isVerbose() const { return m_verbose.value_or( false ); }

    bool isValid() const { return !m_command.isEmpty(); }

    /** @brief Returns a copy of this one command, with variables expanded
     *
     * The given macro-expander is used to expand the command-line.
     * This will normally be a Calamares::String::DictionaryExpander
     * instance, which handles the ROOT and USER variables.
     */
    DLLEXPORT CommandLine expand( KMacroExpanderBase& expander ) const;

    /** @brief As above, with a default macro-expander.
     *
     * The default macro-expander assumes RunInHost (e.g. ROOT will
     * expand to the RootMountPoint set in Global Storage).
     */
    DLLEXPORT CommandLine expand() const;

    /** @brief If nothing has set verbosity yet, update to @p verbose */
    void updateVerbose( bool verbose )
    {
        if ( !m_verbose.has_value() )
        {
            m_verbose = verbose;
        }
    }

private:
    QString m_command;
    QStringList m_environment;
    std::chrono::seconds m_timeout = TimeoutNotSet();
    std::optional< bool > m_verbose;
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
class DLLEXPORT CommandList : protected CommandList_t
{
public:
    /** @brief empty command-list with timeout to apply to entries. */
    CommandList( bool doChroot = true, std::chrono::seconds timeout = std::chrono::seconds( 10 ) );
    /** @brief command-list constructed from script-entries in @p v
     *
     * The global settings @p doChroot and @p timeout can be overridden by
     * the individual script-entries.
     */
    CommandList( const QVariant& v, bool doChroot = true, std::chrono::seconds timeout = std::chrono::seconds( 10 ) );
    CommandList( int ) = delete;
    CommandList( const QVariant&, int ) = delete;

    bool doChroot() const { return m_doChroot; }
    std::chrono::seconds defaultTimeout() const { return m_timeout; }

    Calamares::JobResult run();

    using CommandList_t::at;
    using CommandList_t::cbegin;
    using CommandList_t::cend;
    using CommandList_t::const_iterator;
    using CommandList_t::count;
    using CommandList_t::isEmpty;
    using CommandList_t::push_back;
    using CommandList_t::value_type;

    /** @brief Return a copy of this command-list, with variables expanded
     *
     * Each command-line in the list is expanded with the given @p expander.
     * @see CommandLine::expand() for details.
     */
    DLLEXPORT CommandList expand( KMacroExpanderBase& expander ) const;

    /** @brief As above, with a default macro-expander.
     *
     * Each command-line in the list is expanded with that default macro-expander.
     * @see CommandLine::expand() for details.
     */
    DLLEXPORT CommandList expand() const;

    /** @brief Applies default-value @p verbose to each entry without an explicit setting. */
    DLLEXPORT void updateVerbose( bool verbose );

private:
    bool m_doChroot;
    std::chrono::seconds m_timeout;
};

}  // namespace Calamares
#endif
