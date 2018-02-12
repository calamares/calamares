/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2016, Teo Mrnjavac <teo@kde.org>
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

#include "PythonQtViewStep.h"
#include "utils/Logger.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/PythonQtUtils.h"
#include "utils/Retranslator.h"
#include "viewpages/PythonQtJob.h"

#include <gui/PythonQtScriptingConsole.h>

#include <QBoxLayout>
#include <QWidget>


namespace Calamares
{

PythonQtViewStep::PythonQtViewStep( PythonQtObjectPtr cxt,
                                    QObject* parent )
    : ViewStep( parent )
    , m_widget( new QWidget() )
    , m_cxt( cxt )
{
    PythonQt* pq = PythonQt::self();
    Q_ASSERT( pq );

    // The @calamares_module decorator should have filled _calamares_module_typename
    // for us.
    QString className = m_cxt.getVariable( "_calamares_module_typename" ).toString();

    // Instantiate an object of the class marked with @calamares_module and
    // store it as _calamares_module.
    pq->evalScript( m_cxt, QString( "_calamares_module = %1()" )
                                            .arg( className ) );
    m_obj = pq->lookupObject( m_cxt, "_calamares_module" );

    Q_ASSERT( !m_obj.isNull() );    // no entry point, no party

    // Prepare the base widget for the module's pages
    m_widget->setLayout( new QVBoxLayout );
    CalamaresUtils::unmarginLayout( m_widget->layout() );
    m_cxt.addObject( "_calamares_module_basewidget", m_widget );

    CALAMARES_RETRANSLATE_WIDGET( m_widget,
        CalamaresUtils::lookupAndCall( m_obj,
                                       { "retranslate" },
                                       { CalamaresUtils::translatorLocaleName() } );
    )
}


QString
PythonQtViewStep::prettyName() const
{
    return CalamaresUtils::lookupAndCall( m_obj,
                                          { "prettyName",
                                            "prettyname",
                                            "pretty_name" } ).toString();
}


QWidget*
PythonQtViewStep::widget()
{
    if ( m_widget->layout()->count() > 1 )
        cWarning() << "PythonQtViewStep wrapper widget has more than 1 child. "
                    "This should never happen.";

    bool nothingChanged = m_cxt.evalScript(
        "_calamares_module.widget() in _calamares_module_basewidget.children()" ).toBool();
    if ( nothingChanged )
        return m_widget;

    // Else, we either don't have a child widget, or we have a child widget that
    // was previously set and doesn't apply any more since the Python module
    // set a new one.

    // First we clear the layout, which should only ever have 1 item.
    // We only remove from the layout and not delete because Python is in charge
    // of memory management for these widgets.
    while ( m_widget->layout()->itemAt( 0 ) )
        m_widget->layout()->takeAt( 0 );

    m_cxt.evalScript(
        "_calamares_module_basewidget.layout().addWidget(_calamares_module.widget())" );

    return m_widget;
}


void
PythonQtViewStep::next()
{
    CalamaresUtils::lookupAndCall( m_obj, { "next" } );
}


void
PythonQtViewStep::back()
{
    CalamaresUtils::lookupAndCall( m_obj, { "back" } );
}


bool
PythonQtViewStep::isNextEnabled() const
{
    return CalamaresUtils::lookupAndCall( m_obj,
                                          { "isNextEnabled",
                                            "isnextenabled",
                                            "is_next_enabled" } ).toBool();
}


bool
PythonQtViewStep::isBackEnabled() const
{
    return CalamaresUtils::lookupAndCall( m_obj,
                                          { "isBackEnabled",
                                            "isbackenabled",
                                            "is_back_enabled" } ).toBool();
}


bool
PythonQtViewStep::isAtBeginning() const
{
    return CalamaresUtils::lookupAndCall( m_obj,
                                          { "isAtBeginning",
                                            "isatbeginning",
                                            "is_at_beginning" } ).toBool();
}


bool
PythonQtViewStep::isAtEnd() const
{
    return CalamaresUtils::lookupAndCall( m_obj,
                                          { "isAtEnd",
                                            "isatend",
                                            "is_at_end" } ).toBool();
}


JobList
PythonQtViewStep::jobs() const
{
    JobList jobs;

    PythonQtObjectPtr jobsCallable = PythonQt::self()->lookupCallable( m_obj, "jobs" );
    if ( jobsCallable.isNull() )
        return jobs;

    PythonQtObjectPtr response = PythonQt::self()->callAndReturnPyObject( jobsCallable );
    if ( response.isNull() )
        return jobs;

    PythonQtObjectPtr listPopCallable = PythonQt::self()->lookupCallable( response, "pop" );
    if ( listPopCallable.isNull() )
        return jobs;

    forever
    {
        PythonQtObjectPtr aJob = PythonQt::self()->callAndReturnPyObject( listPopCallable, { 0 } );
        if ( aJob.isNull() )
            break;

        jobs.append( Calamares::job_ptr( new PythonQtJob( m_cxt, aJob ) ) );
    }

    return jobs;
}


void
PythonQtViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    m_obj.addVariable( "configuration", configurationMap );
}


QWidget*
PythonQtViewStep::createScriptingConsole()
{
    PythonQtScriptingConsole* console = new PythonQtScriptingConsole( nullptr, m_cxt );
    console->setProperty( "classname",
                          m_cxt.getVariable( "_calamares_module_typename" ).toString() );
    return console;
}

}
