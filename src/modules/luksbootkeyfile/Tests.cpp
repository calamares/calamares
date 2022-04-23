/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2022 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "JobQueue.h"
#include "utils/Logger.h"

#include <QtTest/QtTest>

#undef STATICTEST
#define STATICTEST extern

// Implementation details
STATICTEST bool hasMountPoint( const QVariantMap& map, const QString& path );

STATICTEST bool isEncrypted( const QVariantMap& map );

STATICTEST bool anyPartition( bool ( *pred )( const QVariantMap& ) );

STATICTEST bool hasUnencryptedSeparateBoot();

STATICTEST bool hasEncryptedRoot();

class LuksBootKeyFileTests : public QObject
{
    Q_OBJECT
public:
    LuksBootKeyFileTests() {}
    ~LuksBootKeyFileTests() override {}

private Q_SLOTS:
    void initTestCase();

    void testMountPoint();
};

void
LuksBootKeyFileTests::initTestCase()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );
    cDebug() << "LuksBootKeyFile test started.";

    if ( !Calamares::JobQueue::instance() )
    {
        (void)new Calamares::JobQueue();
    }
}

void
LuksBootKeyFileTests::testMountPoint()
{
    QVariantMap m;  // As if this is a partition data
    const QString key = QStringLiteral( "mountPoint" );
    const QString boot = QStringLiteral( "/boot" );
    const QString root = QStringLiteral( "/" );

    QVERIFY( !hasMountPoint( m, QString() ) );
    QVERIFY( !hasMountPoint( m, boot ) );

    m.insert( key, boot );
    QVERIFY( hasMountPoint( m, boot ) );
    QVERIFY( !hasMountPoint( m, QString() ) );
    QVERIFY( !hasMountPoint( m, root ) );

    m.insert( key, root );
    QVERIFY( !hasMountPoint( m, boot ) );
    QVERIFY( !hasMountPoint( m, QString() ) );
    QVERIFY( hasMountPoint( m, root ) );

    m.remove( key );
    QVERIFY( !hasMountPoint( m, root ) );
}

QTEST_GUILESS_MAIN( LuksBootKeyFileTests )

#include "utils/moc-warnings.h"

#include "Tests.moc"
