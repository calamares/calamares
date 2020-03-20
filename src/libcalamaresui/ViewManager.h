/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017-2018, Adriaan de Groot <groot@kde.org>
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

#include "DllMacro.h"
#include "viewpages/ViewStep.h"

#include <QAbstractListModel>
#include <QList>
#include <QPushButton>
#include <QStackedWidget>

namespace Calamares
{
/**
 * @brief The ViewManager class handles progression through view pages.
 * @note Singleton object, only use through ViewManager::instance().
 */
class UIDLLEXPORT ViewManager : public QAbstractListModel
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

    /**
     * @ brief Called when "Cancel" is clicked; asks for confirmation.
     * Other means of closing Calamares also call this method, e.g. alt-F4.
     * At the end of installation, no confirmation is asked. Returns true
     * if the user confirms closing the window.
     */
    bool confirmCancelInstallation();

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

    /** @brief Replaces the stack with a view step stating that initialization failed.
     *
     * @param modules a list of failed modules.
     */
    void onInitFailed( const QStringList& modules );

signals:
    void currentStepChanged();
    void enlarge( QSize enlarge ) const;  // See ViewStep::enlarge()
    void cancelEnabled( bool enabled ) const;

private:
    explicit ViewManager( QObject* parent = nullptr );
    virtual ~ViewManager() override;

    void insertViewStep( int before, ViewStep* step );
    void updateButtonLabels();
    void updateCancelEnabled( bool enabled );

    bool isAtVeryEnd() const
    {
        return ( m_currentStep >= m_steps.count() )
            || ( m_currentStep == m_steps.count() - 1 && m_steps.last()->isAtEnd() );
    }

    static ViewManager* s_instance;

    ViewStepList m_steps;
    int m_currentStep;

    QWidget* m_widget;
    QStackedWidget* m_stack;
    QPushButton* m_back;
    QPushButton* m_next;
    QPushButton* m_quit;

public:
    /** @section Model
     *
     * These are the methods and enums used for the as-a-model part
     * of the ViewManager.
     */
    enum Role
    {
        ProgressTreeItemCurrentRole = Qt::UserRole + 11,  ///< Is this the *current* step?
        ProgressTreeItemCompletedRole = Qt::UserRole + 12  ///< Are we past this one?
    };

    QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const override;
    int rowCount( const QModelIndex& parent = QModelIndex() ) const override;

    QHash< int, QByteArray > roleNames() const override;
};

}  // namespace Calamares

#endif  // VIEWMANAGER_H
