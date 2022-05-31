/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef LIBCALAMARESUI_WIDGETS_PRETTYRADIOBUTTON_H
#define LIBCALAMARESUI_WIDGETS_PRETTYRADIOBUTTON_H

#include "DllMacro.h"

#include <QRadioButton>

class QButtonGroup;
class QComboBox;
class QGridLayout;
class QHBoxLayout;

namespace Calamares
{
namespace Widgets
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
    ~PrettyRadioButton() override {}

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
}  // namespace Widgets
}  // namespace Calamares
#endif  // LIBCALAMARESUI_WIDGETS_PRETTYRADIOBUTTON_H
