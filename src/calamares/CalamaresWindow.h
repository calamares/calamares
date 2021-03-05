/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017-2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef CALAMARESWINDOW_H
#define CALAMARESWINDOW_H

#include <QPointer>
#include <QWidget>

namespace Calamares
{
class DebugWindow;
class ViewManager;
}  // namespace Calamares

/**
 * @brief The CalamaresWindow class represents the main window of the Calamares UI.
 */
class CalamaresWindow : public QWidget
{
    Q_OBJECT
public:
    CalamaresWindow( QWidget* parent = nullptr );
    ~CalamaresWindow() override {}

public Q_SLOTS:
    /**
     * This asks the main window to grow to accomodate @p size pixels, to accomodate
     * larger-than-expected window contents. The enlargement may be silently
     * ignored.
     */
    void ensureSize( QSize size );

    /** @brief Set visibility of debug window
     *
     * Shows or hides the debug window, depending on @p show.
     * If Calamares is not in debug mode, nothing happens and the debug
     * window remains hidden.
     */
    void showDebugWindow( bool show );

Q_SIGNALS:
    void debugWindowShown( bool show );

protected:
    virtual void closeEvent( QCloseEvent* e ) override;

private:
    QPointer< Calamares::DebugWindow > m_debugWindow;  // Managed by self
    Calamares::ViewManager* m_viewManager;
};

#endif  // CALAMARESWINDOW_H
