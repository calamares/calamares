/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "PythonQtUtils.h"

namespace CalamaresUtils
{

QVariant
lookupAndCall( PyObject* object,
               const QStringList& candidateNames,
               const QVariantList& args,
               const QVariantMap& kwargs )
{
    Q_ASSERT( object );
    Q_ASSERT( !candidateNames.isEmpty() );

    for ( const QString& name : candidateNames )
    {
        PythonQtObjectPtr callable = PythonQt::self()->lookupCallable( object, name );
        if ( callable )
        {
            return callable.call( args, kwargs );
        }
    }

    // If we haven't found a callable with the given names, we force an error:
    return PythonQt::self()->call( object, candidateNames.first(), args, kwargs );
}

}  // namespace CalamaresUtils
