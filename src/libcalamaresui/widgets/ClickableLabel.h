/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef LIBCALAMARESUI_WIDGETS_CLICKABLELABEL_H
#define LIBCALAMARESUI_WIDGETS_CLICKABLELABEL_H

#include <QElapsedTimer>
#include <QLabel>

#include "DllMacro.h"

namespace Calamares
{
namespace Widgets
{
/** @brief A Label where the whole label area is clickable
 *
 * When clicking anywhere on the Label (text, background, whatever)
 * the signal clicked() is emitted. Use this as a buddy for radio
 * buttons or other clickable things where you want mouse interaction
 * with the label, to be the same as mouse interaction with the control.
 */
class UIDLLEXPORT ClickableLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ClickableLabel( QWidget* parent = nullptr );
    explicit ClickableLabel( const QString& text, QWidget* parent = nullptr );
    ~ClickableLabel() override;

signals:
    void clicked();

protected:
    virtual void mousePressEvent( QMouseEvent* event ) override;
    virtual void mouseReleaseEvent( QMouseEvent* event ) override;

private:
    QElapsedTimer m_time;
};
}  // namespace Widgets
}  // namespace Calamares

#endif  // LIBCALAMARESUI_WIDGETS_CLICKABLELABEL_H
