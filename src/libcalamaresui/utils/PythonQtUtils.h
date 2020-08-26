/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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

}  // namespace CalamaresUtils

#endif  // PYTHONQTUTILS_H
