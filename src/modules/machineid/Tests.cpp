/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019, Adriaan de Groot <groot@kde.org>
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

#include "Workers.h"

#include "utils/Logger.h"


#include <QDir>
#include <QFile>
#include <QtTest/QtTest>

class MachineIdTests : public QObject
{
    Q_OBJECT
public:
    MachineIdTests() {}
    virtual ~MachineIdTests() {}

private Q_SLOTS:
    void initTestCase();

    void testRemoveFile();
    void testCopyFile();

    void testPoolSize();
};

void
MachineIdTests::initTestCase()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );
}

void
MachineIdTests::testCopyFile()
{
    QTemporaryDir d( QDir::tempPath() + QStringLiteral( "/test-XXXXXX" ) );
    cDebug() << "Temporary files as" << QDir::tempPath();
    cDebug() << "Temp dir file at  " << d.path();
    QVERIFY( !d.path().isEmpty() );

    QFile source( d.filePath( "example" ) );
    QVERIFY( !source.exists() );
    source.open( QIODevice::WriteOnly );
    source.write( "Derp" );
    source.close();
    QCOMPARE( source.size(), 4 );
    QVERIFY( source.exists() );

    // This should fail since "example" isn't standard in our test directory
    auto r0 = MachineId::copyFile( d.path(), "example" );
    QVERIFY( !r0 );

    if ( QFile::exists( "CMakeCache.txt" ) )
    {
        auto r1 = MachineId::copyFile( d.path(), "CMakeCache.txt" );
        QVERIFY( r1 );
        QVERIFY( QFile::exists( d.filePath( "CMakeCache.txt" ) ) );
    }
}

void
MachineIdTests::testRemoveFile()
{
}

void
MachineIdTests::testPoolSize()
{
#ifdef Q_OS_FREEBSD
    // It hardly makes sense, but also the /proc entry is missing
    QCOMPARE( MachineId::getUrandomPoolSize(), 512 );
#else
    // Based on a sample size of 1, Netrunner
    QCOMPARE( MachineId::getUrandomPoolSize(), 4096 );
#endif
}


QTEST_GUILESS_MAIN( MachineIdTests )

#include "Tests.moc"
#include "utils/moc-warnings.h"
