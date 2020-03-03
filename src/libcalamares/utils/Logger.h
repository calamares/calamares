/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2014,      Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017-2019, Adriaan de Groot <groot@kde.org>
 *
 *   Calamares is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Calamares is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Calamares. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef UTILS_LOGGER_H
#define UTILS_LOGGER_H

#include <QDebug>

#include "DllMacro.h"

namespace Logger
{
struct FuncSuppressor
{
    explicit constexpr FuncSuppressor( const char[] );
    const char* m_s;
};

DLLEXPORT extern const FuncSuppressor Continuation;
DLLEXPORT extern const FuncSuppressor SubEntry;

enum
{
    LOG_DISABLE = 0,
    LOGERROR = 1,
    LOGWARNING = 2,
    LOGINFO = 3,
    LOGEXTRA = 5,
    LOGDEBUG = 6,
    LOGVERBOSE = 8
};

class DLLEXPORT CDebug : public QDebug
{
public:
    explicit CDebug( unsigned int debugLevel = LOGDEBUG, const char* func = nullptr );
    virtual ~CDebug();

    friend QDebug& operator<<( CDebug&&, const FuncSuppressor& );

private:
    QString m_msg;
    unsigned int m_debugLevel;
    const char* m_funcinfo = nullptr;
};

inline QDebug&
operator<<( CDebug&& s, const FuncSuppressor& f )
{
    s.m_funcinfo = nullptr;
    return s << f.m_s;
}

inline QDebug&
operator<<( QDebug& s, const FuncSuppressor& f )
{
    return s << f.m_s;
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

    const T& first;
    const U& second;
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
}  // namespace Logger

#define cDebug() Logger::CDebug( Logger::LOGDEBUG, Q_FUNC_INFO )
#define cWarning() Logger::CDebug( Logger::LOGWARNING, Q_FUNC_INFO )
#define cError() Logger::CDebug( Logger::LOGERROR, Q_FUNC_INFO )

#endif
