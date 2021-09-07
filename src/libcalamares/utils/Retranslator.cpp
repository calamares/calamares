/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#include "Retranslator.h"

#include "Settings.h"
#include "utils/Dirs.h"
#include "utils/Logger.h"

#include <QCoreApplication>
#include <QDir>
#include <QEvent>
#include <QTranslator>

namespace
{

static bool s_allowLocalTranslations = false;

/** @brief Helper class for loading translations
 *
 * This is used by the loadSingletonTranslator() function to hand off
 * work to translation-type specific code.
 */
struct TranslationLoader
{
    TranslationLoader( const QString& locale )
        : m_localeName( locale )
    {
    }

    virtual ~TranslationLoader();
    /// @brief Loads @p translator with the specific translations of this type
    virtual bool tryLoad( QTranslator* translator ) = 0;

    QString m_localeName;
};

/// @brief Loads translations for branding
struct BrandingLoader : public TranslationLoader
{
    BrandingLoader( const QString& locale, const QString& prefix )
        : TranslationLoader( locale )
        , m_prefix( prefix )
    {
    }

    bool tryLoad( QTranslator* translator ) override;

    QString m_prefix;
};

/// @brief Loads regular Calamares translations (program text)
struct CalamaresLoader : public TranslationLoader
{
    using TranslationLoader::TranslationLoader;
    bool tryLoad( QTranslator* translator ) override;
};

/// @brief Loads timezone name translations
struct TZLoader : public TranslationLoader
{
    using TranslationLoader::TranslationLoader;
    bool tryLoad( QTranslator* translator ) override;
};

TranslationLoader::~TranslationLoader() {}

bool
BrandingLoader::tryLoad( QTranslator* translator )
{
    if ( m_prefix.isEmpty() )
    {
        return false;
    }
    QString brandingTranslationsDirPath( m_prefix );
    brandingTranslationsDirPath.truncate( m_prefix.lastIndexOf( QDir::separator() ) );
    QDir brandingTranslationsDir( brandingTranslationsDirPath );
    if ( brandingTranslationsDir.exists() )
    {
        QString filenameBase( m_prefix );
        filenameBase.remove( 0, m_prefix.lastIndexOf( QDir::separator() ) + 1 );
        if ( translator->load( m_localeName, filenameBase, "_", brandingTranslationsDir.absolutePath() ) )
        {
            cDebug() << Logger::SubEntry << "Branding using locale:" << m_localeName;
            return true;
        }
        else
        {
            cDebug() << Logger::SubEntry << "Branding no translation for" << m_localeName << "using default (en)";
            // TODO: this loads something completely different
            return translator->load( m_prefix + "en" );
        }
    }
    return false;
}

static bool
tryLoad( QTranslator* translator, const QString& prefix, const QString& localeName )
{
    // In debug-mode, try loading from the current directory
    if ( s_allowLocalTranslations && translator->load( prefix + localeName ) )
    {
        cDebug() << Logger::SubEntry << "Loaded local translation" << prefix << localeName;
        return true;
    }

    // Or load from appDataDir -- often /usr/share/calamares -- subdirectory land/
    QDir localeData( CalamaresUtils::appDataDir() );
    if ( localeData.exists()
         && translator->load( localeData.absolutePath() + QStringLiteral( "/lang/" ) + prefix + localeName ) )
    {
        cDebug() << Logger::SubEntry << "Loaded appdata translation" << prefix << localeName;
        return true;
    }

    // Or from QRC (most common)
    if ( translator->load( QStringLiteral( ":/lang/" ) + prefix + localeName ) )
    {
        cDebug() << Logger::SubEntry << "Loaded QRC translation" << prefix << localeName;
        return true;
    }
    else
    {
        cDebug() << Logger::SubEntry << "No translation for" << prefix << localeName << "using default (en)";
        return translator->load( QStringLiteral( ":/lang/" ) + prefix + QStringLiteral( "en" ) );
    }
}

bool
CalamaresLoader::tryLoad( QTranslator* translator )
{
    return ::tryLoad( translator, QStringLiteral( "calamares_" ), m_localeName );
}

bool
TZLoader::tryLoad( QTranslator* translator )
{
    return ::tryLoad( translator, QStringLiteral( "tz_" ), m_localeName );
}

static void
loadSingletonTranslator( TranslationLoader&& loader, QTranslator*& translator_p )
{
    if ( !translator_p )
    {
        QTranslator* translator = new QTranslator();
        loader.tryLoad( translator );
        QCoreApplication::installTranslator( translator );
        translator_p = translator;
    }
    else
    {
        loader.tryLoad( translator_p );
    }
}

}  // namespace

namespace CalamaresUtils
{
static QTranslator* s_brandingTranslator = nullptr;
static QTranslator* s_translator = nullptr;
static QTranslator* s_tztranslator = nullptr;
static QString s_translatorLocaleName;

void
installTranslator( const CalamaresUtils::Locale::Translation::Id& locale, const QString& brandingTranslationsPrefix )
{
    s_translatorLocaleName = locale.name;

    loadSingletonTranslator( BrandingLoader( locale.name, brandingTranslationsPrefix ), s_brandingTranslator );
    loadSingletonTranslator( TZLoader( locale.name ), s_tztranslator );
    loadSingletonTranslator( CalamaresLoader( locale.name ), s_translator );
}

void
installTranslator()
{
    // Just wrap it up like an Id
    installTranslator( { QLocale::system().name() }, QString() );
}

CalamaresUtils::Locale::Translation::Id
translatorLocaleName()
{
    return { s_translatorLocaleName };
}

bool
loadTranslator( const CalamaresUtils::Locale::Translation::Id& locale, const QString& prefix, QTranslator* translator )
{
    return ::tryLoad( translator, prefix, locale.name );
}

Retranslator::Retranslator( QObject* parent )
    : QObject( parent )
{
}

bool
Retranslator::eventFilter( QObject* obj, QEvent* e )
{
    if ( e->type() == QEvent::LanguageChange )
    {
        emit languageChanged();
    }
    // pass the event on to the base
    return QObject::eventFilter( obj, e );
}

Retranslator*
Retranslator::instance()
{
    static Retranslator s_instance( nullptr );
    return &s_instance;
}

void
Retranslator::attach( QObject* o, std::function< void() > f )
{
    connect( instance(), &Retranslator::languageChanged, o, f );
    f();
}

void
setAllowLocalTranslation( bool allow )
{
    s_allowLocalTranslations = allow;
}


}  // namespace CalamaresUtils
