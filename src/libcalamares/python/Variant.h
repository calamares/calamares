/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018-2020, 2024 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef CALAMARES_PYTHONVARIANT_H
#define CALAMARES_PYTHONVARIANT_H

/**
 * @file Support for turning QVariant into Python types, and vice-versa
 *
 * These are helper-functions for converting variants (e.g. values
 * in GlobalStorage, or loaded from YAML) into Python. This is not
 * public API and is used only inside the Python-job-support code.
 */

#include "PythonTypes.h"

#include <QStringList>
#include <QVariant>
#include <QVariantMap>


namespace Calamares
{
namespace Python __attribute__( ( visibility( "hidden" ) ) )
{

Dictionary variantMapToPyDict( const QVariantMap& variantMap );
Object variantToPyObject( const QVariant& variant ); ///< More generic version of variantMapToPyDict

}
}

#endif
