/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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

#include "Job.h"

namespace Calamares
{

JobResult::JobResult( JobResult&& rhs ) :
      m_ok( rhs.m_ok )
    , m_message( std::move( rhs.m_message ) )
    , m_details( std::move( rhs.m_details ) )
{
}

JobResult::operator bool() const
{
    return m_ok;
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
    return JobResult( true, QString(), QString() );
}


JobResult
JobResult::error( const QString& message, const QString& details )
{
    return JobResult( false, message, details );
}


JobResult::JobResult( bool ok, const QString& message, const QString& details )
    : m_ok( ok )
    , m_message( message )
    , m_details( details )
{}


Job::Job( QObject* parent )
    : QObject( parent )
{
}


Job::~Job()
{}


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


} // namespace Calamares
