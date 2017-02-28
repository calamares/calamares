/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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

#ifndef CALAMARESAPPLICATION_H
#define CALAMARESAPPLICATION_H

#include "Typedefs.h"

#include <QApplication>

#define APP CalamaresApplication::instance()

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
    virtual ~CalamaresApplication();

    /**
     * @brief init handles the first part of Calamares application startup.
     * After the main window shows up, the latter part of the startup sequence
     * (including modules loading) happens asynchronously.
     */
    void init();
    static CalamaresApplication* instance();

    /**
     * @brief setDebug controls whether debug mode is enabled
     */
    void setDebug( bool enabled );

    /**
     * @brief isDebug returns true if running in debug mode, otherwise false.
     */
    bool isDebug();

    /**
     * @brief mainWindow returns the Calamares application main window.
     */
    CalamaresWindow* mainWindow();

private slots:
    void initView();
    void initViewSteps();

private:
    void initQmlPath();
    void initSettings();
    void initBranding();
    void initModuleManager();
    void initJobQueue();

    CalamaresWindow* m_mainwindow;
    Calamares::ModuleManager* m_moduleManager;

    bool m_debugMode;
};

#endif //CALAMARESAPPLICATION_H
