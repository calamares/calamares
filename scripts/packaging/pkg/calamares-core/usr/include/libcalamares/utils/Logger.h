/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2010-2011 Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017-2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#ifndef UTILS_LOGGER_H
#define UTILS_LOGGER_H

#include "DllMacro.h"

#include <QDebug>
#include <QSharedPointer>

#include <memory>

namespace Logger
{
class Once;

struct FuncSuppressor
{
    explicit constexpr FuncSuppressor( const char[] );
    const char* m_s;
};

struct NoQuote_t
{
};
struct Quote_t
{
};

DLLEXPORT extern const FuncSuppressor Continuation;
DLLEXPORT extern const FuncSuppressor SubEntry;
DLLEXPORT extern const NoQuote_t NoQuote;
DLLEXPORT extern const Quote_t Quote;

enum
{
    LOG_DISABLE = 0,
    LOGERROR = 1,
    LOGWARNING = 2,
    LOGDEBUG = 6,
    LOGVERBOSE = 8
};

class DLLEXPORT CDebug : public QDebug
{
public:
    explicit CDebug( unsigned int debugLevel = LOGDEBUG, const char* func = nullptr );
    virtual ~CDebug();

    friend CDebug& operator<<( CDebug&&, const FuncSuppressor& );
    friend CDebug& operator<<( CDebug&&, const Once& );

    inline unsigned int level() const { return m_debugLevel; }

private:
    QString m_msg;
    unsigned int m_debugLevel;
    const char* m_funcinfo = nullptr;
};

inline CDebug&
operator<<( CDebug&& s, const FuncSuppressor& f )
{
    if ( s.m_funcinfo )
    {
        s.m_funcinfo = nullptr;
        s.m_msg = QString( f.m_s );
    }
    return s;
}

inline QDebug&
operator<<( QDebug& s, const FuncSuppressor& f )
{
    return s << f.m_s;
}

inline QDebug&
operator<<( QDebug& s, const NoQuote_t& )
{
    return s.noquote().nospace();
}

inline QDebug&
operator<<( QDebug& s, const Quote_t& )
{
    return s.quote().space();
}

/**
 * @brief The full path of the log file.
 */
DLLEXPORT QString logFile();

/**
 * @brief Start logging to the log file.
 *
 * Call this (once) to start logging to the log file (usually
 * ~/.cache/calamares/session.log ). An existing log file is
 * rolled over if it is too large.
 */
DLLEXPORT void setupLogfile();

/**
 * @brief Set a log level for future logging.
 *
 * Pass in a value from the LOG* enum, above. Use 0 to
 * disable logging. Values greater than LOGVERBOSE are
 * limited to LOGVERBOSE, which will log everything.
 *
 * Practical values are 0, 1, 2, and 6.
 */
DLLEXPORT void setupLogLevel( unsigned int level );

/** @brief Return the configured log-level. */
DLLEXPORT unsigned int logLevel();

/** @brief Would the given @p level really be logged? */
DLLEXPORT bool logLevelEnabled( unsigned int level );

/**
 * @brief Row-oriented formatted logging.
 *
 * Use DebugRow to produce multiple rows of 2-column output
 * in a debugging statement. For instance,
 *      cDebug() << DebugRow<int,int>(1,12)
 *               << DebugRow<int,int>(2,24)
 * will produce a single timestamped debug line with continuations.
 * Each DebugRow produces one line of output, with the two values.
 */
template < typename T, typename U >
struct DebugRow
{
public:
    explicit DebugRow( const T& t, const U& u )
        : first( t )
        , second( u )
    {
    }

    const T first;
    const U second;
};

/**
 * @brief List-oriented formatted logging.
 *
 * Use DebugList to produce multiple rows of output in a debugging
 * statement. For instance,
 *      cDebug() << DebugList( QStringList() << "foo" << "bar" )
 * will produce a single timestamped debug line with continuations.
 * Each element of the list of strings will be logged on a separate line.
 */
/* TODO: Calamares 3.3, bump requirements to C++17, and rename
 *       this to DebugList, dropping the convenience-definition
 *       below. In C++17, class template argument deduction is
 *       added, so `DebugList( whatever )` determines the right
 *       type already (also for QStringList).
 */
template < typename T >
struct DebugListT
{
    using list_t = QList< T >;

    explicit DebugListT( const list_t& l )
        : list( l )
    {
    }

    const list_t& list;
};

///@brief Convenience for QStringList, needs no template parameters
struct DebugList : public DebugListT< QString >
{
    explicit DebugList( const list_t& l )
        : DebugListT( l )
    {
    }
};

/**
 * @brief Map-oriented formatted logging.
 *
 * Use DebugMap to produce multiple rows of output in a debugging
 * statement from a map. The output is intentionally a bit-yaml-ish.
 *      cDebug() << DebugMap( map )
 * will produce a single timestamped debug line with continuations.
 * The continued lines will have a key (from the map) and a value
 * on each line.
 */
struct DebugMap
{
public:
    explicit DebugMap( const QVariantMap& m )
        : map( m )
    {
    }

    const QVariantMap& map;
};

/** @brief When logging commands, don't log everything.
 *
 * The command-line arguments to some commands may contain the
 * encrypted password set by the user. Don't log that password,
 * since the log may get posted to bug reports, or stored in
 * the target system.
 */
struct RedactedCommand
{
    RedactedCommand( const QStringList& l )
        : list( l )
    {
    }

    const QStringList& list;
};

QDebug& operator<<( QDebug& s, const RedactedCommand& l );

/** @brief When logging "private" identifiers, keep them consistent but private
 *
 * Send a string to a logger in such a way that each time it is logged,
 * it logs the same way, but without revealing the actual contents.
 * This can be applied to user names, UUIDs, etc.
 */
struct RedactedName
{
    RedactedName( const char* context, const QString& s );
    RedactedName( const QString& context, const QString& s );

    operator QString() const;

private:
    const uint m_id;
    const QString m_context;
};

inline QDebug&
operator<<( QDebug& s, const RedactedName& n )
{
    return s << NoQuote << QString( n ) << Quote;
}

/**
 * @brief Formatted logging of a pointer
 *
 * Pointers are printed as void-pointer, so just an address (unlike, say,
 * QObject pointers which show an address and some metadata) preceded
 * by an '@'. This avoids C-style (void*) casts in the code.
 *
 * Shared pointers are indicated by 'S@' and unique pointers by 'U@'.
 */
struct Pointer
{
public:
    explicit Pointer( const void* p )
        : ptr( p )
        , kind( 0 )
    {
    }

    template < typename T >
    explicit Pointer( const std::shared_ptr< T >& p )
        : ptr( p.get() )
        , kind( 'S' )
    {
    }

    template < typename T >
    explicit Pointer( const std::unique_ptr< T >& p )
        : ptr( p.get() )
        , kind( 'U' )
    {
    }

    const void* const ptr;
    const char kind;
};

/** @brief output operator for DebugRow */
template < typename T, typename U >
inline QDebug&
operator<<( QDebug& s, const DebugRow< T, U >& t )
{
    s << Continuation << t.first << ':' << ' ' << t.second;
    return s;
}

/** @brief output operator for DebugList, assuming operator<< for T exists */
template < typename T = QString >
inline QDebug&
operator<<( QDebug& s, const DebugListT< T >& c )
{
    for ( const auto& i : c.list )
    {
        s << Continuation << i;
    }
    return s;
}

/** @brief supporting method for outputting a DebugMap */
QString toString( const QVariant& v );

/** @brief output operator for DebugMap */
inline QDebug&
operator<<( QDebug& s, const DebugMap& t )
{
    for ( auto it = t.map.constBegin(); it != t.map.constEnd(); ++it )
    {
        s << Continuation << it.key().toUtf8().constData() << ':' << ' ' << toString( it.value() ).toUtf8().constData();
    }
    return s;
}

inline QDebug&
operator<<( QDebug& s, const Pointer& p )
{
    s << NoQuote;
    if ( p.kind )
    {
        s << p.kind;
    }
    s << '@' << p.ptr << Quote;
    return s;
}

/** @brief Convenience object for supplying SubEntry to a debug stream
 *
 * In a function with convoluted control paths, it may be unclear
 * when to supply SubEntry to a debug stream -- it is convenient
 * for the **first** debug statement from a given function to print
 * the function header, and all subsequent onces to get SubEntry.
 *
 * Create an object of type Once and send it (first) to all CDebug
 * objects; this will print the function header only once within the
 * lifetime of that Once object.
 */
class Once
{
public:
    Once()
        : m( true )
    {
    }
    friend CDebug& operator<<( CDebug&&, const Once& );

    /** @brief Restore the object to "fresh" state
     *
     * It may be necessary to allow the Once object to stream the
     * function header again -- for instance, after logging an error,
     * any following debug log might want to re-introduce the header.
     */
    void refresh() { m = true; }

    /** @brief Is this object "fresh"?
     *
     * Once a Once-object has printed (once) it is no longer fresh.
     */
    operator bool() const { return m; }

private:
    mutable bool m = false;
};

inline CDebug&
operator<<( CDebug&& s, const Once& o )
{
    if ( !logLevelEnabled( s.level() ) )
    {
        // This won't print, so it's not using the "onceness"
        return s;
    }

    if ( o.m )
    {
        o.m = false;
        return s;
    }
    s.m_funcinfo = nullptr;
    s << SubEntry;
    return s;
}

}  // namespace Logger

#define cVerbose() Logger::CDebug( Logger::LOGVERBOSE, Q_FUNC_INFO )
#define cDebug() Logger::CDebug( Logger::LOGDEBUG, Q_FUNC_INFO )
#define cWarning() Logger::CDebug( Logger::LOGWARNING, Q_FUNC_INFO )
#define cError() Logger::CDebug( Logger::LOGERROR, Q_FUNC_INFO )

#endif
