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

#ifndef PYTHONQTCONSOLEVIEWSTEP_H
#define PYTHONQTCONSOLEVIEWSTEP_H


#include "viewpages/ViewStep.h"

#include <PythonQt.h>
#include <gui/PythonQtScriptingConsole.h>


class PythonQtConsoleViewStep : public Calamares::ViewStep
{
    Q_OBJECT
public:
    PythonQtConsoleViewStep( PythonQtObjectPtr cxt,
                             QObject* parent = nullptr );

    virtual QString prettyName() const override { return tr( "PythonQt Console" ); }

    virtual QWidget* widget() override;

    virtual void next() override {}
    virtual void back() override {}

    virtual bool isNextEnabled() const override { return true; }
    virtual bool isBackEnabled() const override { return true; }

    virtual bool isAtBeginning() const override { return true; }
    virtual bool isAtEnd() const override { return true; }

    virtual QList< Calamares::job_ptr > jobs() const override { return QList< Calamares::job_ptr >(); }

private:
    PythonQtObjectPtr m_cxt;
    PythonQtScriptingConsole* m_console;
};

#endif // PYTHONQTCONSOLEVIEWSTEP_H
