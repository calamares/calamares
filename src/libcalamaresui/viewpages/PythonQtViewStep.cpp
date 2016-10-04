/* === This file is part of Calamares - <http://github.com/calamares> ===
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

#include <gui/PythonQtScriptingConsole.h>

#include <QBoxLayout>
#include <QWidget>


PythonQtViewStep::PythonQtViewStep( PythonQtObjectPtr cxt,
                                    QObject* parent )
    : ViewStep( parent )
    , m_widget( new QWidget() )
    , m_cxt( cxt )
{
    QString className = m_cxt.getVariable( "_calamares_module_typename" ).toString();

    PythonQt::self()->evalScript( m_cxt, QString( "_calamares_module = %1()" )
                                            .arg( className ) );
    m_obj = PythonQt::self()->lookupObject( m_cxt, "_calamares_module" );

    Q_ASSERT( !m_obj.isNull() );

    m_widget->setLayout( new QVBoxLayout );
    CalamaresUtils::unmarginLayout( m_widget->layout() );
    m_cxt.addObject( "_calamares_module_basewidget", m_widget );
}


QString
PythonQtViewStep::prettyName() const
{
    return PythonQt::self()->call( m_obj, "prettyName" ).toString();
}


QWidget*
PythonQtViewStep::widget()
{
    m_widget->layout()->deleteLater();
    m_widget->setLayout( new QVBoxLayout );
    CalamaresUtils::unmarginLayout( m_widget->layout() );
    m_cxt.evalScript(
        "_calamares_module_basewidget.layout().addWidget(_calamares_module.widget())" );
    return m_widget;
}


void
PythonQtViewStep::next()
{

}


void
PythonQtViewStep::back()
{

}


bool
PythonQtViewStep::isNextEnabled() const
{
    return PythonQt::self()->call( m_obj, "isNextEnabled" ).toBool();
}


bool
PythonQtViewStep::isBackEnabled() const
{
    return PythonQt::self()->call( m_obj, "isBackEnabled" ).toBool();
}


bool
PythonQtViewStep::isAtBeginning() const
{
    return PythonQt::self()->call( m_obj, "isAtBeginning" ).toBool();
}


bool
PythonQtViewStep::isAtEnd() const
{
    return PythonQt::self()->call( m_obj, "isAtEnd" ).toBool();
}


QList< Calamares::job_ptr >
PythonQtViewStep::jobs() const
{
#warning "Not implemented yet."
    return QList< Calamares::job_ptr >();
}


QWidget*
PythonQtViewStep::createScriptingConsole()
{
    PythonQtScriptingConsole* console = new PythonQtScriptingConsole( nullptr, m_cxt );
    console->setProperty( "classname",
                          m_cxt.getVariable( "_calamares_module_typename" ).toString() );
    return console;
}
