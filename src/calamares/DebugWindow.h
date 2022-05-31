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

#include <QPointer>
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

/** @brief Manager for meta-windows (Debug and About windows)
 *
 * Only one DebugWindow is expected to be around. This class manages
 * (exactly one) DebugWindow and can create and destroy it as needed.
 * It is available to the Calamares panels as object `DebugWindow`.
 *
 * The about() method shows a modal pop-up about Calamares.
 */
class DebugWindowManager : public QObject
{
    Q_OBJECT

    /// @brief Proxy to Settings::debugMode() default @c false
    Q_PROPERTY( bool enabled READ enabled CONSTANT FINAL )

    /** @brief Is the debug window visible?
     *
     * Writing @c true to this **may** make the debug window visible to
     * the user; only if debugMode() is on.
     */
    Q_PROPERTY( bool visible READ visible WRITE show NOTIFY visibleChanged )

public:
    DebugWindowManager( QObject* parent = nullptr );
    virtual ~DebugWindowManager() override = default;

public Q_SLOTS:
    bool enabled() const;
    bool visible() const { return m_visible; }
    void show( bool visible );
    void toggle();

    void about();

signals:
    void visibleChanged( bool visible );

private:
    QPointer< DebugWindow > m_debugWindow;
    bool m_visible = false;
};


}  // namespace Calamares
#endif
