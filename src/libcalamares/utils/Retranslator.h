/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#ifndef UTILS_RETRANSLATOR_H
#define UTILS_RETRANSLATOR_H

#include "DllMacro.h"
#include "locale/Translation.h"

#include <QObject>
#include <QString>

#include <functional>

class QEvent;
class QLocale;
class QTranslator;

namespace CalamaresUtils
{
/** @brief changes the application language.
 * @param locale the new locale (names as defined by Calamares).
 * @param brandingTranslationsPrefix the branding path prefix, from Calamares::Branding.
 */
DLLEXPORT void installTranslator( const CalamaresUtils::Locale::Translation::Id& locale,
                                  const QString& brandingTranslationsPrefix );

/** @brief Initializes the translations with the current system settings
 */
DLLEXPORT void installTranslator();

/** @brief The name of the (locale of the) most recently installed translator
 *
 * May return something different from the locale.name() of the
 * QLocale passed in, because Calamares will munge some names and
 * may remap translations.
 */
DLLEXPORT CalamaresUtils::Locale::Translation::Id translatorLocaleName();

/** @brief Loads <prefix><locale> translations into the given @p translator
 *
 * This function is not intended for general use: it is for those special
 * cases where modules need their own translator / translations for data
 * that is locale to the module. Tries to load a .qm from "sensible"
 * locations, which are the same ones that installTranslator() would use.
 * Takes local-translations into account.
 *
 * Note that @p prefix should end with an underscore '_' -- this function
 * does not introduce one by itself.
 *
 * @returns @c true on success
 */
DLLEXPORT bool
loadTranslator( const CalamaresUtils::Locale::Translation::Id& locale, const QString& prefix, QTranslator* translator );

/** @brief Set @p allow to true to load translations from current dir.
 *
 * If false, (or never called) the translations are loaded only from
 * system locations (the AppData dir) and from QRC (compiled in).
 * Enable local translations to test translations stored in the
 * current directory.
 */
DLLEXPORT void setAllowLocalTranslation( bool allow );


/** @brief Handles change-of-language events
 *
 * There is one single Retranslator object. Use `instance()` to get it.
 * The top-level widget of the application should call
 *      `installEventFilter( Retranslator::instance() )`
 * to set up event-handling for translation events. The Retranslator
 * will emit signal `languageChanged()` if there is such an event.
 *
 * Normal consumers should not have to use the Retranslator directly,
 * but use the macros `CALAMARES_RETRANSLATE*` to set things up
 * in code -- the macros will connect to the Retranslator's signals.
 */
class Retranslator : public QObject
{
    Q_OBJECT
public:
    /// @brief Gets the global (single) Retranslator object
    static Retranslator* instance();

    /// @brief Helper function for attaching lambdas
    static void attach( QObject* o, std::function< void( void ) > f );

signals:
    void languageChanged();

protected:
    bool eventFilter( QObject* obj, QEvent* e ) override;

private:
    explicit Retranslator( QObject* parent );
};


}  // namespace CalamaresUtils

/** @brief Call code for this object when language changes
 *
 * @p body should be a code block (it does not need braces) that can be wrapped
 * up as a lambda. When the language changes, the lambda is called. Note that
 * this macro should be used in constructors or other code that is run only
 * once, since otherwise you will end up with multiple calls to @p body.
 *
 * NOTE: unlike plain QObject::connect(), the body is **also** called
 *       immediately after setting up the connection. This allows
 *       setup and translation code to be mixed together.
 */
#define CALAMARES_RETRANSLATE( body ) CalamaresUtils::Retranslator::attach( this, [ = ] { body } )
/** @brief Call code for the given object (widget) when language changes
 *
 * This is identical to CALAMARES_RETRANSLATE, except the @p body is called
 * for the given object, not this object.
 *
 * NOTE: unlike plain QObject::connect(), the body is **also** called
 *       immediately after setting up the connection. This allows
 *       setup and translation code to be mixed together.
 */
#define CALAMARES_RETRANSLATE_FOR( object, body ) CalamaresUtils::Retranslator::attach( object, [ = ] { body } )
/** @brief Call a slot in this object when language changes
 *
 * Given a slot (in method-function-pointer notation), call that slot when the
 * language changes. This is shorthand for connecting the Retranslator's
 * signal to the given slot.
 *
 * NOTE: unlike plain QObject::connect(), the slot is **also** called
 *       immediately after setting up the connection. This allows
 *       setup and translation code to be mixed together.
 */
#define CALAMARES_RETRANSLATE_SLOT( slotfunc ) \
    do \
    { \
        connect( CalamaresUtils::Retranslator::instance(), \
                 &CalamaresUtils::Retranslator::languageChanged, \
                 this, \
                 slotfunc ); \
        ( this->*slotfunc )(); \
    } while ( false )

#endif
