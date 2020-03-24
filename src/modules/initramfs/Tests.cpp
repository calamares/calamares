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

#include "Tests.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "Settings.h"

#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"
#include "utils/Yaml.h"

#include <QtTest/QtTest>

#include <QFileInfo>
#include <QStringList>

QTEST_GUILESS_MAIN( InitramfsTests )

InitramfsTests::InitramfsTests()
{
}

InitramfsTests::~InitramfsTests()
{
}

void
InitramfsTests::initTestCase()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );

    (void) new Calamares::JobQueue();
    (void) new CalamaresUtils::System( true );
}

static const char contents[] = "UMASK=0077\n";
static const char confFile[] = "/tmp/calamares-safe-umask";

void InitramfsTests::cleanup()
{
    QFile::remove( confFile );
}

void InitramfsTests::testCreateTargetFile()
{
    static const char short_confFile[] = "/calamares-safe-umask";

    auto* s = CalamaresUtils::System::instance();
    auto r = s->createTargetFile( short_confFile, QByteArray( contents ) );
    QVERIFY( r.failed() );
    QVERIFY( !r );
    QString path = r.path();
    QVERIFY( path.isEmpty() );  // because no rootmountpoint is set

    Calamares::JobQueue::instance()->globalStorage()->insert( "rootMountPoint", "/tmp" );

    path = s->createTargetFile( short_confFile, QByteArray( contents ) ).path();
    QCOMPARE( path, QString( confFile ) );
    QVERIFY( path.endsWith( short_confFile ) );  // chroot, so path create relative to
    QVERIFY( path.startsWith( "/tmp/" ) );
    QVERIFY( QFile::exists( path ) );

    QFileInfo fi( path );
    QVERIFY( fi.exists() );
    QCOMPARE( ulong( fi.size() ), sizeof( contents )-1 );  // don't count trailing NUL

    QFile::remove( path );

}
