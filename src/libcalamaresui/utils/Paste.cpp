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

#include <QApplication>
#include <QClipboard>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QTcpSocket>
#include <QUrl>
#include <QWidget>

using namespace CalamaresUtils::Units;

/** @brief Reads the logfile, returns its contents.
 *
 * Returns an empty QByteArray() on any kind of error.
 */
STATICTEST QByteArray
logFileContents( qint64 sizeLimit )
{
    const QString name = Logger::logFile();
    QFile pasteSourceFile( name );
    if ( !pasteSourceFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        cWarning() << "Could not open log file" << name;
        return QByteArray();
    }
    QFileInfo fi( pasteSourceFile );
    sizeLimit *= 1024;            //For KiB to bytes
    cDebug() << "Log upload size limit was set to " << sizeLimit << " bytes";
    if ( fi.size() > sizeLimit and sizeLimit > 0 )
    {
        // Fixme : this following line is not getting pasted
        cDebug() << "Only last " << sizeLimit << " bytes of log file (" << fi.size() << ") uploaded" ;
        pasteSourceFile.seek( fi.size() - sizeLimit );
    }
    return pasteSourceFile.read( sizeLimit );
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
    auto [ type, serverUrl, sizeLimit ] = Calamares::Branding::instance()->uploadServer();
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

    QByteArray pasteData = logFileContents( sizeLimit );
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

QString
CalamaresUtils::Paste::doLogUploadUI( QWidget* parent )
{
    // These strings originated in the ViewManager class
    QString pasteUrl = CalamaresUtils::Paste::doLogUpload( parent );
    QString pasteUrlMessage;
    if ( pasteUrl.isEmpty() )
    {
        pasteUrlMessage = QCoreApplication::translate( "Calamares::ViewManager",
                                                       "The upload was unsuccessful. No web-paste was done." );
    }
    else
    {
        QClipboard* clipboard = QApplication::clipboard();
        clipboard->setText( pasteUrl, QClipboard::Clipboard );

        if ( clipboard->supportsSelection() )
        {
            clipboard->setText( pasteUrl, QClipboard::Selection );
        }
        QString pasteUrlFmt = QCoreApplication::translate( "Calamares::ViewManager",
                                                           "Install log posted to\n\n%1\n\nLink copied to clipboard" );
        pasteUrlMessage = pasteUrlFmt.arg( pasteUrl );
    }

    QMessageBox::critical(
        nullptr, QCoreApplication::translate( "Calamares::ViewManager", "Install Log Paste URL" ), pasteUrlMessage );
    return pasteUrl;
}


bool
CalamaresUtils::Paste::isEnabled()
{
    auto [ type, serverUrl, sizeLimit ] = Calamares::Branding::instance()->uploadServer();
    return type != Calamares::Branding::UploadServerType::None;
}
