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
    s_threshold = level + 1;  // Comparison is < in log() function
}

bool
logLevelEnabled( unsigned int level )
{
    return level < s_threshold;
}

unsigned int
logLevel()
{
    return s_threshold > 0 ? s_threshold - 1 : 0;
}

static void
log( const char* msg, unsigned int debugLevel, bool withTime = true )
{
    if ( logLevelEnabled( debugLevel ) )
    {
        QMutexLocker lock( &s_mutex );

        // If we don't format the date as a Qt::ISODate then we get a crash when
        // logging at exit as Qt tries to use QLocale to format, but QLocale is
        // on its way out.
        logfile << QDate::currentDate().toString( Qt::ISODate ).toUtf8().data() << " - "
                << QTime::currentTime().toString().toUtf8().data() << " ["
                << QString::number( debugLevel ).toUtf8().data() << "]: " << msg << std::endl;

        logfile.flush();

        if ( withTime )
        {
            std::cout << QTime::currentTime().toString().toUtf8().data() << " ["
                      << QString::number( debugLevel ).toUtf8().data() << "]: ";
        }
        std::cout << msg << std::endl;
    }
}


static void
CalamaresLogHandler( QtMsgType type, const QMessageLogContext&, const QString& msg )
{
    static QMutex s_mutex;

    QByteArray ba = msg.toUtf8();
    const char* message = ba.constData();

    QMutexLocker locker( &s_mutex );

    switch ( type )
    {
    case QtInfoMsg:
        log( message, LOGVERBOSE );
        break;
    case QtDebugMsg:
        log( message, LOGDEBUG );
        break;
    case QtWarningMsg:
        log( message, LOGWARNING );
        break;
    case QtCriticalMsg:
    case QtFatalMsg:
        log( message, LOGERROR );
        break;
    }
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
    if ( logLevelEnabled( m_debugLevel ) )
    {
        if ( m_funcinfo )
        {
            m_msg.prepend( s_Continuation );  // Prepending, so back-to-front
            m_msg.prepend( m_funcinfo );
        }
        log( m_msg.toUtf8().data(), m_debugLevel, m_funcinfo );
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

}  // namespace Logger
