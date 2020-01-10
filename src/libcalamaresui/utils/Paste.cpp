/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019, Bill Auger
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

#include "Paste.h"

#include "utils/Logger.h"

#include <QFile>
#include <QRegularExpression>
#include <QTcpSocket>
#include <QUrl>

namespace CalamaresUtils
{

QString
sendLogToPastebin( QObject* parent, const QString& ficheHost, quint16 fichePort )
{
    QString pasteUrlFmt = parent->tr( "Install log posted to:\n%1" );
    QFile pasteSourceFile( Logger::logFile() );
    if ( !pasteSourceFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        cError() << "Could not open log file";
        return QString();
    }

    QByteArray pasteData;
    while ( !pasteSourceFile.atEnd() )
    {
        pasteData += pasteSourceFile.readLine();
    }

    QTcpSocket* socket = new QTcpSocket( parent );
    socket->connectToHost( ficheHost, fichePort );

    if ( !socket->waitForConnected() )
    {
        cError() << "Could not connect to paste server";
        socket->close();
        return QString();
    }

    cDebug() << "Connected to paste server";

    socket->write( pasteData );

    if ( !socket->waitForBytesWritten() )
    {
        cError() << "Could not write to paste server";
        socket->close();
        return QString();
    }

    cDebug() << "Paste data written to paste server";

    if ( !socket->waitForReadyRead() )
    {
        cError() << "No data from paste server";
        socket->close();
        return QString();
    }

    cDebug() << "Reading response from paste server";

    char resp[ 1024 ];
    resp[ 0 ] = '\0';
    qint64 nBytesRead = socket->readLine( resp, 1024 );
    socket->close();

    QUrl pasteUrl = QUrl( QString( resp ).trimmed(), QUrl::StrictMode );
    QString pasteUrlStr = pasteUrl.toString();
    QRegularExpression pasteUrlRegex( "^http[s]?://" + ficheHost );
    QString pasteUrlMsg = QString( pasteUrlFmt ).arg( pasteUrlStr );

    if ( nBytesRead < 8 || !pasteUrl.isValid() || !pasteUrlRegex.match( pasteUrlStr ).hasMatch() )
    {
        cError() << "No data from paste server";
        return QString();
    }

    cDebug() << "Paste server results:" << pasteUrlMsg;
    return pasteUrlMsg;
}
}  // namespace CalamaresUtils
