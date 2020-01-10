/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2015, Teo Mrnjavac <teo@kde.org>
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

#ifndef CALAMARES_DEBUGWINDOW_H
#define CALAMARES_DEBUGWINDOW_H

#include "VariantModel.h"

#include <QVariant>
#include <QWidget>

#include <memory>

namespace Calamares
{

// From the .ui file
namespace Ui
{
class DebugWindow;
}

class DebugWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DebugWindow();

signals:
    void closed();

protected:
    void closeEvent( QCloseEvent* e ) override;

private:
    Ui::DebugWindow* m_ui;
    QVariant m_globals;
    QVariant m_module;
    std::unique_ptr< VariantModel > m_globals_model;
    std::unique_ptr< VariantModel > m_module_model;
};


}  // namespace Calamares
#endif
