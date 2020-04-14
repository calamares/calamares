/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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

#ifndef WELCOMEPAGE_H
#define WELCOMEPAGE_H

#include "locale/LabelModel.h"

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
    explicit WelcomePage( Config* conf, QWidget* parent = nullptr );

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
    void showAboutBox();

protected:
    void focusInEvent( QFocusEvent* e ) override;  //choose the child widget to focus

private:
    /// @brief Fill the list of languages with the available translations
    void initLanguages();

    Ui::WelcomePage* ui;
    CheckerContainer* m_checkingWidget;
    CalamaresUtils::Locale::LabelModel* m_languages;

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
