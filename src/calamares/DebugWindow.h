/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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
