/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2010-2011 Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#include "Logger.h"

#include "CalamaresVersionX.h"
#include "utils/Dirs.h"

#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QMutex>
#include <QRandomGenerator>
#include <QTextStream>
#include <QTime>
#include <QVariant>

#include <fstream>
#include <iostream>

static constexpr const int LOGFILE_SIZE = 1024 * 256;

static std::ofstream logfile;
static unsigned int s_threshold =
#ifdef QT_NO_DEBUG
    Logger::LOG_DISABLE;
#else
    Logger::LOGDEBUG;  // Comparison is < in log() function
#endif
static QMutex s_mutex;

static const char s_Continuation[] = "\n    ";
static const char s_SubEntry[] = "    .. ";


namespace Logger
{

void
setupLogLevel( unsigned int level )
{
    if ( level > LOGVERBOSE )
    {
        level = LOGVERBOSE;
    }
    s_threshold = level + 1;  // Comparison is < in logLevelEnabled() function
}

unsigned int
logLevel()
{
    // Undo the +1 in setupLogLevel()
    return s_threshold > 0 ? s_threshold - 1 : 0;
}

bool
logLevelEnabled( unsigned int level )
{
    return level < s_threshold;
}

/** @brief Should we call the log_implementation() function with this level?
 *
 * The implementation logs everything for which logLevelEnabled() is
 * true to the file **and** to stdout; it logs everything at debug-level
 * or below to the file regardless.
 */
static inline bool
log_enabled( unsigned int level )
{
    return level <= LOGDEBUG || logLevelEnabled( level );
}

static void
log_implementation( const char* msg, unsigned int debugLevel, const bool withTime )
{
    QMutexLocker lock( &s_mutex );

    const auto date = QDate::currentDate().toString( Qt::ISODate );
    const auto time = QTime::currentTime().toString();

    // If we don't format the date as a Qt::ISODate then we get a crash when
    // logging at exit as Qt tries to use QLocale to format, but QLocale is
    // on its way out.
    logfile << date.toUtf8().data() << " - " << time.toUtf8().data() << " [" << debugLevel << "]: " << msg << std::endl;

    logfile.flush();

    if ( logLevelEnabled( debugLevel ) )
    {
        if ( withTime )
        {
            std::cout << time.toUtf8().data() << " [" << debugLevel << "]: ";
        }
        // The endl is desired, since it also flushes (like the logfile, above)
        std::cout << msg << std::endl;
    }
}


static void
CalamaresLogHandler( QtMsgType type, const QMessageLogContext&, const QString& msg )
{
    unsigned int level = LOGVERBOSE;
    switch ( type )
    {
    case QtInfoMsg:
        level = LOGVERBOSE;
        break;
    case QtDebugMsg:
        level = LOGDEBUG;
        break;
    case QtWarningMsg:
        level = LOGWARNING;
        break;
    case QtCriticalMsg:
    case QtFatalMsg:
        level = LOGERROR;
        break;
    }

    if ( !log_enabled( level ) )
    {
        return;
    }

    log_implementation( msg.toUtf8().constData(), level, true );
}


QString
logFile()
{
    return CalamaresUtils::appLogDir().filePath( "session.log" );
}


void
setupLogfile()
{
    if ( QFileInfo( logFile().toLocal8Bit() ).size() > LOGFILE_SIZE )
    {
        QByteArray lc;
        {
            QFile f( logFile().toLocal8Bit() );
            f.open( QIODevice::ReadOnly | QIODevice::Text );
            lc = f.readAll();
            f.close();
        }

        QFile::remove( logFile().toLocal8Bit() );

        {
            QFile f( logFile().toLocal8Bit() );
            f.open( QIODevice::WriteOnly | QIODevice::Text );
            f.write( lc.right( LOGFILE_SIZE - ( LOGFILE_SIZE / 4 ) ) );
            f.close();
        }
    }

    // Since the log isn't open yet, this probably only goes to stdout
    cDebug() << "Using log file:" << logFile();

    // Lock while (re-)opening the logfile
    {
        QMutexLocker lock( &s_mutex );
        logfile.open( logFile().toLocal8Bit(), std::ios::app );
        if ( logfile.tellp() )
        {
            logfile << "\n\n" << std::endl;
        }
        logfile << "=== START CALAMARES " << CALAMARES_VERSION << std::endl;
    }

    qInstallMessageHandler( CalamaresLogHandler );
}

CDebug::CDebug( unsigned int debugLevel, const char* func )
    : QDebug( &m_msg )
    , m_debugLevel( debugLevel )
    , m_funcinfo( func )
{
    if ( debugLevel <= LOGERROR )
    {
        m_msg = QStringLiteral( "ERROR: " );
    }
    else if ( debugLevel <= LOGWARNING )
    {
        m_msg = QStringLiteral( "WARNING: " );
    }
}


CDebug::~CDebug()
{
    if ( log_enabled( m_debugLevel ) )
    {
        if ( m_funcinfo )
        {
            m_msg.prepend( s_Continuation );  // Prepending, so back-to-front
            m_msg.prepend( m_funcinfo );
        }
        log_implementation( m_msg.toUtf8().data(), m_debugLevel, bool( m_funcinfo ) );
    }
}

constexpr FuncSuppressor::FuncSuppressor( const char s[] )
    : m_s( s )
{
}

const constexpr FuncSuppressor Continuation( s_Continuation );
const constexpr FuncSuppressor SubEntry( s_SubEntry );
const constexpr NoQuote_t NoQuote {};
const constexpr Quote_t Quote {};

QString
toString( const QVariant& v )
{
    auto t = v.type();

    if ( t == QVariant::List )
    {
        QStringList s;
        auto l = v.toList();
        for ( auto lit = l.constBegin(); lit != l.constEnd(); ++lit )
        {
            s << lit->toString();
        }
        return s.join( ", " );
    }
    else
    {
        return v.toString();
    }
}

QDebug&
operator<<( QDebug& s, const RedactedCommand& l )
{
    // Special case logging: don't log the (encrypted) password.
    if ( l.list.contains( "usermod" ) )
    {
        for ( const auto& item : l.list )
            if ( item.startsWith( "$6$" ) )
            {
                s << "<password>";
            }
            else
            {
                s << item;
            }
    }
    else
    {
        s << l.list;
    }

    return s;
}

/** @brief Returns a stable-but-private hash of @p context and @p s
 *
 * Identical strings with the same context will be hashed the same,
 * so that they can be logged and still recognized as the-same.
 */
static uint
insertRedactedName( const QString& context, const QString& s )
{
    static uint salt = QRandomGenerator::global()->generate();  // Just once

    uint val = qHash( context, salt );
    return qHash( s, val );
}

RedactedName::RedactedName( const QString& context, const QString& s )
    : m_id( insertRedactedName( context, s ) )
    , m_context( context )
{
}

RedactedName::RedactedName( const char* context, const QString& s )
    : RedactedName( QString::fromLatin1( context ), s )
{
}

RedactedName::operator QString() const
{
    return QString( m_context + '$' + QString::number( m_id, 16 ) );
}

}  // namespace Logger
