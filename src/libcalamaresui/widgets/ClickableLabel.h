/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
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

#ifndef LIBCALAMARESUI_CLICKABLELABEL_H
#define LIBCALAMARESUI_CLICKABLELABEL_H

#include <QElapsedTimer>
#include <QLabel>

#include "DllMacro.h"

namespace Calamares
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
    virtual ~ClickableLabel() override;

signals:
    void clicked();

protected:
    virtual void mousePressEvent( QMouseEvent* event ) override;
    virtual void mouseReleaseEvent( QMouseEvent* event ) override;

private:
    QElapsedTimer m_time;
};

}  // namespace Calamares

#endif  // LIBCALAMARESUI_CLICKABLELABEL_H
