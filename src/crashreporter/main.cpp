/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2015-2016, Teo Mrnjavac <teo@kde.org>
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

#include <libcrashreporter-gui/CrashReporter.h>

#include <libcrashreporter-gui/CrashReporterGzip.h>

#include "CrashReporterConfig.h"

#include <QTranslator>
#include <iostream>
#include <QApplication>
#include <QDir>
#include <QFileInfo>

#include "utils/CalamaresUtils.h"
#include "utils/Logger.h"

#include <numeric>

#ifdef Q_OS_WIN
    #include <windows.h>
    #include <unistd.h>
#endif


#ifdef Q_OS_LINUX
const char* k_usage =
    "Usage:\n"
    "  CrashReporter <dumpFilePath> <linuxBacktracePath>\n";
#else
const char* k_usage =
    "Usage:\n"
    "  CrashReporter <dumpFilePath>\n";
#endif

int main( int argc, char* argv[] )
{
#ifdef Q_OS_WIN // log to console window
    if ( fileno( stdout ) != -1 && _get_osfhandle( fileno( stdout ) ) != -1 )
    {
        /* stdout is fine, presumably redirected to a file or pipe */
    }
    else
    {
        typedef BOOL (WINAPI * AttachConsole_t) (DWORD);
        AttachConsole_t p_AttachConsole = (AttachConsole_t) GetProcAddress( GetModuleHandleW( L"kernel32.dll" ), "AttachConsole" );

        if ( p_AttachConsole != NULL && p_AttachConsole( ATTACH_PARENT_PROCESS ) )
        {
            _wfreopen ( L"CONOUT$", L"w", stdout );
            dup2( fileno( stdout ), 1 );
            _wfreopen ( L"CONOUT$", L"w", stderr );
            dup2( fileno( stderr ), 2 );
        }
    }
#endif

    // used by some Qt stuff, eg QSettings
    // leave first! As Settings object is created quickly
    QCoreApplication::setOrganizationName( QLatin1String( CALAMARES_ORGANIZATION_NAME ) );
    QCoreApplication::setOrganizationDomain( QLatin1String( CALAMARES_ORGANIZATION_DOMAIN ) );
    QCoreApplication::setApplicationName( QLatin1String( CALAMARES_APPLICATION_NAME ) );
    QCoreApplication::setApplicationVersion( QLatin1String( CALAMARES_VERSION ) );

    QApplication app( argc, argv );
    CalamaresUtils::installTranslator( QLocale::system(), QString(), &app );

#ifdef Q_OS_LINUX
    if ( app.arguments().size() != 8 )
#else
    if ( app.arguments().size() != 2 )
#endif
    {
        std::cout << k_usage;
        return 1;
    }
    cDebug() << "Arguments list:" << app.arguments().join( ", " );

    CrashReporter reporter( QUrl( CRASHREPORTER_SUBMIT_URL ),  app.arguments() );

    #ifdef CRASHREPORTER_ICON
    reporter.setLogo( QPixmap( CRASHREPORTER_ICON ) );
    #endif
    reporter.setWindowTitle( CRASHREPORTER_PRODUCT_NAME );
    reporter.setText("<html><head/><body><p><span style=\" font-weight:600;\">Sorry!"
                     "</span> " CRASHREPORTER_PRODUCT_NAME " crashed. Please tell us "
                     "about it! " CRASHREPORTER_PRODUCT_NAME " has created an error "
                     "report for you that can help improve the stability in the "
                     "future. You can now send this report directly to the "
                     CRASHREPORTER_PRODUCT_NAME " developers.</p><p>Can you tell us "
                     "what you were doing when this happened?</p></body></html>");
    reporter.setBottomText(QString());

    reporter.setReportData( "BuildID", CRASHREPORTER_BUILD_ID );
    reporter.setReportData( "ProductName",  CRASHREPORTER_PRODUCT_NAME );
    reporter.setReportData( "Version", CRASHREPORTER_VERSION_STRING );
    reporter.setReportData( "ReleaseChannel", CRASHREPORTER_RELEASE_CHANNEL);

    //reporter.setReportData( "timestamp", QByteArray::number( QDateTime::currentDateTime().toTime_t() ) );



        // add parameters

//        QList<Pair> pairs;
//        pairs  //<< Pair( "BuildID", buildId.toUtf8() )
//        << Pair( )
//        //<< Pair( "Version", CalamaresUtils::appFriendlyVersion().toLocal8Bit() )
//        //<< Pair( "Vendor", "Tomahawk" )
//        //<< Pair(  )

        //            << Pair("InstallTime", "1357622062")
        //            << Pair("Theme", "classic/1.0")
        //            << Pair("Version", "30")
        //            << Pair("id", "{ec8030f7-c20a-464f-9b0e-13a3a9e97384}")
        //            << Pair("Vendor", "Mozilla")
        //            << Pair("EMCheckCompatibility", "true")
        //            << Pair("Throttleable", "0")
        //            << Pair("URL", "http://code.google.com/p/crashme/")
        //            << Pair("version", "20.0a1")
        //            << Pair("CrashTime", "1357770042")
        //            << Pair("submitted_timestamp", "2013-01-09T22:21:18.646733+00:00")
        //            << Pair("buildid", "20130107030932")
        //            << Pair("timestamp", "1357770078.646789")
        //            << Pair("Notes", "OpenGL: NVIDIA Corporation -- GeForce 8600M GT/PCIe/SSE2 -- 3.3.0 NVIDIA 313.09 -- texture_from_pixmap\r\n")
        //            << Pair("StartupTime", "1357769913")
        //            << Pair("FramePoisonSize", "4096")
        //            << Pair("FramePoisonBase", "7ffffffff0dea000")
        //            << Pair("Add-ons", "%7B972ce4c6-7e08-4474-a285-3208198ce6fd%7D:20.0a1,crashme%40ted.mielczarek.org:0.4")
        //            << Pair("SecondsSinceLastCrash", "1831736")
        //            << Pair("ProductName", "WaterWolf")
        //            << Pair("legacy_processing", "0")
        //            << Pair("ProductID", "{ec8030f7-c20a-464f-9b0e-13a3a9e97384}")

        ;

    // send log
    QFile logFile( CalamaresUtils::appLogDir().filePath( "Calamares.log" ) );
    logFile.open( QFile::ReadOnly );
    reporter.setReportData( "upload_file_calamareslog",
                            gzip_compress( logFile.readAll() ),
                            "application/x-gzip",
                            QFileInfo( logFile ).fileName().toUtf8());
    logFile.close();

    reporter.show();

    return app.exec();
}
