/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017-2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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
    Q_PROPERTY( int currentStepIndex READ currentStepIndex NOTIFY currentStepChanged FINAL )

    Q_PROPERTY( bool nextEnabled READ nextEnabled NOTIFY nextEnabledChanged FINAL )
    Q_PROPERTY( QString nextLabel READ nextLabel NOTIFY nextLabelChanged FINAL )
    Q_PROPERTY( QString nextIcon READ nextIcon NOTIFY nextIconChanged FINAL )

    Q_PROPERTY( bool backEnabled READ backEnabled NOTIFY backEnabledChanged FINAL )
    Q_PROPERTY( QString backLabel READ backLabel NOTIFY backLabelChanged FINAL )
    Q_PROPERTY( QString backIcon READ backIcon NOTIFY backIconChanged FINAL )

    Q_PROPERTY( bool quitEnabled READ quitEnabled NOTIFY quitEnabledChanged FINAL )
    Q_PROPERTY( QString quitLabel READ quitLabel NOTIFY quitLabelChanged FINAL )
    Q_PROPERTY( QString quitIcon READ quitIcon NOTIFY quitIconChanged FINAL )
    Q_PROPERTY( QString quitTooltip READ quitTooltip NOTIFY quitTooltipChanged FINAL )

    Q_PROPERTY( bool quitVisible READ quitVisible NOTIFY quitVisibleChanged FINAL )

    Q_PROPERTY( bool backAndNextVisible READ backAndNextVisible NOTIFY backAndNextVisibleChanged FINAL )

    ///@brief Sides on which the ViewManager has side-panels
    Q_PROPERTY( Qt::Orientations panelSides READ panelSides WRITE setPanelSides MEMBER m_panelSides )

    // Global properties, where ViewManager proxies to Settings
    Q_PROPERTY( bool isDebugMode READ isDebugMode CONSTANT FINAL )
    Q_PROPERTY( bool isChrootMode READ isChrootMode CONSTANT FINAL )
    Q_PROPERTY( bool isSetupMode READ isSetupMode CONSTANT FINAL )
    Q_PROPERTY( QString logFilePath READ logFilePath CONSTANT FINAL )

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
     * @brief Called when "Cancel" is clicked; asks for confirmation.
     * Other means of closing Calamares also call this method, e.g. alt-F4.
     * At the end of installation, no confirmation is asked.
     *
     * @return @c true if the user confirms closing the window.
     */
    bool confirmCancelInstallation();

    Qt::Orientations panelSides() const { return m_panelSides; }
    void setPanelSides( Qt::Orientations panelSides ) { m_panelSides = panelSides; }

public Q_SLOTS:
    /**
     * @brief next moves forward to the next page of the current ViewStep (if any),
     * or to the first page of the next ViewStep if the current ViewStep doesn't
     * have any more pages.
     */
    void next();
    bool nextEnabled() const
    {
        return m_nextEnabled;  ///< Is the next-button to be enabled
    }
    QString nextLabel() const
    {
        return m_nextLabel;  ///< What should be displayed on the next-button
    }
    QString nextIcon() const
    {
        return m_nextIcon;  ///< Name of the icon to show
    }

    /**
     * @brief back moves backward to the previous page of the current ViewStep (if any),
     * or to the last page of the previous ViewStep if the current ViewStep doesn't
     * have any pages before the current one.
     */
    void back();
    bool backEnabled() const
    {
        return m_backEnabled;  ///< Is the back-button to be enabled
    }
    QString backLabel() const
    {
        return m_backLabel;  ///< What should be displayed on the back-button
    }
    QString backIcon() const
    {
        return m_backIcon;  ///< Name of the icon to show
    }

    bool backAndNextVisible() const
    {
        return m_backAndNextVisible;  ///< Is the quit-button to be enabled
    }
    /**
     * @brief Probably quit
     *
     * Asks for confirmation if necessary. Terminates the application.
     */
    void quit();
    bool quitEnabled() const
    {
        return m_quitEnabled;  ///< Is the quit-button to be enabled
    }
    QString quitLabel() const
    {
        return m_quitLabel;  ///< What should be displayed on the quit-button
    }
    QString quitIcon() const
    {
        return m_quitIcon;  ///< Name of the icon to show
    }
    bool quitVisible() const
    {
        return m_quitVisible;  ///< Should the quit-button be visible
    }
    QString quitTooltip() const { return m_quitTooltip; }

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

    /** @brief Tell the manager that initialization / loading is complete.
     *
     * Call this at least once, to tell the manager to activate the first page.
     */
    void onInitComplete();

    /// @brief Connected to ViewStep::nextStatusChanged for all steps
    void updateNextStatus( bool enabled );

    /// @brief Proxy to Settings::debugMode() default @c false
    bool isDebugMode() const;
    /// @brief Proxy to Settings::doChroot() default @c true
    bool isChrootMode() const;
    /// @brief Proxy to Settings::isSetupMode() default @c false
    bool isSetupMode() const;
    /// @brief Proxy to Logger::logFile(), default empty
    QString logFilePath() const;

signals:
    void currentStepChanged();
    void ensureSize( QSize size ) const;  // See ViewStep::ensureSize()
    void cancelEnabled( bool enabled ) const;

    void nextEnabledChanged( bool ) const;
    void nextLabelChanged( QString ) const;
    void nextIconChanged( QString ) const;

    void backEnabledChanged( bool ) const;
    void backLabelChanged( QString ) const;
    void backIconChanged( QString ) const;
    void backAndNextVisibleChanged( bool ) const;

    void quitEnabledChanged( bool ) const;
    void quitLabelChanged( QString ) const;
    void quitIconChanged( QString ) const;
    void quitVisibleChanged( bool ) const;
    void quitTooltipChanged( QString ) const;

private:
    explicit ViewManager( QObject* parent = nullptr );
    ~ViewManager() override;

    void insertViewStep( int before, ViewStep* step );
    void updateButtonLabels();
    void updateCancelEnabled( bool enabled );
    void updateBackAndNextVisibility( bool visible );

    inline bool currentStepValid() const { return ( 0 <= m_currentStep ) && ( m_currentStep < m_steps.length() ); }

    static ViewManager* s_instance;

    ViewStepList m_steps;
    int m_currentStep;

    QWidget* m_widget;
    QStackedWidget* m_stack;

    bool m_nextEnabled = false;
    QString m_nextLabel;
    QString m_nextIcon;  ///< Name of icon to show on button

    bool m_backEnabled = false;
    QString m_backLabel;
    QString m_backIcon;

    bool m_backAndNextVisible = true;

    bool m_quitEnabled = false;
    QString m_quitLabel;
    QString m_quitIcon;
    QString m_quitTooltip;
    bool m_quitVisible = true;

    Qt::Orientations m_panelSides;

public:
    /** @section Model
     *
     * These are the methods and enums used for the as-a-model part
     * of the ViewManager.
     */
    enum Role
    {
        ProgressTreeItemCurrentIndex = Qt::UserRole + 13  ///< Index (row) of the current step
    };

    QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const override;
    int rowCount( const QModelIndex& parent = QModelIndex() ) const override;
};

}  // namespace Calamares

#endif  // VIEWMANAGER_H
