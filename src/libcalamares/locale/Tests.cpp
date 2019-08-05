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

#include "locale/LabelModel.h"
#include "locale/TranslatableConfiguration.h"

#include "CalamaresVersion.h"
#include "utils/Logger.h"

#include <QtTest/QtTest>

QTEST_GUILESS_MAIN( LocaleTests )

LocaleTests::LocaleTests() {}

LocaleTests::~LocaleTests() {}

void
LocaleTests::initTestCase()
{
}

void
LocaleTests::testLanguageModelCount()
{
    const auto* m = CalamaresUtils::Locale::availableTranslations();

    QVERIFY( m );
    QVERIFY( m->rowCount( QModelIndex() ) > 1 );

    int dutch = m->find( QLocale( "nl_NL" ) );
    QVERIFY( dutch > 0 );
    QCOMPARE( m->find( "NL" ), dutch );
    // must be capitals
    QCOMPARE( m->find( "nl" ), -1 );
    QCOMPARE( m->find( QLocale( "nl" ) ), dutch );

    // Belgium speaks Dutch as well
    QCOMPARE( m->find( "BE" ), dutch );
}

void
LocaleTests::testEsperanto()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );

    const auto* m = CalamaresUtils::Locale::availableTranslations();

    QVERIFY( m );

    // Cursory test that all the locales found have a sensible language,
    // and that some specific languages have sensible corresponding data.
    //
    // This fails on Esperanto (or, if Esperanto is added to Qt, then
    // this will pass and the test after the loop will fail.
    for ( int i = 0; i < m->rowCount( QModelIndex() ); ++i )
    {
        const auto& label = m->locale( i );
        const auto locale = label.locale();
        cDebug() << label.label() << locale;

        QVERIFY( locale.language() == QLocale::Greek ? locale.script() == QLocale::GreekScript : true );
        QVERIFY( locale.language() == QLocale::Korean ? locale.script() == QLocale::KoreanScript : true );
        QVERIFY( locale.language() == QLocale::Lithuanian ? locale.country() == QLocale::Lithuania : true );
        QVERIFY( locale.language() != QLocale::C );
    }
#if QT_VERSION < QT_VERSION_CHECK( 5, 12, 2 )
    QCOMPARE( QLocale( "eo" ).language(), QLocale::C );
#else
    QCOMPARE( QLocale( "eo" ).language(), QLocale::Esperanto );
#endif
}

static const QStringList&
someLanguages()
{
    static QStringList languages { "nl", "de", "da", "nb", "sr@latin", "ar", "ru" };
    return languages;
}


void
LocaleTests::testTranslatableLanguages()
{
    QStringList availableLanguages = QString( CALAMARES_TRANSLATION_LANGUAGES ).split( ';' );
    cDebug() << "Translation languages:" << availableLanguages;
    for ( const auto& language : someLanguages() )
    {
        // Could be QVERIFY, but then we don't see what language code fails
        QCOMPARE( availableLanguages.contains( language ) ? language : QString(), language );
    }
}

void
LocaleTests::testTranslatableConfig1()
{
    QCOMPARE( QLocale().name(), "C" );  // Otherwise plain get() is dubious
    CalamaresUtils::Locale::TranslatedString ts1( "Hello" );
    QCOMPARE( ts1.count(), 1 );

    QCOMPARE( ts1.get(), "Hello" );
    QCOMPARE( ts1.get( QLocale( "nl" ) ), "Hello" );

    QVariantMap map;
    map.insert( "description", "description (no language)" );
    CalamaresUtils::Locale::TranslatedString ts2( map, "description" );
    QCOMPARE( ts2.count(), 1 );

    QCOMPARE( ts2.get(), "description (no language)" );
    QCOMPARE( ts2.get( QLocale( "nl" ) ), "description (no language)" );
}

void
LocaleTests::testTranslatableConfig2()
{
    QCOMPARE( QLocale().name(), "C" );  // Otherwise plain get() is dubious
    QVariantMap map;

    for ( const auto& language : someLanguages() )
    {
        map.insert( QString( "description[%1]" ).arg( language ),
                    QString( "description (language %1)" ).arg( language ) );
        if ( language != "nl" )
        {
            map.insert( QString( "name[%1]" ).arg( language ), QString( "name (language %1)" ).arg( language ) );
        }
    }

    CalamaresUtils::Locale::TranslatedString ts1( map, "description" );
    // The +1 is because "" is always also inserted
    QCOMPARE( ts1.count(), someLanguages().count() + 1 );

    QCOMPARE( ts1.get(), "description" );  // it wasn't set
    QCOMPARE( ts1.get( QLocale( "nl" ) ), "description (language nl)" );
    for ( const auto& language : someLanguages() )
    {
        // Skip Serbian (latin) because QLocale() constructed with it
        // doesn't retain the @latin part.
        if ( language == "sr@latin" )
        {
            continue;
        }
        // Could be QVERIFY, but then we don't see what language code fails
        QCOMPARE( ts1.get( language ) == QString( "description (language %1)" ).arg( language ) ? language : QString(),
                  language );
    }
    QCOMPARE( ts1.get( QLocale( QLocale::Language::Serbian, QLocale::Script::LatinScript, QLocale::Country::Serbia ) ),
              "description (language sr@latin)" );

    CalamaresUtils::Locale::TranslatedString ts2( map, "name" );
    // We skipped dutch this time
    QCOMPARE( ts2.count(), someLanguages().count() );
}
