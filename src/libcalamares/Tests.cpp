/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2018-2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "Settings.h"
#include "modulesystem/InstanceKey.h"
#include "utils/Logger.h"

#include <QObject>
#include <QSignalSpy>
#include <QtTest/QtTest>

class TestLibCalamares : public QObject
{
    Q_OBJECT
public:
    TestLibCalamares() {}
    ~TestLibCalamares() override {}

private Q_SLOTS:
    void testGSModify();
    void testGSLoadSave();
    void testGSLoadSave2();
    void testGSLoadSaveYAMLStringList();

    void testInstanceKey();
    void testInstanceDescription();

    void testSettings();

    void testJobQueue();
};

void
TestLibCalamares::testGSModify()
{
    Calamares::GlobalStorage gs;
    QSignalSpy spy( &gs, &Calamares::GlobalStorage::changed );

    const QString key( "derp" );

    QCOMPARE( gs.count(), 0 );
    QVERIFY( !gs.contains( key ) );

    const int value = 17;
    gs.insert( key, value );
    QCOMPARE( gs.count(), 1 );
    QVERIFY( gs.contains( key ) );
    QCOMPARE( gs.value( key ).type(), QVariant::Int );
    QCOMPARE( gs.value( key ).toString(), QString( "17" ) );  // It isn't a string, but does convert
    QCOMPARE( gs.value( key ).toInt(), value );

    gs.remove( key );
    QCOMPARE( gs.count(), 0 );
    QVERIFY( !gs.contains( key ) );

    QCOMPARE( spy.count(), 2 );  // one insert, one remove
}

void
TestLibCalamares::testGSLoadSave()
{
    Calamares::GlobalStorage gs;
    const QString jsonfilename( "gs.test.json" );
    const QString yamlfilename( "gs.test.yaml" );

    gs.insert( "derp", 17 );
    gs.insert( "cow", "moo" );

    QVariantList l;
    for ( const auto& s : QStringList { "dopey", "sneezy" } )
    {
        l.append( s );
    }
    gs.insert( "dwarfs", l );

    QCOMPARE( gs.count(), 3 );

    QVERIFY( gs.saveJson( jsonfilename ) );
    Calamares::GlobalStorage gs2;
    QCOMPARE( gs2.count(), 0 );
    QVERIFY( gs2.loadJson( jsonfilename ) );
    QCOMPARE( gs2.count(), 3 );
    QCOMPARE( gs2.data(), gs.data() );

    QVERIFY( gs.saveYaml( yamlfilename ) );
    Calamares::GlobalStorage gs3;
    QCOMPARE( gs3.count(), 0 );
    QVERIFY( gs3.loadYaml( jsonfilename ) );
    QCOMPARE( gs3.count(), 3 );
    QCOMPARE( gs3.data(), gs.data() );

    // YAML can load as JSON!
    QVERIFY( gs3.loadYaml( jsonfilename ) );
    QCOMPARE( gs3.count(), 3 );
    QCOMPARE( gs3.data(), gs.data() );

    // Failures in loading
    QVERIFY( !gs3.loadJson( yamlfilename ) );

    Calamares::GlobalStorage gs4;
    gs4.insert( "derp", 32 );
    gs4.insert( "dorp", "Varsseveld" );
    QCOMPARE( gs4.count(), 2 );
    QVERIFY( gs4.contains( "dorp" ) );
    QCOMPARE( gs4.value( "derp" ).toInt(), 32 );
    QVERIFY( gs4.loadJson( jsonfilename ) );
    // 3 keys from the file, but one overwrite
    QCOMPARE( gs4.count(), 4 );
    QVERIFY( gs4.contains( "dorp" ) );
    QCOMPARE( gs4.value( "derp" ).toInt(), 17 );  // This one was overwritten
}

void
TestLibCalamares::testGSLoadSave2()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );

    const QString filename( "../src/libcalamares/testdata/yaml-list.conf" );
    if ( !QFile::exists( filename ) )
    {
        return;
    }

    Calamares::GlobalStorage gs1;
    const QString key( "dwarfs" );

    QVERIFY( gs1.loadYaml( filename ) );
    QCOMPARE( gs1.count(), 3 );  // From examining the file
    QVERIFY( gs1.contains( key ) );
    cDebug() << gs1.value( key ).type() << gs1.value( key );
    QCOMPARE( gs1.value( key ).type(), QVariant::List );

    const QString yamlfilename( "gs.test.yaml" );
    QVERIFY( gs1.saveYaml( yamlfilename ) );

    Calamares::GlobalStorage gs2;
    QVERIFY( gs2.loadYaml( yamlfilename ) );
    QVERIFY( gs2.contains( key ) );
    QCOMPARE( gs2.value( key ).type(), QVariant::List );
}

void
TestLibCalamares::testGSLoadSaveYAMLStringList()
{
    Calamares::GlobalStorage gs;
    const QString yamlfilename( "gs.test.yaml" );

    gs.insert( "derp", 17 );
    gs.insert( "cow", "moo" );
    gs.insert( "dwarfs", QStringList { "happy", "dopey", "sleepy", "sneezy", "doc", "thorin", "balin" } );

    QCOMPARE( gs.count(), 3 );
    QCOMPARE( gs.value( "dwarfs" ).toList().count(), 7 );  // There's seven dwarfs, right?
    QVERIFY( gs.value( "dwarfs" ).toStringList().contains( "thorin" ) );
    QVERIFY( !gs.value( "dwarfs" ).toStringList().contains( "gimli" ) );


    QVERIFY( gs.saveYaml( yamlfilename ) );

    Calamares::GlobalStorage gs2;
    QCOMPARE( gs2.count(), 0 );
    QVERIFY( gs2.loadYaml( yamlfilename ) );
    QCOMPARE( gs2.count(), 3 );
    QEXPECT_FAIL( "", "QStringList doesn't write out nicely", Continue );
    QCOMPARE( gs2.value( "dwarfs" ).toList().count(), 7 );  // There's seven dwarfs, right?
    QCOMPARE( gs2.value( "dwarfs" ).toString(), QStringLiteral( "<QStringList>" ) );  // .. they're gone
}

void
TestLibCalamares::testInstanceKey()
{
    using InstanceKey = Calamares::ModuleSystem::InstanceKey;
    {
        InstanceKey k;
        QVERIFY( !k.isValid() );
        QVERIFY( !k.isCustom() );
        QVERIFY( k.module().isEmpty() );
    }
    {
        InstanceKey k( QStringLiteral( "welcome" ), QString() );
        QVERIFY( k.isValid() );
        QVERIFY( !k.isCustom() );
        QCOMPARE( k.module(), QStringLiteral( "welcome" ) );
        QCOMPARE( k.id(), QStringLiteral( "welcome" ) );
    }
    {
        InstanceKey k( QStringLiteral( "shellprocess" ), QStringLiteral( "zfssetup" ) );
        QVERIFY( k.isValid() );
        QVERIFY( k.isCustom() );
        QCOMPARE( k.module(), QStringLiteral( "shellprocess" ) );
        QCOMPARE( k.id(), QStringLiteral( "zfssetup" ) );
    }

    {
        // This is a bad idea, names and ids with odd punctuation
        InstanceKey k( QStringLiteral( " o__O " ), QString() );
        QVERIFY( k.isValid() );
        QVERIFY( !k.isCustom() );
        QCOMPARE( k.module(), QStringLiteral( " o__O " ) );
    }
    {
        // .. but @ is disallowed
        InstanceKey k( QStringLiteral( "welcome@hi" ), QString() );
        QVERIFY( !k.isValid() );
        QVERIFY( !k.isCustom() );
        QVERIFY( k.module().isEmpty() );
    }

    {
        InstanceKey k = InstanceKey::fromString( "welcome" );
        QVERIFY( k.isValid() );
        QVERIFY( !k.isCustom() );
        QCOMPARE( k.module(), QStringLiteral( "welcome" ) );
        QCOMPARE( k.id(), QStringLiteral( "welcome" ) );
    }
    {
        InstanceKey k = InstanceKey::fromString( "welcome@welcome" );
        QVERIFY( k.isValid() );
        QVERIFY( !k.isCustom() );
        QCOMPARE( k.module(), QStringLiteral( "welcome" ) );
        QCOMPARE( k.id(), QStringLiteral( "welcome" ) );
    }

    {
        InstanceKey k = InstanceKey::fromString( "welcome@hi" );
        QVERIFY( k.isValid() );
        QVERIFY( k.isCustom() );
        QCOMPARE( k.module(), QStringLiteral( "welcome" ) );
        QCOMPARE( k.id(), QStringLiteral( "hi" ) );
    }
    {
        InstanceKey k = InstanceKey::fromString( "welcome@hi@hi" );
        QVERIFY( !k.isValid() );
        QVERIFY( !k.isCustom() );
        QVERIFY( k.module().isEmpty() );
        QVERIFY( k.id().isEmpty() );
    }
}

void
TestLibCalamares::testInstanceDescription()
{
    using InstanceDescription = Calamares::InstanceDescription;
    using InstanceKey = Calamares::ModuleSystem::InstanceKey;

    // With invalid keys
    //
    //
    {
        InstanceDescription d;
        QVERIFY( !d.isValid() );
        QVERIFY( !d.isCustom() );
        QCOMPARE( d.weight(), 0 );
        QVERIFY( d.configFileName().isEmpty() );
        QVERIFY( !d.explicitWeight() );
    }

    {
        InstanceDescription d( InstanceKey {} );  // most-vexing, use brace-init instead
        QVERIFY( !d.isValid() );
        QVERIFY( !d.isCustom() );
        QCOMPARE( d.weight(), 0 );
        QVERIFY( d.configFileName().isEmpty() );
        QVERIFY( !d.explicitWeight() );
    }

    // Private constructor
    //
    // This does set up the config file, to default values
    {
        InstanceDescription d( InstanceKey::fromString( "welcome" ) );
        QVERIFY( d.isValid() );
        QVERIFY( !d.isCustom() );
        QCOMPARE( d.weight(), 1 );  // **now** the constraints kick in
        QVERIFY( !d.configFileName().isEmpty() );
        QCOMPARE( d.configFileName(), QStringLiteral( "welcome.conf" ) );
        QVERIFY( !d.explicitWeight() );
    }

    {
        InstanceDescription d( InstanceKey::fromString( "welcome@hi" ) );
        QVERIFY( d.isValid() );
        QVERIFY( d.isCustom() );
        QCOMPARE( d.weight(), 1 );  // **now** the constraints kick in
        QVERIFY( !d.configFileName().isEmpty() );
        QCOMPARE( d.configFileName(), QStringLiteral( "welcome.conf" ) );
        QVERIFY( !d.explicitWeight() );
    }


    // From settings, normal program flow
    //
    //
    {
        QVariantMap m;

        InstanceDescription d = InstanceDescription::fromSettings( m );
        QVERIFY( !d.isValid() );
    }
    {
        QVariantMap m;
        m.insert( "name", "welcome" );

        InstanceDescription d = InstanceDescription::fromSettings( m );
        QVERIFY( !d.isValid() );
        QVERIFY( !d.explicitWeight() );
    }
    {
        QVariantMap m;
        m.insert( "module", "welcome" );

        InstanceDescription d = InstanceDescription::fromSettings( m );
        QVERIFY( d.isValid() );
        QVERIFY( !d.isCustom() );
        // Valid, but no weight set by settings
        QCOMPARE( d.weight(), 1 );
        QVERIFY( !d.explicitWeight() );

        QCOMPARE( d.key().module(), QString( "welcome" ) );
        QCOMPARE( d.key().id(), QString( "welcome" ) );
        QCOMPARE( d.configFileName(), QString( "welcome.conf" ) );
    }
    {
        QVariantMap m;
        m.insert( "module", "welcome" );
        m.insert( "weight", 1 );

        InstanceDescription d = InstanceDescription::fromSettings( m );
        QVERIFY( d.isValid() );
        QVERIFY( !d.isCustom() );

        //Valid, set explicitly
        QCOMPARE( d.weight(), 1 );
        QVERIFY( d.explicitWeight() );

        QCOMPARE( d.key().module(), QString( "welcome" ) );
        QCOMPARE( d.key().id(), QString( "welcome" ) );
        QCOMPARE( d.configFileName(), QString( "welcome.conf" ) );
    }
    {
        QVariantMap m;
        m.insert( "module", "welcome" );
        m.insert( "id", "hi" );
        m.insert( "weight", "17" );  // String, that's kind of bogus

        InstanceDescription d = InstanceDescription::fromSettings( m );
        QVERIFY( d.isValid() );
        QVERIFY( d.isCustom() );
        QCOMPARE( d.weight(), 17 );
        QCOMPARE( d.key().module(), QString( "welcome" ) );
        QCOMPARE( d.key().id(), QString( "hi" ) );
        QCOMPARE( d.configFileName(), QString( "welcome.conf" ) );
        QVERIFY( d.explicitWeight() );
    }
    {
        QVariantMap m;
        m.insert( "module", "welcome" );
        m.insert( "id", "hi" );
        m.insert( "weight", 134 );
        m.insert( "config", "hi.conf" );

        InstanceDescription d = InstanceDescription::fromSettings( m );
        QVERIFY( d.isValid() );
        QVERIFY( d.isCustom() );
        QCOMPARE( d.weight(), 100 );
        QCOMPARE( d.key().module(), QString( "welcome" ) );
        QCOMPARE( d.key().id(), QString( "hi" ) );
        QCOMPARE( d.configFileName(), QString( "hi.conf" ) );
        QVERIFY( d.explicitWeight() );
    }
}

void
TestLibCalamares::testSettings()
{
    {
        Calamares::Settings s( false );
        QVERIFY( !s.debugMode() );
        QVERIFY( !s.isValid() );
    }
    {
        Calamares::Settings s( true );
        QVERIFY( s.debugMode() );
        QVERIFY( s.moduleInstances().isEmpty() );
        QVERIFY( s.modulesSequence().isEmpty() );
        QVERIFY( s.brandingComponentName().isEmpty() );
        QVERIFY( !s.isValid() );

        s.setConfiguration( R"(---
branding: default  # needed for it to be considered valid
instances:
    - module: welcome
      id: hi
      weight: 75
    - module: welcome
      id: yo
      config: yolo.conf
sequence:
    - show:
        - welcome@hi
        - welcome@yo
        - dummycpp
        - summary
    - exec:
        - welcome@hi
)",
                            QStringLiteral( "<testdata>" ) );

        QVERIFY( s.debugMode() );
        QCOMPARE( s.moduleInstances().count(), 4 );  // there are 4 module instances mentioned
        QCOMPARE( s.modulesSequence().count(), 2 );  // 2 steps (show, exec)
        QVERIFY( !s.brandingComponentName().isEmpty() );
        QVERIFY( s.isValid() );

        // Make a lambda where we can adjust what it looks for from the outside,
        //   by capturing a reference.
        QString moduleKey = QString( "welcome" );
        auto moduleFinder = [ &moduleKey ]( const Calamares::InstanceDescription& d )
        { return d.isValid() && d.key().module() == moduleKey; };

        const auto it0 = std::find_if( s.moduleInstances().constBegin(), s.moduleInstances().constEnd(), moduleFinder );
        QVERIFY( it0 != s.moduleInstances().constEnd() );

        moduleKey = QString( "derp" );
        const auto it1 = std::find_if( s.moduleInstances().constBegin(), s.moduleInstances().constEnd(), moduleFinder );
        QVERIFY( it1 == s.moduleInstances().constEnd() );

        int validCount = 0;
        int customCount = 0;
        for ( const auto& d : s.moduleInstances() )
        {
            if ( d.isValid() )
            {
                validCount++;
            }
            if ( d.isCustom() )
            {
                customCount++;
            }
            QVERIFY( d.isCustom() ? d.isValid() : true );  // All custom entries are valid

            if ( !d.isCustom() )
            {
                QCOMPARE( d.configFileName(), QString( "%1.conf" ).arg( d.key().module() ) );
            }
            else
            {
                // Specific cases from this config file
                if ( d.key().id() == QString( "yo" ) )
                {
                    QCOMPARE( d.configFileName(), QString( "yolo.conf" ) );
                }
                else
                {
                    QCOMPARE( d.configFileName(), QString( "welcome.conf" ) );  // Not set in the settings data
                }
            }
        }
        QCOMPARE( customCount, 2 );
        QCOMPARE( validCount, 4 );  // welcome@hi is listed twice, in *show* and *exec*
    }
}

constexpr const std::chrono::milliseconds MAX_TEST_DURATION( 3000 );
constexpr const int MAX_TEST_SLEEP( 2 );  // seconds, < MAX_TEST_DURATION

Q_STATIC_ASSERT( std::chrono::seconds( MAX_TEST_SLEEP ) < MAX_TEST_DURATION );

class DummyJob : public Calamares::Job
{
public:
    DummyJob( QObject* parent )
        : Calamares::Job( parent )
    {
    }
    ~DummyJob() override;

    QString prettyName() const override;
    Calamares::JobResult exec() override;
};

DummyJob::~DummyJob() {}

QString
DummyJob::prettyName() const
{
    return QString( "DummyJob" );
}

Calamares::JobResult
DummyJob::exec()
{
    cDebug() << "Starting DummyJob";
    progress( 0.5 );
    QThread::sleep( MAX_TEST_SLEEP );
    cDebug() << ".. continuing DummyJob";
    progress( 0.75 );
    return Calamares::JobResult::ok();
}


void
TestLibCalamares::testJobQueue()
{
    // Run an empty queue
    {
        Calamares::JobQueue q;
        QVERIFY( !q.isRunning() );

        QSignalSpy spy_progress( &q, &Calamares::JobQueue::progress );
        QSignalSpy spy_finished( &q, &Calamares::JobQueue::finished );
        QSignalSpy spy_failed( &q, &Calamares::JobQueue::failed );

        QEventLoop loop;
        connect( &q, &Calamares::JobQueue::finished, &loop, &QEventLoop::quit );
        QTimer::singleShot( MAX_TEST_DURATION, &loop, &QEventLoop::quit );
        q.start();
        QVERIFY( q.isRunning() );
        loop.exec();
        QVERIFY( !q.isRunning() );
        QCOMPARE( spy_finished.count(), 1 );
        QCOMPARE( spy_failed.count(), 0 );
        QCOMPARE( spy_progress.count(), 1 );  // just one, 100% at queue end
    }

    // Run a dummy queue
    {
        Calamares::JobQueue q;
        QVERIFY( !q.isRunning() );

        q.enqueue( 8, Calamares::JobList() << Calamares::job_ptr( new DummyJob( this ) ) );
        QSignalSpy spy_progress( &q, &Calamares::JobQueue::progress );
        QSignalSpy spy_finished( &q, &Calamares::JobQueue::finished );
        QSignalSpy spy_failed( &q, &Calamares::JobQueue::failed );

        QEventLoop loop;
        connect( &q, &Calamares::JobQueue::finished, &loop, &QEventLoop::quit );
        QTimer::singleShot( MAX_TEST_DURATION, &loop, &QEventLoop::quit );
        q.start();
        QVERIFY( q.isRunning() );
        loop.exec();
        QVERIFY( !q.isRunning() );
        QCOMPARE( spy_finished.count(), 1 );
        QCOMPARE( spy_failed.count(), 0 );
        // 0% by the queue at job start
        // 50% by the job itself
        // 90% by the job itself
        // 100% by the queue at job end
        // 100% by the queue at queue end
        QCOMPARE( spy_progress.count(), 5 );
    }

    {
        Calamares::JobQueue q;
        QVERIFY( !q.isRunning() );

        q.enqueue( 8, Calamares::JobList() << Calamares::job_ptr( new DummyJob( this ) ) );
        q.enqueue( 12,
                   Calamares::JobList() << Calamares::job_ptr( new DummyJob( this ) )
                                        << Calamares::job_ptr( new DummyJob( this ) ) );
        QSignalSpy spy_progress( &q, &Calamares::JobQueue::progress );
        QSignalSpy spy_finished( &q, &Calamares::JobQueue::finished );
        QSignalSpy spy_failed( &q, &Calamares::JobQueue::failed );

        QEventLoop loop;
        connect( &q, &Calamares::JobQueue::finished, &loop, &QEventLoop::quit );
        // Run the loop longer because the jobs take longer (there are 3 of them)
        QTimer::singleShot( 3 * MAX_TEST_DURATION, &loop, &QEventLoop::quit );
        q.start();
        QVERIFY( q.isRunning() );
        loop.exec();
        QVERIFY( !q.isRunning() );
        QCOMPARE( spy_finished.count(), 1 );
        QCOMPARE( spy_failed.count(), 0 );
        // 0% by the queue at job start
        // 50% by the job itself
        // 90% by the job itself
        // 100% by the queue at job end
        // 4 more for the next job
        // 4 more for the next job
        // 100% by the queue at queue end
        QCOMPARE( spy_progress.count(), 13 );

        /* Consider how progress will be reported:
         *
         * - the first module has weight 8, so the 1 job it has has weight 8
         * - the second module has weight 12, so each of its two jobs has weight 6
         *
         * Total weight of the modules is 20. So the events are
         *
         * Job Progress  Overall Weight Consumed  Overall Progress
         *   1      0            0                       0.00
         *   1     50            4                       0.20
         *   1     75            6                       0.30
         *   1    100            8                       0.40
         *   2      0            8                       0.40
         *   2     50           11 (8 + 50% of 6)        0.55
         *   2     75           12.5                     0.625
         *   2    100           14                       0.70
         *   3      0           14                       0.70
         *   3     50           17                       0.85
         *   3     75           18.5                     0.925
         *   3    100           20                       1.00
         *   -    100           20                       1.00
         */
        cDebug() << "Progress signals:";
        qreal overallProgress = 0.0;
        for ( const auto& e : spy_progress )
        {
            QCOMPARE( e.count(), 2 );
            const auto v = e.first();
            QVERIFY( v.canConvert< qreal >() );
            qreal progress = v.toReal();
            cDebug() << Logger::SubEntry << progress;
            QVERIFY( progress >= overallProgress );  // Doesn't go backwards
            overallProgress = progress;
        }
    }
}


QTEST_GUILESS_MAIN( TestLibCalamares )

#include "utils/moc-warnings.h"

#include "Tests.moc"
