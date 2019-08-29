/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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

#include "Retranslator.h"

#include "Logger.h"

#include <QCoreApplication>
#include <QDir>
#include <QEvent>
#include <QTranslator>


namespace CalamaresUtils
{
static QTranslator* s_brandingTranslator = nullptr;
static QTranslator* s_translator = nullptr;
static QString s_translatorLocaleName;

void
installTranslator( const QLocale& locale, const QString& brandingTranslationsPrefix, QObject* parent )
{
    QString localeName = locale.name();
    localeName.replace( "-", "_" );

    if ( localeName == "C" )
    {
        localeName = "en";
    }

    // Special case of sr@latin
    //
    // See top-level CMakeLists.txt about special cases for translation loading.
    if ( locale.language() == QLocale::Language::Serbian && locale.script() == QLocale::Script::LatinScript )
    {
        localeName = QStringLiteral( "sr@latin" );
    }

    cDebug() << "Looking for translations for" << localeName;

    QTranslator* translator = nullptr;

    // Branding translations
    if ( !brandingTranslationsPrefix.isEmpty() )
    {
        QString brandingTranslationsDirPath( brandingTranslationsPrefix );
        brandingTranslationsDirPath.truncate( brandingTranslationsPrefix.lastIndexOf( QDir::separator() ) );
        QDir brandingTranslationsDir( brandingTranslationsDirPath );
        if ( brandingTranslationsDir.exists() )
        {
            QString filenameBase( brandingTranslationsPrefix );
            filenameBase.remove( 0, brandingTranslationsPrefix.lastIndexOf( QDir::separator() ) + 1 );
            translator = new QTranslator( parent );
            if ( translator->load( locale, filenameBase, "_", brandingTranslationsDir.absolutePath() ) )
            {
                cDebug() << Logger::SubEntry << "Branding using locale:" << localeName;
            }
            else
            {
                cDebug() << Logger::SubEntry << "Branding using default, system locale not found:" << localeName;
                translator->load( brandingTranslationsPrefix + "en" );
            }

            if ( s_brandingTranslator )
            {
                QCoreApplication::removeTranslator( s_brandingTranslator );
                delete s_brandingTranslator;
            }

            QCoreApplication::installTranslator( translator );
            s_brandingTranslator = translator;
        }
    }

    // Calamares translations
    translator = new QTranslator( parent );
    if ( translator->load( QString( ":/lang/calamares_" ) + localeName ) )
    {
        cDebug() << Logger::SubEntry << "Calamares using locale:" << localeName;
    }
    else
    {
        cDebug() << Logger::SubEntry << "Calamares using default, system locale not found:" << localeName;
        translator->load( QString( ":/lang/calamares_en" ) );
    }

    if ( s_translator )
    {
        QCoreApplication::removeTranslator( s_translator );
        delete s_translator;
    }

    QCoreApplication::installTranslator( translator );
    s_translator = translator;

    s_translatorLocaleName = localeName;
}


QString
translatorLocaleName()
{
    return s_translatorLocaleName;
}

Retranslator*
Retranslator::retranslatorFor( QObject* parent )
{
    Retranslator* r = nullptr;
    for ( QObject* child : parent->children() )
    {
        r = qobject_cast< Retranslator* >( child );
        if ( r )
        {
            return r;
        }
    }

    return new Retranslator( parent );
}

void
Retranslator::attachRetranslator( QObject* parent, std::function< void( void ) > retranslateFunc )
{
    retranslatorFor( parent )->m_retranslateFuncList.append( retranslateFunc );
    retranslateFunc();
}


Retranslator::Retranslator( QObject* parent )
    : QObject( parent )
{
    parent->installEventFilter( this );
}


bool
Retranslator::eventFilter( QObject* obj, QEvent* e )
{
    if ( obj == parent() )
    {
        if ( e->type() == QEvent::LanguageChange )
        {
            foreach ( std::function< void() > func, m_retranslateFuncList )
            {
                func();
            }
            emit languageChange();
        }
    }
    // pass the event on to the base
    return QObject::eventFilter( obj, e );
}


}  // namespace CalamaresUtils
