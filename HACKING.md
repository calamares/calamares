Hacking on Calamares
====================

Join #calamares on Freenode.

Patches go to [github.com/calamares](https://github.com/calamares/calamares).

Formatting
----------
* Spaces, not tabs.
* Indentation is 4 spaces.
* Lines should be limited to 90 characters.
* Spaces between brackets and argument functions, including for template arguments
* No space before brackets, except for keywords, for example `function( argument )` but
  `if ( condition )`.
* For pointer and reference variable declarations, put a space before the variable name
  and no space between the type and the `*` or `&`.
* `for`, `if`, `else`, `while` and similar statements put the brackets on the next line,
  although brackets are not needed for single statements.
* Function and class definitions have their brackets on separate lines.
* A function implementation's return type is on its own line.
* `CamelCase.{cpp,h}` style file names.

Example:
```
bool
MyClass::myMethod( QStringList list, const QString& name )
{
    if ( list.isEmpty() )
        return false;

    foreach ( const QString& string, list )
        cDebug() << "Current string is " << string;

    switch ( m_enumValue )
    {
    case Something:
        return true;
    case SomethingElse:
        doSomething();
        break;
    }
}
```

Naming
------
* Use CamelCase for everything.
* Local variables should start out with a lowercase letter.
* Class names are captialized
* Prefix class member variables with `m_`, e.g. `m_queue`.
* Prefix static member variables with `s_`, e.g. `s_instance`.
* Functions are named in the Qt style, like Java's, without the 'get' prefix.
    * A getter is `variable()`.
    * If it's a getter for a boolean, prefix with 'is', so `isCondition()`.
    * A setter is `setVariable( arg )`.

Includes
--------
Header includes should be listed in the following order:

* own header,
* Calamares includes,
* includes for Qt-based libraries,
* Qt includes,
* other includes.

They should also be sorted alphabetically for ease of locating them.

Includes in a header file should be kept to the absolute minimum, as to keep compile times short. This can be achieved by using forward declarations instead of includes,
like `class QListView;`.

Example:
```
#include "Settings.h"

#include "CalamaresApplication.h"
#include "utils/CalamaresUtils.h"
#include "utils/Logger.h"
#include "YamlUtils.h"

#include <QDir>
#include <QFile>

#include <yaml-cpp/yaml.h>
```

Use include guards, not `#pragma once`.

C++ tips
--------
All C++11 features are acceptable, and the use of new C++11 features is encouraged when
it makes the code easier to understand and more maintainable.

The use of `nullptr` is preferred over the use of `0` or `NULL`.

For Qt containers it is better to use Qt's own `foreach`. For all other containers, the
range-based `for` syntax introduced with C++11 is preferred ([see this blog post][1]).

When reimplementing a virtual method, always add the `override` keyword.

Try to keep your code const correct. Declare methods const if they don't mutate the 
object, and use const variables. It improves safety, and also makes it easier to 
understand the code.

For the Qt signal-slot system, the new (Qt5) syntax is to be preferred because it allows
the compiler to check for the existence of signals and slots. As an added benefit, the
new syntax can also be used with `tr1::bind` and C++11 lambdas. For more information, see
the [Qt wiki][2].

Example:
```
connect( m_next, &QPushButton::clicked, this, &ViewManager::next );

connect( m_moduleManager, &Calamares::ModuleManager::modulesLoaded, [this]
{
    m_mainwindow->show();
});
```

Debugging
---------
Use `cDebug()` and `cLog()` from `utils/Logger.h`.


[1]: http://blog.qt.digia.com/blog/2011/05/26/cpp0x-in-qt/
[2]: http://qt-project.org/wiki/New_Signal_Slot_Syntax
