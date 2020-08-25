/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "Config.h"

#include "utils/Logger.h"

#include <QObject>
#include <QtTest/QtTest>

class TrackingTests : public QObject
{
    Q_OBJECT
public:
    TrackingTests();
    ~TrackingTests() override;

private Q_SLOTS:
    void initTestCase();
    void testEmptyConfig();
};

TrackingTests::TrackingTests()
    : QObject()
{
}

TrackingTests::~TrackingTests() {}

void
TrackingTests::initTestCase()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );
    cDebug() << "Tracking test started.";
}

void
TrackingTests::testEmptyConfig()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );

    Config* c = new Config;
    QVERIFY( c->generalPolicy().isEmpty() );
    QVERIFY( c->installTracking() );  // not-nullptr

    cDebug() << "Install" << Logger::Pointer( c->installTracking() );

    delete c;  // also deletes the owned tracking-configs
}


QTEST_GUILESS_MAIN( TrackingTests )

#include "utils/moc-warnings.h"

#include "Tests.moc"
