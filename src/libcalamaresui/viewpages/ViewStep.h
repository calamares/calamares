/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef VIEWSTEP_H
#define VIEWSTEP_H

#include "DllMacro.h"
#include "Job.h"

#include "modulesystem/InstanceKey.h"
#include "modulesystem/Requirement.h"

#include <QList>
#include <QObject>
#include <QSize>

namespace Calamares
{

/**
 * @brief The ViewStep class is the base class for all view modules.
 * A view module is a Calamares module which has at least one UI page (exposed as
 * ViewStep::widget), and can optionally create Calamares jobs at runtime.
 * As of early 2020, a view module can be implemented by deriving from ViewStep
 * in C++ (as a Qt Plugin or a Qml ViewStep).
 *
 * A ViewStep can describe itself in human-readable format for the SummaryPage
 * (which shows all of the things which have been collected to be done in the
 * next exec-step) through prettyStatus() and createSummaryWidget().
 */
class UIDLLEXPORT ViewStep : public QObject
{
    Q_OBJECT
public:
    explicit ViewStep( QObject* parent = nullptr );
    ~ViewStep() override;

    /** @brief Human-readable name of the step
     *
     * This (translated) string is shown in the sidebar (progress)
     * and during installation. There is no default.
     */
    virtual QString prettyName() const = 0;

    /** @brief Describe what this step will do during install
     *
     * Optional. May return a non-empty string describing what this
     * step is going to do (should be translated). This is also used
     * in the summary page to describe what is going to be done.
     * Return an empty string to provide no description.
     *
     * The default implementation returns an empty string, so nothing
     * will be displayed for this step when a summary is shown.
     */
    virtual QString prettyStatus() const;

    /** @brief Return a long description what this step will do during install
     *
     * Optional. May return a widget which will be inserted in the summary
     * page. The caller takes ownership of the widget. Return nullptr to
     * provide no widget. In general, this is only used for complicated
     * steps where prettyStatus() is not sufficient.
     *
     * The default implementation returns nullptr, so nothing
     * will be displayed for this step when a summary is shown.
     */
    virtual QWidget* createSummaryWidget() const;

    /** @brief Get (or create) the widget for this view step
     *
     * While a view step **may** create the widget when it is loaded,
     * it is recommended to wait with widget creation until the
     * widget is actually asked for: a view step **may** be used
     * without a UI.
     */
    virtual QWidget* widget() = 0;

    /** @brief Get margins for this widget
     *
     * This is called by the layout manager to find the desired
     * margins (width is used for left and right margin, height is
     * used for top and bottom margins) for the widget. The
     * @p panelSides indicates where there are panels in the overall
     * layout: horizontally and / or vertically adjacent (or none!)
     * to the view step's widget.
     *
     * Should return a size based also on QStyle metrics for layout.
     * The default implementation just returns the default layout metrics
     * (often 11 pixels on a side).
     */
    virtual QSize widgetMargins( Qt::Orientations panelSides );

    /**
     * @brief Multi-page support, go next
     *
     * Multi-page view steps need to manage the content visible in the widget
     * themselves. This method is called when the user clicks the *next*
     * button, and should switch to the next of the multiple-pages. It needs
     * to be consistent with both isNextEnabled() and isAtEnd().
     *
     * In particular: when isAtEnd() returns false, next() is called when
     * the user clicks the button and a new page should be shown by this
     * view step. When isAtEnd() returns true, clicking the button will
     * switch to the next view step in sequence, rather than a next page
     * in the current view step.
     */
    virtual void next();
    /// @brief Multi-page support, go back
    virtual void back();

    /// @brief Can the user click *next* with currently-filled-in data?
    virtual bool isNextEnabled() const = 0;
    /// @brief Can the user click *previous* with currently-filled-in data?
    virtual bool isBackEnabled() const = 0;

    /**
     * @brief Multi-page support, switch to previous view step?
     *
     * For a multi-page view step, this indicates that the first (beginning)
     * page is showing. Clicking *previous* when at the beginning of a view
     * step, switches to the previous step, not the previous page of the
     * current view step.
     */
    virtual bool isAtBeginning() const = 0;
    /// @brief Multi-page support, switch to next view step?
    virtual bool isAtEnd() const = 0;

    /**
     * @brief onActivate called every time a ViewStep is shown, either by going forward
     * or backward.
     * The default implementation does nothing.
     */
    virtual void onActivate();

    /**
     * @brief onLeave called every time a ViewStep is hidden and control passes to
     * another ViewStep, either by going forward or backward.
     * The default implementation does nothing.
     */
    virtual void onLeave();

    /**
     * @brief Jobs needed to run this viewstep
     *
     * When a ViewStep is listed in the exec section, its jobs are executed instead.
     * This function returns that list of jobs; an empty list is ok.
     */
    virtual JobList jobs() const = 0;

    void setModuleInstanceKey( const Calamares::ModuleSystem::InstanceKey& instanceKey );
    Calamares::ModuleSystem::InstanceKey moduleInstanceKey() const { return m_instanceKey; }

    virtual void setConfigurationMap( const QVariantMap& configurationMap );

    /**
     * @brief Can this module proceed, on this machine?
     *
     * This is called asynchronously at startup, and returns a list of
     * the requirements that the module has checked, and their status.
     * See Calamares::RequirementEntry for details.
     */
    virtual RequirementsList checkRequirements();

signals:
    /// @brief Tells the viewmanager to enable the *next* button according to @p status
    void nextStatusChanged( bool status );

    /* Emitted when the viewstep thinks it needs more space than is currently
     * available for display. @p size is the requested space, that is needed
     * to display the entire page.
     *
     * This request may be silently ignored.
     */
    void ensureSize( QSize enlarge ) const;

protected:
    Calamares::ModuleSystem::InstanceKey m_instanceKey;
};

using ViewStepList = QList< ViewStep* >;
}  // namespace Calamares

#endif  // VIEWSTEP_H
