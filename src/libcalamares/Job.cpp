/* === This file is part of Calamares - <https://github.com/calamares> ===
 * 
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
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
 *
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *   License-Filename: LICENSE
 *
 */

#include "Job.h"

namespace Calamares
{

JobResult::JobResult( JobResult&& rhs )
    : m_message( std::move( rhs.m_message ) )
    , m_details( std::move( rhs.m_details ) )
    , m_number( rhs.m_number )
{
}

JobResult::operator bool() const
{
    return m_number == 0;
}


QString
JobResult::message() const
{
    return m_message;
}


void
JobResult::setMessage( const QString& message )
{
    m_message = message;
}


QString
JobResult::details() const
{
    return m_details;
}


void
JobResult::setDetails( const QString& details )
{
    m_details = details;
}

JobResult
JobResult::ok()
{
    return JobResult( QString(), QString(), NoError );
}


JobResult
JobResult::error( const QString& message, const QString& details )
{
    return JobResult( message, details, GenericError );
}

JobResult
JobResult::internalError( const QString& message, const QString& details, int number )
{
    return JobResult( message, details, number ? number : GenericError );
}

JobResult::JobResult( const QString& message, const QString& details, int number )
    : m_message( message )
    , m_details( details )
    , m_number( number )
{
}


Job::Job( QObject* parent )
    : QObject( parent )
{
}


Job::~Job() {}


qreal
Job::getJobWeight() const
{
    return qreal( 1.0 );
}


QString
Job::prettyDescription() const
{
    return QString();
}


QString
Job::prettyStatusMessage() const
{
    return QString();
}


}  // namespace Calamares
