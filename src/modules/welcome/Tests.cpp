/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "Config.h"

#include "utils/Logger.h"
#include "utils/Yaml.h"

#include <QtTest/QtTest>

class WelcomeTests : public QObject
{
    Q_OBJECT
public:
    WelcomeTests();
    ~WelcomeTests() override {}

private Q_SLOTS:
    void initTestCase();

    void testOneUrl();
};

WelcomeTests::WelcomeTests() {}

void
WelcomeTests::initTestCase()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );
    cDebug() << "Welcome test started.";
}

void
WelcomeTests::testOneUrl()
{
    Config c;

    // BUILD_AS_TEST is the source-directory path
    QString filename = QStringLiteral( "1a-checkinternet.conf" );
    QFile fi( QString( "%1/%2" ).arg( BUILD_AS_TEST, filename ) );
    QVERIFY( fi.exists() );

    bool ok = false;
    const auto map = CalamaresUtils::loadYaml( fi, &ok );
    QVERIFY( ok );
    QVERIFY( map.count() > 0 );
    QVERIFY( map.contains( "requirements" ) );
}


QTEST_GUILESS_MAIN( WelcomeTests )

#include "utils/moc-warnings.h"

#include "Tests.moc"
