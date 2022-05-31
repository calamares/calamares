/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef WELCOMEPAGE_H
#define WELCOMEPAGE_H

#include "locale/TranslationsModel.h"

#include <QStyledItemDelegate>
#include <QWidget>

namespace Ui
{
class WelcomePage;
}

class CheckerContainer;
class Config;
class WelcomePage : public QWidget
{
    Q_OBJECT
public:
    WelcomePage( Config* config, QWidget* parent = nullptr );

    enum class Button
    {
        Support,
        Donate,
        KnownIssues,
        ReleaseNotes
    };

    /// @brief Configure the button @p n, to open @p url
    void setupButton( Button b, const QString& url );

    /// @brief Set international language-selector icon
    void setLanguageIcon( QPixmap );

    /// @brief Results of requirements checking
    bool verdict() const;

    /// @brief Change the language from an external source.
    void externallySelectedLanguage( int row );

    void init();

public slots:
    void retranslate();

protected:
    void focusInEvent( QFocusEvent* e ) override;  //choose the child widget to focus

private:
    /// @brief Fill the list of languages with the available translations
    void initLanguages();

    Ui::WelcomePage* ui;
    CheckerContainer* m_checkingWidget;
    CalamaresUtils::Locale::TranslationsModel* m_languages;

    Config* m_conf;
};

/** @brief Delegate to display language information in two columns.
 *
 * Displays the native language name and the English language name.
 */
class LocaleTwoColumnDelegate : public QStyledItemDelegate
{
public:
    using QStyledItemDelegate::QStyledItemDelegate;

    void paint( QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const override;
};

#endif  // WELCOMEPAGE_H
