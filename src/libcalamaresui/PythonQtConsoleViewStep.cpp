#include "PythonQtConsoleViewStep.h"

using namespace Calamares;

PythonQtConsoleViewStep::PythonQtConsoleViewStep( PythonQtObjectPtr cxt,
                                                  QObject* parent )
    : ViewStep( parent )
{
    m_cxt = cxt;
    qDebug() << "SMO" << PythonQtConsoleViewStep::staticMetaObject.className();
    PythonQt::self()->registerClass( &PythonQtConsoleViewStep::staticMetaObject, "Calamares" );
    m_console = new PythonQtScriptingConsole( nullptr, m_cxt );
}

QWidget*
PythonQtConsoleViewStep::widget()
{
    return m_console;
}


