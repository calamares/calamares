/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Bill Auger
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "Paste.h"

#include "Branding.h"
#include "utils/Logger.h"

#include <QApplication>
#include <QClipboard>
#include <QFile>
#include <QStringList>
#include <QTcpSocket>
#include <QUrl>

/** @brief Reads the logfile, returns its contents.
 *
 * Returns an empty QByteArray() on any kind of error.
 */
static QByteArray
logFileContents()
{
    QFile pasteSourceFile( Logger::logFile() );
    if ( !pasteSourceFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        cError() << "Could not open log file";
        return QByteArray();
    }
    // TODO: read the **last** 16kiB?
    return pasteSourceFile.read( 16384 /* bytes */ );
}

namespace CalamaresUtils
{

QString
ficheLogUpload( QObject* parent )
{
    auto [ type, serverUrl ] = Calamares::Branding::instance()->uploadServer();

    QByteArray pasteData = logFileContents();
    if ( pasteData.isEmpty() )
    {
        // An error has already been logged
        return QString();
    }

    QTcpSocket* socket = new QTcpSocket( parent );
    socket->connectToHost( serverUrl.host(), serverUrl.port() );

    if ( !socket->waitForConnected() )
    {
        cError() << "Could not connect to paste server";
        socket->close();
        return QString();
    }

    cDebug() << "Connected to paste server" << serverUrl.host();

    socket->write( pasteData );

    if ( !socket->waitForBytesWritten() )
    {
        cError() << "Could not write to paste server";
        socket->close();
        return QString();
    }

    cDebug() << Logger::SubEntry << "Paste data written to paste server";

    if ( !socket->waitForReadyRead() )
    {
        cError() << "No data from paste server";
        socket->close();
        return QString();
    }

    cDebug() << Logger::SubEntry << "Reading response from paste server";
    QByteArray responseText = socket->readLine( 1024 );
    socket->close();

    QUrl pasteUrl = QUrl( QString( responseText ).trimmed(), QUrl::StrictMode );
    QString pasteUrlStr = pasteUrl.toString();

    QString pasteUrlFmt = parent->tr( "Install log posted to\n\n%1\n\nLink copied to clipboard" );
    QString pasteUrlMsg = pasteUrlFmt.arg( pasteUrlStr );

    if ( pasteUrl.isValid() && pasteUrl.host() == serverUrl.host() )
    {
        QClipboard* clipboard = QApplication::clipboard();
        clipboard->setText( pasteUrlStr, QClipboard::Clipboard );

        if ( clipboard->supportsSelection() )
        {
            clipboard->setText( pasteUrlStr, QClipboard::Selection );
        }
    }
    else
    {
        cError() << "No data from paste server";
        return QString();
    }

    cDebug() << Logger::SubEntry << "Paste server results:" << pasteUrlMsg;
    return pasteUrlMsg;
}
}  // namespace CalamaresUtils
