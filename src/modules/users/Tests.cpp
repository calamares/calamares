/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "Config.h"

#include "JobQueue.h"
#include "utils/Logger.h"
#include "utils/Yaml.h"

#include <QtTest/QtTest>

// Implementation details
extern void setConfigurationDefaultGroups( const QVariantMap& map, QList< GroupDescription >& defaultGroups );
extern HostNameAction getHostNameAction( const QVariantMap& configurationMap );
extern bool addPasswordCheck( const QString& key, const QVariant& value, PasswordCheckList& passwordChecks );
extern QString
makeHostnameSuggestion( const QString& templateString, const QStringList& fullNameParts, const QString& loginName );

/** @brief Test Config object methods and internals
 *
 */
class UserTests : public QObject
{
    Q_OBJECT
public:
    UserTests();
    ~UserTests() override {}

private Q_SLOTS:
    void initTestCase();

    // Derpy test for getting and setting regular values
    void testGetSet();

    void testDefaultGroups();
    void testDefaultGroupsYAML_data();
    void testDefaultGroupsYAML();

    void testHostActions_data();
    void testHostActions();
    void testHostActions2();
    void testHostSuggestions_data();
    void testHostSuggestions();

    void testPasswordChecks();
    void testUserPassword();

    void testAutoLogin_data();
    void testAutoLogin();

    void testUserYAML_data();
    void testUserYAML();
};

UserTests::UserTests() {}

void
UserTests::initTestCase()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );
    cDebug() << "Users test started.";

    if ( !Calamares::JobQueue::instance() )
    {
        (void)new Calamares::JobQueue();
    }
}

void
UserTests::testGetSet()
{
    Config c;

    {
        const QString sh( "/bin/sh" );
        QCOMPARE( c.userShell(), QString() );
        c.setUserShell( sh );
        QCOMPARE( c.userShell(), sh );
        c.setUserShell( sh + sh );
        QCOMPARE( c.userShell(), sh + sh );

        const QString badsh( "bash" );  // Not absolute, that's bad
        c.setUserShell( badsh );  // .. so unchanged
        QCOMPARE( c.userShell(), sh + sh );  // what was set previously

        // Explicit set to empty is ok
        c.setUserShell( QString() );
        QCOMPARE( c.userShell(), QString() );
    }
    {
        const QString al( "autolg" );
        QCOMPARE( c.autoLoginGroup(), QString() );
        c.setAutoLoginGroup( al );
        QCOMPARE( c.autoLoginGroup(), al );
        QVERIFY( !c.doAutoLogin() );
        c.setAutoLogin( true );
        QVERIFY( c.doAutoLogin() );
        QCOMPARE( c.autoLoginGroup(), al );
    }
    {
        const QString su( "sudogrp" );
        QCOMPARE( c.sudoersGroup(), QString() );
        c.setSudoersGroup( su );
        QCOMPARE( c.sudoersGroup(), su );
    }
    {
        const QString ful( "Jan-Jaap Karel Kees" );
        const QString lg( "jjkk" );
        QCOMPARE( c.fullName(), QString() );
        QCOMPARE( c.loginName(), QString() );
        QVERIFY( c.loginNameStatus().isEmpty() );  // empty login name is ok
        c.setLoginName( lg );
        c.setFullName( ful );
        QVERIFY( c.loginNameStatus().isEmpty() );  // now it's still ok
        QCOMPARE( c.loginName(), lg );
        QCOMPARE( c.fullName(), ful );
    }
    // Test forbidden login names
    {
        QVERIFY( c.forbiddenLoginNames().contains( QStringLiteral( "root" ) ) );
        QVERIFY( c.loginNameStatus().isEmpty() );  // it's ok now
        c.setLoginName( "root" );
        QVERIFY( !c.loginNameStatus().isEmpty() );  // can't be root
    }
}


void
UserTests::testDefaultGroups()
{
    {
        QList< GroupDescription > groups;
        QVariantMap hweelGroup;
        QVERIFY( groups.isEmpty() );
        hweelGroup.insert( "defaultGroups", QStringList { "hweel" } );
        setConfigurationDefaultGroups( hweelGroup, groups );
        QCOMPARE( groups.count(), 1 );
        QVERIFY( groups.contains( GroupDescription( "hweel" ) ) );
    }

    {
        QStringList desired { "wheel", "root", "operator" };
        QList< GroupDescription > groups;
        QVariantMap threeGroup;
        QVERIFY( groups.isEmpty() );
        threeGroup.insert( "defaultGroups", desired );
        setConfigurationDefaultGroups( threeGroup, groups );
        QCOMPARE( groups.count(), 3 );
        QVERIFY( !groups.contains( GroupDescription( "hweel" ) ) );
        for ( const auto& s : desired )
        {
            QVERIFY( groups.contains( GroupDescription( s ) ) );
        }
    }

    {
        QList< GroupDescription > groups;
        QVariantMap explicitEmpty;
        QVERIFY( groups.isEmpty() );
        explicitEmpty.insert( "defaultGroups", QStringList() );
        setConfigurationDefaultGroups( explicitEmpty, groups );
        QCOMPARE( groups.count(), 0 );
    }

    {
        QList< GroupDescription > groups;
        QVariantMap missing;
        QVERIFY( groups.isEmpty() );
        setConfigurationDefaultGroups( missing, groups );
        QCOMPARE( groups.count(), 6 );  // because of fallback!
        QVERIFY( groups.contains( GroupDescription( "lp", false, GroupDescription::SystemGroup {} ) ) );
    }

    {
        QList< GroupDescription > groups;
        QVariantMap typeMismatch;
        QVERIFY( groups.isEmpty() );
        typeMismatch.insert( "defaultGroups", 1 );
        setConfigurationDefaultGroups( typeMismatch, groups );
        QCOMPARE( groups.count(), 6 );  // because of fallback!
        QVERIFY( groups.contains( GroupDescription( "lp", false, GroupDescription::SystemGroup {} ) ) );
    }
}

void
UserTests::testDefaultGroupsYAML_data()
{
    QTest::addColumn< QString >( "filename" );
    QTest::addColumn< int >( "count" );
    QTest::addColumn< QString >( "group" );

    QTest::newRow( "users.conf" ) << "users.conf" << 7 << "video";
    QTest::newRow( "dashed list" ) << "tests/4-audio.conf" << 4 << "audio";
    QTest::newRow( "blocked list" ) << "tests/3-wing.conf" << 3 << "wing";
    QTest::newRow( "issue 1523" ) << "tests/5-issue-1523.conf" << 4 << "foobar";
}

void
UserTests::testDefaultGroupsYAML()
{
    if ( !Calamares::JobQueue::instance() )
    {
        (void)new Calamares::JobQueue();
    }

    QFETCH( QString, filename );
    QFETCH( int, count );
    QFETCH( QString, group );

    // BUILD_AS_TEST is the source-directory path
    QFile fi( QString( "%1/%2" ).arg( BUILD_AS_TEST, filename ) );
    QVERIFY( fi.exists() );

    bool ok = false;
    const auto map = CalamaresUtils::loadYaml( fi, &ok );
    QVERIFY( ok );
    QVERIFY( map.count() > 0 );

    Config c;
    c.setConfigurationMap( map );

    QCOMPARE( c.defaultGroups().count(), count );
    QVERIFY( c.defaultGroups().contains( group ) );
}


void
UserTests::testHostActions_data()
{
    QTest::addColumn< bool >( "set" );
    QTest::addColumn< QString >( "string" );
    QTest::addColumn< int >( "result" );

    QTest::newRow( "unset  " ) << false << QString() << int( HostNameAction::EtcHostname );
    QTest::newRow( "empty  " ) << true << QString() << int( HostNameAction::EtcHostname );
    QTest::newRow( "bad    " ) << true << QString( "derp" ) << int( HostNameAction::EtcHostname );
    QTest::newRow( "none   " ) << true << QString( "none" ) << int( HostNameAction::None );
    QTest::newRow( "systemd" ) << true << QString( "Hostnamed" ) << int( HostNameAction::SystemdHostname );
    QTest::newRow( "etc(1) " ) << true << QString( "etcfile" ) << int( HostNameAction::EtcHostname );
    QTest::newRow( "etc(2) " ) << true << QString( "etc" ) << int( HostNameAction::EtcHostname );
    QTest::newRow( "etc-bad" )
        << true << QString( "etchost" )
        << int( HostNameAction::EtcHostname );  // This isn't a valid name, but defaults to EtcHostname
    QTest::newRow( "ci-sysd" ) << true << QString( "hOsTnaMed" )
                               << int( HostNameAction::SystemdHostname );  // Case-insensitive
    QTest::newRow( "trbs   " ) << true << QString( "transient" ) << int( HostNameAction::Transient );
    QTest::newRow( "ci-trns" ) << true << QString( "trANSient" ) << int( HostNameAction::Transient );
}

void
UserTests::testHostActions()
{
    QFETCH( bool, set );
    QFETCH( QString, string );
    QFETCH( int, result );

    QVariantMap m;
    if ( set )
    {
        m.insert( "location", string );
    }
    // action is independent of writeHostsFile
    QCOMPARE( getHostNameAction( m ), HostNameAction( result ) );
    m.insert( "writeHostsFile", false );
    QCOMPARE( getHostNameAction( m ), HostNameAction( result ) );
    m.insert( "writeHostsFile", true );
    QCOMPARE( getHostNameAction( m ), HostNameAction( result ) );
}

void
UserTests::testHostActions2()
{
    Config c;
    QVariantMap legacy;

    // Test defaults
    c.setConfigurationMap( legacy );
    QCOMPARE( c.hostnameAction(), HostNameAction::EtcHostname );
    QCOMPARE( c.writeEtcHosts(), true );

    QVariantMap hostSettings;
    hostSettings.insert( "writeHostsFile", false );
    hostSettings.insert( "location", "Hostnamed" );
    legacy.insert( "hostname", hostSettings );
    c.setConfigurationMap( legacy );
    QCOMPARE( c.hostnameAction(), HostNameAction::SystemdHostname );
    QCOMPARE( c.writeEtcHosts(), false );
}


void
UserTests::testHostSuggestions_data()
{
    QTest::addColumn< QString >( "templateString" );
    QTest::addColumn< QString >( "result" );

    QTest::newRow( "unset  " ) << QString() << QString();
    QTest::newRow( "const  " ) << QStringLiteral( "derp" ) << QStringLiteral( "derp" );
    QTest::newRow( "escaped" ) << QStringLiteral( "$$" ) << QString();  // Because invalid
    QTest::newRow( "default" ) << QStringLiteral( "${first}-pc" )
                               << QStringLiteral( "chuck-pc" );  // Avoid ${product} because it's DMI-based
    QTest::newRow( "full   " ) << QStringLiteral( "${name}" ) << QStringLiteral( "chuckyeager" );
    QTest::newRow( "login+ " ) << QStringLiteral( "${login}-${first}" ) << QStringLiteral( "bill-chuck" );
    // This is a bit dodgy: assumes CPU architecture of the testing host
    QTest::newRow( " cpu   " ) << QStringLiteral( "${cpu}X" )
                               << QStringLiteral( "x8664X" );  // Assume we don't test on non-amd64
    // These have X X in the template to indicate that they are bogus. Mostly we want
    // to see what the template engine does for these.
    QTest::newRow( "@prod  " ) << QStringLiteral( "X${product}X" ) << QString();
    QTest::newRow( "@prod2 " ) << QStringLiteral( "X${product2}X" ) << QString();
    QTest::newRow( "@host  " ) << QStringLiteral( "X${host}X" ) << QString();
}

void
UserTests::testHostSuggestions()
{
    const QStringList fullName { "Chuck", "Yeager" };
    const QString login { "bill" };

    QFETCH( QString, templateString );
    QFETCH( QString, result );

    if ( templateString.startsWith( 'X' ) && templateString.endsWith( 'X' ) )
    {
        QEXPECT_FAIL( "", "Test is too host-specific", Continue );
        cWarning() << Logger::SubEntry << "Next test" << templateString << "->"
                   << makeHostnameSuggestion( templateString, fullName, login );
    }
    QCOMPARE( makeHostnameSuggestion( templateString, fullName, login ), result );
}


void
UserTests::testPasswordChecks()
{
    {
        PasswordCheckList l;
        QCOMPARE( l.length(), 0 );
        QVERIFY( !addPasswordCheck( "nonempty", QVariant( false ), l ) );  // a silly setting
        QCOMPARE( l.length(), 0 );
        QVERIFY( addPasswordCheck( "nonempty", QVariant( true ), l ) );
        QCOMPARE( l.length(), 1 );
    }
}

void
UserTests::testUserPassword()
{
    if ( !Calamares::JobQueue::instance() )
    {
        (void)new Calamares::JobQueue( nullptr );
    }

    {
        Config c;

        QVERIFY( c.userPassword().isEmpty() );
        QVERIFY( c.userPasswordSecondary().isEmpty() );
        // There are no validity checks, so no check for nonempty
        QCOMPARE( c.userPasswordValidity(), Config::PasswordValidity::Valid );

        c.setUserPassword( "bogus" );
        QCOMPARE( c.userPasswordValidity(), Config::PasswordValidity::Invalid );
        QCOMPARE( c.userPassword(), "bogus" );
        c.setUserPasswordSecondary( "bogus" );
        QCOMPARE( c.userPasswordValidity(), Config::PasswordValidity::Valid );
    }

    {
        Config c;

        QVariantMap m;
        m.insert( "allowWeakPasswords", true );
        m.insert( "allowWeakPasswordsDefault", true );
        m.insert( "defaultGroups", QStringList { "wheel" } );

        QVariantMap pwreq;
        pwreq.insert( "nonempty", true );
        pwreq.insert( "minLength", 6 );
        m.insert( "passwordRequirements", pwreq );

        c.setConfigurationMap( m );

        QVERIFY( c.userPassword().isEmpty() );
        QVERIFY( c.userPasswordSecondary().isEmpty() );
        // There is now a nonempty check, but weak passwords are ok
        QCOMPARE( c.userPasswordValidity(), int( Config::PasswordValidity::Weak ) );

        c.setUserPassword( "bogus" );
        QCOMPARE( c.userPasswordValidity(), int( Config::PasswordValidity::Invalid ) );
        c.setUserPasswordSecondary( "bogus" );
        QCOMPARE( c.userPasswordValidity(), int( Config::PasswordValidity::Weak ) );

        QVERIFY( !c.requireStrongPasswords() );
        c.setRequireStrongPasswords( true );
        QVERIFY( c.requireStrongPasswords() );
        // Now changed requirements make the password invalid
        QCOMPARE( c.userPassword(), "bogus" );
        QCOMPARE( c.userPasswordValidity(), int( Config::PasswordValidity::Invalid ) );
    }

    {
        Config c;
        QVERIFY( c.userPassword().isEmpty() );
        QCOMPARE( c.userPasswordValidity(), Config::PasswordValidity::Valid );

        QSignalSpy spy_pwChanged( &c, &Config::userPasswordChanged );
        QSignalSpy spy_pwSecondaryChanged( &c, &Config::userPasswordSecondaryChanged );
        QSignalSpy spy_pwStatusChanged( &c, &Config::userPasswordStatusChanged );

        c.setUserPassword( "bogus" );
        c.setUserPassword( "bogus" );
        QCOMPARE( spy_pwChanged.count(), 1 );
        QCOMPARE( spy_pwStatusChanged.count(), 1 );
        QCOMPARE( c.userPasswordValidity(), Config::PasswordValidity::Invalid );
        c.setUserPassword( "sugob" );
        c.setUserPasswordSecondary( "sugob" );
        QCOMPARE( spy_pwChanged.count(), 2 );
        QCOMPARE( spy_pwSecondaryChanged.count(), 1 );
        QCOMPARE( spy_pwStatusChanged.count(), 3 );
        QCOMPARE( c.userPasswordValidity(), Config::PasswordValidity::Valid );
    }
}

void
UserTests::testAutoLogin_data()
{
    QTest::addColumn< QString >( "filename" );
    QTest::addColumn< bool >( "autoLoginIsSet" );
    QTest::addColumn< QString >( "autoLoginGroupName" );

    QTest::newRow( "old, old" ) << "tests/6a-issue-1672.conf" << true << "derp";
    QTest::newRow( "old, new" ) << "tests/6b-issue-1672.conf" << true << "derp";
    QTest::newRow( "new, old" ) << "tests/6c-issue-1672.conf" << true << "derp";
    QTest::newRow( "new, new" ) << "tests/6d-issue-1672.conf" << true << "derp";
    QTest::newRow( "default" ) << "tests/6e-issue-1672.conf" << false << QString();
}

void
UserTests::testAutoLogin()
{
    QFETCH( QString, filename );
    QFETCH( bool, autoLoginIsSet );
    QFETCH( QString, autoLoginGroupName );

    // BUILD_AS_TEST is the source-directory path
    QFile fi( QString( "%1/%2" ).arg( BUILD_AS_TEST, filename ) );
    QVERIFY( fi.exists() );

    bool ok = false;
    const auto map = CalamaresUtils::loadYaml( fi, &ok );
    QVERIFY( ok );
    QVERIFY( map.count() > 0 );

    Config c;
    c.setConfigurationMap( map );

    QCOMPARE( c.doAutoLogin(), autoLoginIsSet );
    QCOMPARE( c.autoLoginGroup(), autoLoginGroupName );
}

void
UserTests::testUserYAML_data()
{
    QTest::addColumn< QString >( "filename" );
    QTest::addColumn< QString >( "shell" );

    const QString bash = QStringLiteral( "/bin/bash" );

    // All the old settings are ignored
    QTest::newRow( "old, unset   " ) << "tests/7ao-shell.conf" << bash;
    QTest::newRow( "old, empty   " ) << "tests/7bo-shell.conf" << bash;
    QTest::newRow( "old, relative" ) << "tests/7co-shell.conf" << bash;
    QTest::newRow( "old, invalid " ) << "tests/7do-shell.conf" << bash;
    QTest::newRow( "old, absolute" ) << "tests/7eo-shell.conf" << bash;

    QTest::newRow( "new, unset   " ) << "tests/7an-shell.conf"
                                     << "/bin/bash";
    QTest::newRow( "new, empty   " ) << "tests/7bn-shell.conf"
                                     << "";
    QTest::newRow( "new, relative" ) << "tests/7cn-shell.conf"
                                     << "/bin/ls";  // Setting is ignored
    QTest::newRow( "new, invalid " ) << "tests/7dn-shell.conf"
                                     << "";
    QTest::newRow( "new, absolute" ) << "tests/7en-shell.conf"
                                     << "/usr/bin/dash";
}

void
UserTests::testUserYAML()
{
    Config c;
    c.setUserShell( QStringLiteral( "/bin/ls" ) );

    QFETCH( QString, filename );
    QFETCH( QString, shell );

    // BUILD_AS_TEST is the source-directory path
    QFile fi( QString( "%1/%2" ).arg( BUILD_AS_TEST, filename ) );
    QVERIFY( fi.exists() );

    bool ok = false;
    const auto map = CalamaresUtils::loadYaml( fi, &ok );
    QVERIFY( ok );
    QVERIFY( map.count() > 0 );

    QCOMPARE( c.userShell(), QStringLiteral( "/bin/ls" ) );
    c.setConfigurationMap( map );
    QCOMPARE( c.userShell(), shell );
}


QTEST_GUILESS_MAIN( UserTests )

#include "utils/moc-warnings.h"

#include "Tests.moc"
