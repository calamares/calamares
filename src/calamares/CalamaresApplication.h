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

class CalamaresApplication : public QApplication
{
    Q_OBJECT
public:
    CalamaresApplication( int& argc, char* argv[] );
    virtual ~CalamaresApplication();

    void init();
    static CalamaresApplication* instance();

    void setDebug( bool enabled );
    bool isDebug();

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
