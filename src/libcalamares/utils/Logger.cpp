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

#include "Logger.h"

#include <iostream>
#include <fstream>

#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QMutex>
#include <QTime>
#include <QVariant>

#include "utils/CalamaresUtils.h"
#include "CalamaresVersion.h"

#define LOGFILE_SIZE 1024 * 256

static std::ofstream logfile;
static unsigned int s_threshold =
#ifdef QT_NO_DEBUG
            Logger::LOG_DISABLE;
#else
            Logger::LOGEXTRA + 1;  // Comparison is < in log() function
#endif
static QMutex s_mutex;

namespace Logger
{

void
setupLogLevel(unsigned int level)
{
    if ( level > LOGVERBOSE )
        level = LOGVERBOSE;
    s_threshold = level + 1;  // Comparison is < in log() function
}

bool
logLevelEnabled(unsigned int level)
{
    return level < s_threshold;
}

unsigned int
logLevel()
{
    return s_threshold > 0 ? s_threshold - 1 : 0;
}

static void
log( const char* msg, unsigned int debugLevel, bool toDisk = true )
{
    if ( toDisk || debugLevel < s_threshold )
    {
        QMutexLocker lock( &s_mutex );

        // If we don't format the date as a Qt::ISODate then we get a crash when
        // logging at exit as Qt tries to use QLocale to format, but QLocale is
        // on its way out.
        logfile << QDate::currentDate().toString( Qt::ISODate ).toUtf8().data()
                << " - "
                << QTime::currentTime().toString().toUtf8().data()
                << " [" << QString::number( debugLevel ).toUtf8().data() << "]: "
                << msg << std::endl;

        logfile.flush();
    }

    if ( debugLevel <= LOGEXTRA || debugLevel < s_threshold )
    {
        QMutexLocker lock( &s_mutex );

        std::cout << QTime::currentTime().toString().toUtf8().data()
             << " [" << QString::number( debugLevel ).toUtf8().data() << "]: "
             << msg << std::endl;
        std::cout.flush();
    }
}


static void
CalamaresLogHandler( QtMsgType type, const QMessageLogContext& context, const QString& msg )
{
    static QMutex s_mutex;

    Q_UNUSED( context );

    QByteArray ba = msg.toUtf8();
    const char* message = ba.constData();

    QMutexLocker locker( &s_mutex );
    switch( type )
    {
        case QtDebugMsg:
            log( message, LOGVERBOSE );
            break;

        case QtInfoMsg:
            log( message, 1 );
            break;

        case QtCriticalMsg:
        case QtWarningMsg:
        case QtFatalMsg:
            log( message, 0 );
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
        logfile << "\n\n" << std::endl;
    logfile << "=== START CALAMARES " << CALAMARES_VERSION << std::endl;
    }

    qInstallMessageHandler( CalamaresLogHandler );
}

CLog::CLog( unsigned int debugLevel )
    : QDebug( &m_msg )
    , m_debugLevel( debugLevel )
{
}


CLog::~CLog()
{
    log( m_msg.toUtf8().data(), m_debugLevel );
}

CDebug::~CDebug()
{
}

const char* continuation = "\n    ";

QString toString( const QVariant& v )
{
    auto t = v.type();

    if ( t == QVariant::List )
    {
        QStringList s;
        auto l = v.toList();
        for ( auto lit = l.constBegin(); lit != l.constEnd(); ++lit )
            s << lit->toString();
        return s.join(", ");
    }
    else
        return v.toString();
}

}  // namespace
