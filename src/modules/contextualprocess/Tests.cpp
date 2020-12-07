/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2017-2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "Tests.h"

#include "Binding.h"
#include "ContextualProcessJob.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/CalamaresUtilsSystem.h"
#include "utils/CommandList.h"
#include "utils/Logger.h"
#include "utils/Yaml.h"

#include <QtTest/QtTest>

#include <QFileInfo>
#include <QStringList>

QTEST_GUILESS_MAIN( ContextualProcessTests )

using CommandList = CalamaresUtils::CommandList;

ContextualProcessTests::ContextualProcessTests() {}

ContextualProcessTests::~ContextualProcessTests() {}

void
ContextualProcessTests::initTestCase()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );

    // Ensure we have a system object, expect it to be a "bogus" one
    CalamaresUtils::System* system = CalamaresUtils::System::instance();
    QVERIFY( system );
    QVERIFY( system->doChroot() );

    // Ensure we have a system-wide GlobalStorage with /tmp as root
    if ( !Calamares::JobQueue::instance() )
    {
        cDebug() << "Creating new JobQueue";
        (void)new Calamares::JobQueue();
    }
    Calamares::GlobalStorage* gs
        = Calamares::JobQueue::instance() ? Calamares::JobQueue::instance()->globalStorage() : nullptr;
    QVERIFY( gs );
}

void
ContextualProcessTests::testProcessListSampleConfig()
{
    YAML::Node doc;

    QStringList dirs { "src/modules/contextualprocess", "." };
    for ( const auto& dir : dirs )
    {
        QString filename = dir + "/contextualprocess.conf";
        if ( QFileInfo::exists( filename ) )
        {
            doc = YAML::LoadFile( filename.toStdString() );
            break;
        }
    }

    ContextualProcessJob job;
    job.setConfigurationMap( CalamaresUtils::yamlMapToVariant( doc ) );

    QCOMPARE( job.count(), 2 );  // Only "firmwareType" and "branding.shortVersion"
    QCOMPARE( job.count( "firmwareType" ), 4 );
    QCOMPARE( job.count( "branding.shortVersion" ), 2 );  // in the example config
}

void
ContextualProcessTests::testFetch()
{
    Logger::setupLogLevel( Logger::LOGVERBOSE );

    QVariantMap m;
    // Some keys without sub-map
    m.insert( QStringLiteral( "carrot" ), true );
    m.insert( QStringLiteral( "tomato" ), QStringLiteral( "fruit" ) );

    // A key with sub-map
    {
        QVariantMap names;
        names.insert( QStringLiteral( "blackcurrant" ), QStringLiteral( "black" ) );
        names.insert( QStringLiteral( "redcurrant" ), QStringLiteral( "red" ) );
        names.insert( QStringLiteral( "knoebels" ), QStringLiteral( "green" ) );
        names.insert( QStringLiteral( "strawberry" ), QStringLiteral( "red" ) );
        m.insert( QStringLiteral( "berries" ), names );
    }

    // Another key with sub-map
    {
        QVariantMap names;
        names.insert( QStringLiteral( "ext4" ), 1 );
        names.insert( QStringLiteral( "zfs" ), 2 );
        names.insert( QStringLiteral( "swap" ), 2 );
        m.insert( QStringLiteral( "filesystem_use" ), names );
    }

    QCOMPARE( m.count(), 4 );

    Calamares::GlobalStorage* gs
        = Calamares::JobQueue::instance() ? Calamares::JobQueue::instance()->globalStorage() : nullptr;
    QVERIFY( gs );

    // Copy the built-up-map into GS
    for ( auto it = m.cbegin(); it != m.cend(); ++it )
    {
        gs->insert( it.key(), it.value() );
    }

    // Testing of fetch()
    {
        ContextualProcessBinding b( QStringLiteral( "carrot" ) );
        QString s;
        QVERIFY( b.fetch( gs, s ) );
        QCOMPARE( s, QStringLiteral( "true" ) );  // String representation of boolean true
    }
    {
        ContextualProcessBinding b( QStringLiteral( "tomato" ) );
        QString s;
        QVERIFY( b.fetch( gs, s ) );
        QCOMPARE( s, QStringLiteral( "fruit" ) );
    }
    {
        // Key not found
        ContextualProcessBinding b( QStringLiteral( "parsnip" ) );
        QString s = QStringLiteral( "white" );
        QVERIFY( !b.fetch( gs, s ) );
        QCOMPARE( s, QString() );
        QVERIFY( s.isEmpty() );
    }
    {
        // Submap gets smashed
        ContextualProcessBinding b( QStringLiteral( "berries" ) );
        QString s;
        QVERIFY( b.fetch( gs, s ) );
        QVERIFY( s.isEmpty() );  // No string representation
    }
    {
        // Compound lookup
        ContextualProcessBinding b( QStringLiteral( "berries.strawberry" ) );
        QString s;
        QVERIFY( b.fetch( gs, s ) );
        QCOMPARE( s, QStringLiteral( "red" ) );
    }
    {
        ContextualProcessBinding b( QStringLiteral( "berries.knoebels" ) );
        QString s;
        QVERIFY( b.fetch( gs, s ) );
        QCOMPARE( s, QStringLiteral( "green" ) );
    }
    {
        ContextualProcessBinding b( QStringLiteral( "filesystem_use.ext4" ) );
        QString s;
        QVERIFY( b.fetch( gs, s ) );
        QCOMPARE( s, QStringLiteral( "1" ) );
    }
    {
        ContextualProcessBinding b( QStringLiteral( "filesystem_use.zfs" ) );
        QString s;
        QVERIFY( b.fetch( gs, s ) );
        QCOMPARE( s, QStringLiteral( "2" ) );
    }
    {
        // Key not found, compound
        ContextualProcessBinding b( QStringLiteral( "filesystem_use.ufs" ) );
        QString s = QStringLiteral( "ufs" );
        QVERIFY( !b.fetch( gs, s ) );
        QCOMPARE( s, QString() );
        QVERIFY( s.isEmpty() );
    }
}
