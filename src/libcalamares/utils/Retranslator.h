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

#include <QList>
#include <QObject>
#include <QString>

#include <functional>

class QEvent;
class QLocale;
class QTranslator;

namespace CalamaresUtils
{
/**
 * @brief installTranslator changes the application language.
 * @param locale the new locale.
 * @param brandingTranslationsPrefix the branding path prefix, from Calamares::Branding.
 */
DLLEXPORT void installTranslator( const QLocale& locale, const QString& brandingTranslationsPrefix );

/** @brief The name of the (locale of the) most recently installed translator
 *
 * May return something different from the locale.name() of the
 * QLocale passed in, because Calamares will munge some names and
 * may remap translations.
 */
DLLEXPORT QString translatorLocaleName();

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
DLLEXPORT bool loadTranslator( const QLocale& locale, const QString& prefix, QTranslator* translator );

/** @brief Set @p allow to true to load translations from current dir.
 *
 * If false, (or never called) the translations are loaded only from
 * system locations (the AppData dir) and from QRC (compiled in).
 * Enable local translations to test translations stored in the
 * current directory.
 */
DLLEXPORT void setAllowLocalTranslation( bool allow );

class Retranslator : public QObject
{
    Q_OBJECT
public:
    /// @brief Call @p retranslateFunc when the language changes
    static void attachRetranslator( QObject* parent, std::function< void( void ) > retranslateFunc );
    /// @brief What retranslator belongs to @p parent (may create one)
    static Retranslator* retranslatorFor( QObject* parent );

    /// @brief Call @p retranslateFunc when the language changes
    void addRetranslateFunc( std::function< void( void ) > retranslateFunc );

signals:
    void languageChange();

protected:
    bool eventFilter( QObject* obj, QEvent* e ) override;

private:
    explicit Retranslator( QObject* parent );

    QList< std::function< void( void ) > > m_retranslateFuncList;
};


}  // namespace CalamaresUtils

#define CALAMARES_RETRANSLATE( body ) CalamaresUtils::Retranslator::attachRetranslator( this, [=] { body } )
#define CALAMARES_RETRANSLATE_WIDGET( widget, body ) \
    CalamaresUtils::Retranslator::attachRetranslator( widget, [=] { body } )
#define CALAMARES_RETRANSLATE_SLOT( slotfunc ) \
    do \
    { \
        this->connect( CalamaresUtils::Retranslator::retranslatorFor( this ), \
                       &CalamaresUtils::Retranslator::languageChange, \
                       this, \
                       slotfunc ); \
    } while ( 0 )

#endif
