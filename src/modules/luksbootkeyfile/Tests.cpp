/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2022 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "GlobalStorage.h"
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
    void testIsEncrypted();
    void testAnyPartition();
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

void
LuksBootKeyFileTests::testIsEncrypted()
{
    QVariantMap m;  // As if this is a partition data
    const QString key = QStringLiteral( "luksMapperName" );
    const QString name = QStringLiteral( "any-name" );

    QVERIFY( !isEncrypted( m ) );

    // Even an empty string is considered encrypted
    m.insert( key, QString() );
    QVERIFY( isEncrypted( m ) );

    m.insert( key, name );
    QVERIFY( isEncrypted( m ) );

    m.insert( key, QString() );
    QVERIFY( isEncrypted( m ) );

    m.remove( key );
    QVERIFY( !isEncrypted( m ) );
}


void
LuksBootKeyFileTests::testAnyPartition()
{
    // This is kind of annoying: we need to build up
    // partition data in GS because the functions we're testing
    // go straight to GS.
    auto* gs = Calamares::JobQueue::instanceGlobalStorage();
    QVERIFY( gs );

    const QString partitionsKey = QStringLiteral( "partitions" );
    const QString mountPointKey = QStringLiteral( "mountPoint" );
    const QString boot = QStringLiteral( "/boot" );
    const QString root = QStringLiteral( "/" );

    QVariantList partitions;
    QVariantMap p;
    QVERIFY( !gs->contains( partitionsKey ) );

    // Empty list!
    QVERIFY( !anyPartition( []( const QVariantMap& ) { return true; } ) );

    gs->insert( partitionsKey, partitions );
    QVERIFY( !anyPartition( []( const QVariantMap& ) { return true; } ) );  // Still an empty list

    partitions.append( p );
    QCOMPARE( partitions.count(), 1 );
    gs->insert( partitionsKey, partitions );
    QVERIFY( anyPartition( []( const QVariantMap& ) { return true; } ) );  // Now a one-element list
    QVERIFY( !anyPartition( []( const QVariantMap& ) { return false; } ) );  // Now a one-element list

    p.insert( mountPointKey, boot );
    QVERIFY( hasMountPoint( p, boot ) );
    partitions.append( p );
    QCOMPARE( partitions.count(), 2 );

    // Note that GS is not updated yet, so we expect this to fail
    QEXPECT_FAIL( "", "GS not updated", Continue );
    QVERIFY( anyPartition(
        []( const QVariantMap& partdata )
        {
            cDebug() << partdata;
            return hasMountPoint( partdata, QStringLiteral( "/boot" ) );
        } ) );

    gs->insert( partitionsKey, partitions );  // Update GS
    QVERIFY( anyPartition(
        []( const QVariantMap& partdata )
        {
            cDebug() << partdata;
            return hasMountPoint( partdata, QStringLiteral( "/boot" ) );
        } ) );
    QVERIFY( !anyPartition( []( const QVariantMap& partdata )
                            { return hasMountPoint( partdata, QStringLiteral( "/" ) ); } ) );
    QVERIFY( !anyPartition( []( const QVariantMap& partdata ) { return hasMountPoint( partdata, QString() ); } ) );

    QVERIFY( !hasEncryptedRoot() );
    QVERIFY( hasUnencryptedSeparateBoot() );
}

QTEST_GUILESS_MAIN( LuksBootKeyFileTests )

#include "utils/moc-warnings.h"

#include "Tests.moc"
