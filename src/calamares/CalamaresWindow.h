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

#include <QWidget>

#include <memory>

namespace Calamares
{
class DebugWindowManager;
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

protected:
    virtual void closeEvent( QCloseEvent* e ) override;

private:
    Calamares::DebugWindowManager* m_debugManager = nullptr;
    Calamares::ViewManager* m_viewManager = nullptr;
};

#endif  // CALAMARESWINDOW_H
