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
#include "DllMacro.h"
#include "utils/Logger.h"
#include "utils/Units.h"

#include <QFile>
#include <QFileInfo>
#include <QTcpSocket>
#include <QUrl>

using namespace CalamaresUtils::Units;

/** @brief Reads the logfile, returns its contents.
 *
 * Returns an empty QByteArray() on any kind of error.
 */
STATICTEST QByteArray
logFileContents()
{
    const QString name = Logger::logFile();
    QFile pasteSourceFile( name );
    if ( !pasteSourceFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        cWarning() << "Could not open log file" << name;
        return QByteArray();
    }
    QFileInfo fi( pasteSourceFile );
    if ( fi.size() > 16_KiB )
    {
        pasteSourceFile.seek( fi.size() - 16_KiB );
    }
    return pasteSourceFile.read( 16_KiB );
}


STATICTEST QString
ficheLogUpload( const QByteArray& pasteData, const QUrl& serverUrl, QObject* parent )
{
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
    if ( pasteUrl.isValid() && pasteUrl.host() == serverUrl.host() )
    {
        cDebug() << Logger::SubEntry << "Paste server results:" << pasteUrl;
        return pasteUrl.toString();
    }
    else
    {
        cError() << "No data from paste server";
        return QString();
    }
}

QString
CalamaresUtils::Paste::doLogUpload( QObject* parent )
{
    auto [ type, serverUrl ] = Calamares::Branding::instance()->uploadServer();
    if ( !serverUrl.isValid() )
    {
        cWarning() << "Upload configure with invalid URL";
        return QString();
    }
    if ( type == Calamares::Branding::UploadServerType::None )
    {
        // Early return to avoid reading the log file
        return QString();
    }

    QByteArray pasteData = logFileContents();
    if ( pasteData.isEmpty() )
    {
        // An error has already been logged
        return QString();
    }

    switch ( type )
    {
    case Calamares::Branding::UploadServerType::None:
        cWarning() << "No upload configured.";
        return QString();
    case Calamares::Branding::UploadServerType::Fiche:
        return ficheLogUpload( pasteData, serverUrl, parent );
    }
    return QString();
}
