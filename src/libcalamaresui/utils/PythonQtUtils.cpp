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
            return callable.call( args, kwargs );
    }

    // If we haven't found a callable with the given names, we force an error:
    return PythonQt::self()->call( object, candidateNames.first(), args, kwargs );
}

}
