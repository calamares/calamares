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
