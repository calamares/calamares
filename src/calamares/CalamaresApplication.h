/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2018-2019, Adriaan de Groot <groot@kde.org>
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
    virtual ~CalamaresApplication();

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
