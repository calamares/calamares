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

#ifndef LIBCALAMARESUI_PRETTYRADIOBUTTON_H
#define LIBCALAMARESUI_PRETTYRADIOBUTTON_H

#include "DllMacro.h"

#include <QRadioButton>

class QButtonGroup;
class QComboBox;
class QGridLayout;
class QHBoxLayout;

namespace Calamares
{
class ClickableLabel;

/** @brief A radio button with fancy label next to it.
 *
 * The fancy label is used so that the text alongside the radio
 * button can word-wrap, be multi-line, and support rich text.
 *
 * The radio button itself can be retrieved with buttonWidget(),
 * and the whole behaves a lot like a label. Extra options can be
 * added to the display (options are hidden when the button is
 * not selected) with addOptionsComboBox().
 */
class UIDLLEXPORT PrettyRadioButton : public QWidget
{
    Q_OBJECT
public:
    explicit PrettyRadioButton( QWidget* parent = nullptr );
    virtual ~PrettyRadioButton() { }

    /// @brief Passes @p text on to the ClickableLabel
    void setText( const QString& text );

    // Icon applies to the radio-button part
    void setIconSize( const QSize& size );
    QSize iconSize() const;
    void setIcon( const QIcon& icon );

    // Applies to the radio-button part
    void setChecked( bool checked );
    bool isChecked() const;

    /** @brief Adds the radio-button part to the given @p group
     *
     * For managing the pretty-radio-button in button groups like normal
     * radio buttons, call addToGroup() rather that group->addButton().
     */
    void addToGroup( QButtonGroup* group, int id = -1 );

    /// @brief Add an options drop-down to this button.
    void addOptionsComboBox( QComboBox* );

protected slots:
    /// Options are hidden when the radio button is off
    void toggleOptions( bool checked );

protected:
    ClickableLabel* m_label;
    QRadioButton* m_radio;
    QGridLayout* m_mainLayout;
    QHBoxLayout* m_optionsLayout;
};

}  // namespace Calamares
#endif  // LIBCALAMARESUI_PRETTYRADIOBUTTON_H
