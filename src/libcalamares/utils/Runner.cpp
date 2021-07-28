/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#include "Runner.h"

namespace
{
}

namespace Calamares
{
namespace Utils
{

struct Runner::Private
{
    QStringList m_command;
};

Runner::Runner() {}
Runner::Runner( const QStringList& command )
    : d( std::make_unique< Private >() )
{
    d->m_command = command;
}

Runner::~Runner() {}


}  // namespace Utils
}  // namespace Calamares
