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
    RunLocation m_location = RunLocation::RunInHost;
};

Runner::Runner() {}
Runner::Runner( const QStringList& command )
    : d( std::make_unique< Private >() )
{
    d->m_command = command;
}

Runner::~Runner() {}

Runner&
Runner::setCommand( const QStringList& command )
{
    d->m_command = command;
    return *this;
}

}  // namespace Utils
}  // namespace Calamares
