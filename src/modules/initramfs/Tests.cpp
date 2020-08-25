/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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

InitramfsTests::InitramfsTests() {}

InitramfsTests::~InitramfsTests() {}

void
InitramfsTests::initTestCase()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );

    (void)new Calamares::JobQueue();
    (void)new CalamaresUtils::System( true );
}

static const char contents[] = "UMASK=0077\n";
static const char confFile[] = "/tmp/calamares-safe-umask";

void
InitramfsTests::cleanup()
{
    QFile::remove( confFile );
}

void
InitramfsTests::testCreateTargetFile()
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
    QCOMPARE( ulong( fi.size() ), sizeof( contents ) - 1 );  // don't count trailing NUL

    QFile::remove( path );
}
