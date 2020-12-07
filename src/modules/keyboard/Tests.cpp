/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */
#include "utils/Logger.h"

#include <QtTest/QtTest>

// Internals of SetKeyboardLayoutJob.cpp
extern QString findLegacyKeymap( const QString& layout, const QString& model, const QString& variant );

class KeyboardLayoutTests : public QObject
{
    Q_OBJECT
public:
    KeyboardLayoutTests() {}
    ~KeyboardLayoutTests() override {}

private Q_SLOTS:
    void initTestCase();

    void testSimpleLayoutLookup_data();
    void testSimpleLayoutLookup();
};

void
KeyboardLayoutTests::initTestCase()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );
}

void
KeyboardLayoutTests::testSimpleLayoutLookup_data()
{
    QTest::addColumn< QString >( "layout" );
    QTest::addColumn< QString >( "model" );
    QTest::addColumn< QString >( "variant" );
    QTest::addColumn< QString >( "vconsole" );

    QTest::newRow( "us" ) << QString( "us" ) << QString() << QString() << QString( "us" );
    QTest::newRow( "turkish default" ) << QString( "tr" ) << QString() << QString() << QString( "trq" );
    QTest::newRow( "turkish alt-q" ) << QString( "tr" ) << QString() << QString( "alt" ) << QString( "trq" );
    QTest::newRow( "turkish f" ) << QString( "tr" ) << QString() << QString( "f" ) << QString( "trf" );
}


void
KeyboardLayoutTests::testSimpleLayoutLookup()
{
    QFETCH( QString, layout );
    QFETCH( QString, model );
    QFETCH( QString, variant );
    QFETCH( QString, vconsole );

    QCOMPARE( findLegacyKeymap( layout, model, variant ), vconsole );
}


QTEST_GUILESS_MAIN( KeyboardLayoutTests )

#include "utils/moc-warnings.h"

#include "Tests.moc"
