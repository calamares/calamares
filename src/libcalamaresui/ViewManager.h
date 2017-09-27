/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
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

/**
 * @brief The ViewManager class handles progression through view pages.
 * @note Singleton object, only use through ViewManager::instance().
 */
class UIDLLEXPORT ViewManager : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief instance access to the ViewManager singleton.
     * @return pointer to the singleton instance.
     */
    static ViewManager* instance();
    static ViewManager* instance( QObject* parent );

    /**
     * @brief centralWidget always returns the central widget in the Calamares main
     * window.
     * @return a pointer to the active QWidget (usually a wizard page provided by a
     * view module).
     */
    QWidget* centralWidget();

    /**
     * @brief addViewStep appends a view step to the roster.
     * @param step a pointer to the ViewStep object to add.
     * @note a ViewStep is the active instance of a view module, it aggregates one
     * or more view pages, plus zero or more jobs which may be created at runtime.
     */
    void addViewStep( ViewStep* step );

    /**
     * @brief viewSteps returns the list of currently present view steps.
     * @return the ViewStepList.
     * This should only return an empty list before startup is complete.
     */
    ViewStepList viewSteps() const;

    /**
     * @brief currentStep returns the currently active ViewStep, i.e. the ViewStep
     * which owns the currently visible view page.
     * @return the active ViewStep. Do not confuse this with centralWidget().
     * @see ViewStep::centralWidget
     */
    ViewStep* currentStep() const;

    /**
     * @brief currentStepIndex returns the index of the currently active ViewStep.
     * @return the index.
     */
    int currentStepIndex() const;


public slots:
    /**
     * @brief next moves forward to the next page of the current ViewStep (if any),
     * or to the first page of the next ViewStep if the current ViewStep doesn't
     * have any more pages.
     */
    void next();

    /**
     * @brief back moves backward to the previous page of the current ViewStep (if any),
     * or to the last page of the previous ViewStep if the current ViewStep doesn't
     * have any pages before the current one.
     */
    void back();

    /**
     * @brief onInstallationFailed displays an error message when a fatal failure
     * happens in a ViewStep.
     * @param message the error string.
     * @param details the details string.
     */
    void onInstallationFailed( const QString& message, const QString& details );

signals:
    void currentStepChanged();
    void enlarge( QSize enlarge ) const;  // See ViewStep::enlarge()

private:
    explicit ViewManager( QObject* parent = nullptr );
    virtual ~ViewManager();

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
