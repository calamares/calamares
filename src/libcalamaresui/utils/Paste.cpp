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
#include <QRegularExpression>
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

QStringList UploadServersList = {
    "fiche"
    // In future more serverTypes can be added as Calamares support them
    // "none" serverType is explicitly not mentioned here
};

QString
ficheLogUpload( QObject* parent )
{
    const QString& ficheHost = Calamares::Branding::instance()->uploadServer( Calamares::Branding::URL );
    quint16 fichePort = Calamares::Branding::instance()->uploadServer( Calamares::Branding::Port ).toInt();

    QByteArray pasteData = logFileContents();
    if ( pasteData.isEmpty() )
    {
        // An error has already been logged
        return QString();
    }

    QTcpSocket* socket = new QTcpSocket( parent );
    socket->connectToHost( ficheHost, fichePort );

    if ( !socket->waitForConnected() )
    {
        cError() << "Could not connect to paste server";
        socket->close();
        return QString();
    }

    cDebug() << "Connected to paste server" << ficheHost;

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
    QRegularExpression pasteUrlRegex( "^http[s]?://" + ficheHost );

    QString pasteUrlFmt = parent->tr( "Install log posted to\n\n%1\n\nLink copied to clipboard" );
    QString pasteUrlMsg = pasteUrlFmt.arg( pasteUrlStr );

    if ( pasteUrl.isValid() && pasteUrlRegex.match( pasteUrlStr ).hasMatch() )
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
