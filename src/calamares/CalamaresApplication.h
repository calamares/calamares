/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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

#define APP CalamaresApplication::instance()

class CalamaresWindow;

class CalamaresApplication : public QApplication
{
    Q_OBJECT
public:
    CalamaresApplication( int& argc, char *argv[] );
    virtual ~CalamaresApplication();

    void init();
    static CalamaresApplication* instance();

    void initSettings();
    void initBranding();
    void initPlugins();
    void initJobQueue();

private:
    CalamaresWindow* m_mainwindow;

    //QPointer< Calamares::JobQueue > m_jobQueue;
};

#endif //CALAMARESAPPLICATION_H
