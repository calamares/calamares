/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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

#include "JobQueue.h"

#include "Job.h"

#include <QThread>

namespace Calamares
{

class JobThread : public QThread
{
public:
    JobThread( JobQueue* queue )
    : QThread( queue )
    , m_queue( queue )
    {
    }

    void setJobs( const QList< Calamares::job_ptr >& jobs )
    {
        m_jobs = jobs;
    }

    void run() override
    {
        int total = m_jobs.size();
        int current = 0;
        for( auto job : m_jobs )
        {
            emitProgress( current, total, job->prettyName() );
            job->exec();
            ++current;
        }
        emitProgress( total, total, QString() );
    }

private:
    QList< Calamares::job_ptr > m_jobs;
    JobQueue* m_queue;

    void emitProgress( int current, int total, const QString& prettyName )
    {
        QMetaObject::invokeMethod( m_queue, "progress", Qt::QueuedConnection,
            Q_ARG( int, current ),
            Q_ARG( int, total ),
            Q_ARG( QString, prettyName )
        );
    }
};


JobQueue* JobQueue::s_instance = nullptr;


JobQueue*
JobQueue::instance()
{
    return s_instance;
}


JobQueue::JobQueue( QObject* parent )
    : QObject( parent )
    , m_thread( new JobThread( this ) )
{
    Q_ASSERT( !s_instance );
    s_instance = this;
}


void
JobQueue::start()
{
    Q_ASSERT( !m_thread->isRunning() );
    m_thread->setJobs( m_jobs );
    m_thread->start();
}


void
JobQueue::enqueue( const Calamares::job_ptr& job )
{
    Q_ASSERT( !m_thread->isRunning() );
    m_jobs.append( job );
}


void
JobQueue::enqueue( const QList< job_ptr >& jobs )
{
    Q_ASSERT( !m_thread->isRunning() );
    m_jobs.append( jobs );
}

} // namespace Calamares
