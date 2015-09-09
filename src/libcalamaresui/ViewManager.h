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

#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H

#include "UiDllMacro.h"
#include "Typedefs.h"

#include <QList>
#include <QPushButton>
#include <QStackedWidget>


namespace Calamares
{

class ViewStep;
class ExecutionViewStep;

class UIDLLEXPORT ViewManager : public QObject
{
    Q_OBJECT
public:
    static ViewManager* instance();

    explicit ViewManager( QObject* parent = nullptr );
    virtual ~ViewManager();

    QWidget* centralWidget();

    void addViewStep( ViewStep* step );

    ViewStepList viewSteps() const;
    ViewStep* currentStep() const;
    int currentStepIndex() const;


public slots:
    void next();
    void back();

    void onInstallationFailed( const QString& message, const QString& details );

signals:
    void currentStepChanged();

private:
    void insertViewStep( int before, ViewStep* step );

    static ViewManager* s_instance;

    ViewStepList m_steps;
    int m_currentStep;

    QWidget* m_widget;
    QStackedWidget* m_stack;
    QPushButton* m_back;
    QPushButton* m_next;
    QPushButton* m_quit;
};

}

#endif // VIEWMANAGER_H
