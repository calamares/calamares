/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#include "Paste.h"

#include "utils/Logger.h"

#include <QDateTime>
#include <QtTest/QtTest>

extern QByteArray logFileContents();
extern QString ficheLogUpload( const QByteArray& pasteData, const QUrl& serverUrl, QObject* parent );

class TestPaste : public QObject
{
    Q_OBJECT

public:
    TestPaste() {}
    ~TestPaste() override {}

private Q_SLOTS:
    void testGetLogFile();
    void testFichePaste();
};

void
TestPaste::testGetLogFile()
{
    QFile::remove( Logger::logFile() );
    // This test assumes nothing **else** has set up logging yet
    QByteArray contentsOfLogfileBefore = logFileContents();
    QVERIFY( contentsOfLogfileBefore.isEmpty() );

    Logger::setupLogLevel( Logger::LOGDEBUG );
    Logger::setupLogfile();

    QByteArray contentsOfLogfileAfterSetup = logFileContents();
    QVERIFY( !contentsOfLogfileAfterSetup.isEmpty() );
}

void
TestPaste::testFichePaste()
{
    QString blabla( "the quick brown fox tested Calamares and found it rubbery" );
    QDateTime now = QDateTime::currentDateTime();

    QByteArray d = ( blabla + now.toString() ).toUtf8();
    QString s = ficheLogUpload( d, QUrl( "http://termbin.com:9999" ), nullptr );

    cDebug() << "Paste data to" << s;
    QVERIFY( !s.isEmpty() );
}


QTEST_GUILESS_MAIN( TestPaste )

#include "utils/moc-warnings.h"

#include "TestPaste.moc"
