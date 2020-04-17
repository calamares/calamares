/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017, 2020, Adriaan de Groot <groot@kde.org>
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

#ifndef VIEWSTEP_H
#define VIEWSTEP_H

#include "Job.h"
#include "DllMacro.h"

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
 * in C++ (as a Qt Plugin or a Qml ViewStep) or in Python with the PythonQt interface
 * (which also mimics the ViewStep class).
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
    virtual ~ViewStep() override;

    virtual QString prettyName() const = 0;

    /**
     * Optional. May return a non-empty string describing what this
     * step is going to do (should be translated). This is also used
     * in the summary page to describe what is going to be done.
     * Return an empty string to provide no description.
     */
    virtual QString prettyStatus() const;

    /**
     * Optional. May return a widget which will be inserted in the summary
     * page. The caller takes ownership of the widget. Return nullptr to
     * provide no widget. In general, this is only used for complicated
     * steps where prettyStatus() is not sufficient.
     */
    virtual QWidget* createSummaryWidget() const;

    //TODO: we might want to make this a QSharedPointer
    virtual QWidget* widget() = 0;

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
