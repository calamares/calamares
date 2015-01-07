/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2014,      Teo Mrnjavac <teo@kde.org>
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

#define LOGFILE_SIZE 1024 * 256

#define RELEASE_LEVEL_THRESHOLD 0
#define DEBUG_LEVEL_THRESHOLD LOGEXTRA

using namespace std;

ofstream logfile;
static int s_threshold = -1;
QMutex s_mutex;

namespace Logger
{

static void
log( const char *msg, unsigned int debugLevel, bool toDisk = true )
{
    if ( s_threshold < 0 )
    {
        if ( qApp->arguments().contains( "--debug" ) ||
             qApp->arguments().contains( "-d" ) )
            s_threshold = LOGVERBOSE;
        else
            #ifdef QT_NO_DEBUG
            s_threshold = RELEASE_LEVEL_THRESHOLD;
            #else
            s_threshold = DEBUG_LEVEL_THRESHOLD;
            #endif
    }

    if ( toDisk || (int)debugLevel <= s_threshold )
    {
        QMutexLocker lock( &s_mutex );

        // If we don't format the date as a Qt::ISODate then we get a crash when
        // logging at exit as Qt tries to use QLocale to format, but QLocale is
        // on its way out.
        logfile << QDate::currentDate().toString( Qt::ISODate ).toUtf8().data()
                << " - "
                << QTime::currentTime().toString().toUtf8().data()
                << " [" << QString::number( debugLevel ).toUtf8().data() << "]: "
                << msg << endl;

        logfile.flush();
    }

    if ( debugLevel <= LOGEXTRA || (int)debugLevel <= s_threshold )
    {
        QMutexLocker lock( &s_mutex );

        cout << QTime::currentTime().toString().toUtf8().data()
             << " [" << QString::number( debugLevel ).toUtf8().data() << "]: "
             << msg << endl;

        cout.flush();
    }
}


void
CalamaresLogHandler( QtMsgType type, const QMessageLogContext& context, const QString& msg )
{
    static QMutex s_mutex;

    QByteArray ba = msg.toUtf8();
    const char* message = ba.constData();

    QMutexLocker locker( &s_mutex );
    switch( type )
    {
        case QtDebugMsg:
            log( message, LOGVERBOSE );
            break;

        case QtCriticalMsg:
            log( message, 0 );
            break;

        case QtWarningMsg:
            log( message, 0 );
            break;

        case QtFatalMsg:
            log( message, 0 );
            break;
    }
}


QString
logFile()
{
    return CalamaresUtils::appLogDir().filePath( "Calamares.log" );
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

    logfile.open( logFile().toLocal8Bit(), ios::app );
    qInstallMessageHandler( CalamaresLogHandler );
}

}

using namespace Logger;

CLog::CLog( unsigned int debugLevel )
    : QDebug( &m_msg )
    , m_debugLevel( debugLevel )
{
}


CLog::~CLog()
{
    log( m_msg.toUtf8().data(), m_debugLevel );
}

