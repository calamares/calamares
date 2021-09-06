/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019-2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2020 Camilo Higuita <milo.h@aol.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef KEYBOARD_CONFIG_H
#define KEYBOARD_CONFIG_H

#include "AdditionalLayoutInfo.h"
#include "Job.h"
#include "KeyboardLayoutModel.h"

#include <QAbstractListModel>
#include <QMap>
#include <QObject>
#include <QTimer>
#include <QUrl>

class Config : public QObject
{
    Q_OBJECT
    Q_PROPERTY( KeyboardModelsModel* keyboardModelsModel READ keyboardModels CONSTANT FINAL )
    Q_PROPERTY( KeyboardLayoutModel* keyboardLayoutsModel READ keyboardLayouts CONSTANT FINAL )
    Q_PROPERTY( KeyboardVariantsModel* keyboardVariantsModel READ keyboardVariants CONSTANT FINAL )
    Q_PROPERTY( QString prettyStatus READ prettyStatus NOTIFY prettyStatusChanged FINAL )

public:
    Config( QObject* parent = nullptr );

    /// @brief Based on current xkb settings, pick a layout
    void detectCurrentKeyboardLayout();
    /// @brief Based on current locale, pick a layout
    void guessLocaleKeyboardLayout();

    Calamares::JobList createJobs();
    QString prettyStatus() const;

    /// @brief When leaving the page, write to GS
    void finalize();

    static AdditionalLayoutInfo getAdditionalLayoutInfo( const QString& layout );

    /* A model is a physical configuration of a keyboard, e.g. 105-key PC
     * or TKL 88-key physical size.
     */
    KeyboardModelsModel* keyboardModels() const;
    /* A layout describes the basic keycaps / language assigned to the
     * keys of the physical keyboard, e.g. English (US) or Russian.
     */
    KeyboardLayoutModel* keyboardLayouts() const;
    /* A variant describes a variant of the basic keycaps; this can
     * concern options (dead keys), or different placements of the keycaps
     * (dvorak).
     */
    KeyboardVariantsModel* keyboardVariants() const;

    /** @brief Call this to change application language
     *
     * The models (for keyboard model, layouts and variants) provide
     * translations of strings in the xkb table, so need to be
     * notified of language changes as well.
     *
     * Only widgets get LanguageChange events, so one of them will
     * need to call this.
     */
    void retranslate();

    void setConfigurationMap( const QVariantMap& configurationMap );

signals:
    void prettyStatusChanged();

private:
    void updateVariants( const QPersistentModelIndex& currentItem, QString currentVariant = QString() );

    /* These two methods are used in tandem to apply changes to the
     * keyboard layout. This introduces a slight delay between selecting
     * a keyboard, and applying it to the system -- so that if you
     * scroll through or down-arrow through the list of keyboards,
     * you don't get buried under xkbset processes.
     *
     * xkbChanged() is called when the selection changes, and triggers
     * a delayed call to xkbApply() which does the actual work.
     */
    void xkbChanged( int index );
    void xkbApply();

    KeyboardModelsModel* m_keyboardModelsModel;
    KeyboardLayoutModel* m_keyboardLayoutsModel;
    KeyboardVariantsModel* m_keyboardVariantsModel;

    QString m_selectedLayout;
    QString m_selectedModel;
    QString m_selectedVariant;

    // Layout (and corresponding info) added if current one doesn't support ASCII (e.g. Russian or Japanese)
    AdditionalLayoutInfo m_additionalLayoutInfo;

    QTimer m_setxkbmapTimer;

    // From configuration
    QString m_xOrgConfFileName;
    QString m_convertedKeymapPath;
    bool m_writeEtcDefaultKeyboard = true;

    // The state determines whether we guess settings or preserve them:
    // - Initial -> Guessing
    // - Initial -> UserSelected
    // - Guessing -> Initial
    enum class State
    {
        Initial,  // after configuration, nothing special going on
        Guessing,  // on activation
        UserSelected  // explicit choice is made, preserve that
    };
    State m_state = State::Initial;

    /** @brief Handles state change when selections in model, variant, layout
     *
     * This handles the Initial -> UserSelected transition in particular.
     */
    void selectionChange();
};


#endif
