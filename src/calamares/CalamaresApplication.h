/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018-2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef CALAMARESAPPLICATION_H
#define CALAMARESAPPLICATION_H

#include <QApplication>

class CalamaresWindow;

namespace Calamares
{
class ModuleManager;
}


/**
 * @brief The CalamaresApplication class extends QApplication to handle
 * Calamares startup and lifetime of main components.
 */
class CalamaresApplication : public QApplication
{
    Q_OBJECT
public:
    CalamaresApplication( int& argc, char* argv[] );
    ~CalamaresApplication() override;

    /**
     * @brief init handles the first part of Calamares application startup.
     * After the main window shows up, the latter part of the startup sequence
     * (including modules loading) happens asynchronously.
     */
    void init();
    static CalamaresApplication* instance();

    /**
     * @brief mainWindow returns the Calamares application main window.
     */
    CalamaresWindow* mainWindow();

private slots:
    void initView();
    void initViewSteps();
    void initFailed( const QStringList& l );

private:
    // Initialization steps happen in this order
    void initQmlPath();
    void initBranding();
    void initModuleManager();
    void initJobQueue();

    CalamaresWindow* m_mainwindow;
    Calamares::ModuleManager* m_moduleManager;
};

#endif  // CALAMARESAPPLICATION_H
