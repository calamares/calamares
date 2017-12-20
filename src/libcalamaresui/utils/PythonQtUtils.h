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

#ifndef PYTHONQTUTILS_H
#define PYTHONQTUTILS_H

#include <PythonQt.h>

#include <QVariant>


namespace CalamaresUtils
{
//NOTE: when running this, it is assumed that Python is initialized and
//      PythonQt::self() is valid.
QVariant lookupAndCall( PyObject* object,
                        const QStringList& candidateNames,
                        const QVariantList& args = QVariantList(),
                        const QVariantMap& kwargs = QVariantMap() );

} //ns

#endif // PYTHONQTUTILS_H
