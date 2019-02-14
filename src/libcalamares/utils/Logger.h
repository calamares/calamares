/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2014,      Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017-2018, Adriaan de Groot <groot@kde.org>
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

#ifndef CALAMARES_LOGGER_H
#define CALAMARES_LOGGER_H

#include <QDebug>

#include "DllMacro.h"

namespace Logger
{
    extern const char* continuation;

    enum
    {
        LOG_DISABLE = 0,
        LOGERROR = 1,
        LOGWARNING = 2,
        LOGINFO  = 3,
        LOGEXTRA = 5,
        LOGDEBUG = 6,
        LOGVERBOSE = 8
    } ;

    class DLLEXPORT CLog : public QDebug
    {
    public:
        explicit CLog( unsigned int debugLevel );
        virtual ~CLog();

    private:
        QString m_msg;
        unsigned int m_debugLevel;
    };

    class DLLEXPORT CDebug : public CLog
    {
    public:
        CDebug( unsigned int debugLevel = LOGDEBUG ) : CLog( debugLevel )
        {
            if ( debugLevel <= LOGERROR )
                *this << "ERROR:";
            else if ( debugLevel <= LOGWARNING )
                *this << "WARNING:";
        }
        virtual ~CDebug();
    };

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
    template<typename T, typename U>
    struct DebugRow
    {
    public:
        explicit DebugRow(const T& t, const U& u)
            : first(t)
            , second(u)
        {}

        const T& first;
        const U& second;
    } ;

    /**
     * @brief List-oriented formatted logging.
     *
     * Use DebugList to produce multiple rows of output in a debugging
     * statement. For instance,
     *      cDebug() << DebugList( QStringList() << "foo" << "bar" )
     * will produce a single timestamped debug line with continuations.
     * Each element of the list of strings will be logged on a separate line.
     */
    struct DebugList
    {
        explicit DebugList( const QStringList& l )
            : list(l)
        {}

        const QStringList& list;
    } ;

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
        explicit DebugMap(const QVariantMap& m)
            : map( m )
        {}

        const QVariantMap& map;
    } ;

    /** @brief output operator for DebugRow */
    template<typename T, typename U>
    inline QDebug&
    operator <<( QDebug& s, const DebugRow<T, U>& t )
    {
        s << continuation << t.first << ':' << ' ' << t.second;
        return s;
    }

    /** @brief output operator for DebugList */
    inline QDebug&
    operator <<( QDebug& s, const DebugList& c )
    {
        for( const auto& i : c.list )
            s << continuation << i;
        return s;
    }

    /** @brief supporting method for outputting a DebugMap */
    QString toString( const QVariant& v );

    /** @brief output operator for DebugMap */
    inline QDebug&
    operator <<( QDebug& s, const DebugMap& t )
    {
        for ( auto it = t.map.constBegin(); it != t.map.constEnd(); ++it )
            s << continuation << it.key().toUtf8().constData() << ':' << ' ' << toString( it.value() ).toUtf8().constData();
        return s;
    }
}

#define cDebug Logger::CDebug
#define cWarning() Logger::CDebug(Logger::LOGWARNING)
#define cError() Logger::CDebug(Logger::LOGERROR)

#endif // CALAMARES_LOGGER_H
