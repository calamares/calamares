/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Bill Auger
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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
