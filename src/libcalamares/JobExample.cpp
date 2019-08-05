/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019, Adriaan de Groot <groot.org>
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

#include "JobExample.h"

namespace Calamares
{

QString
NamedJob::prettyName() const
{
    return tr( "Example job (%1)" ).arg( m_name );
}

JobResult
GoodJob::exec()
{
    return JobResult::ok();
}

JobResult
FailJob::exec()
{
    return JobResult::error( tr( "Job failed (%1)" ).arg( m_name ),
                             tr( "Programmed job failure was explicitly requested." ) );
}

}  // namespace Calamares
