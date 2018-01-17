/* === This file is part of Calamares - <https://github.com/calamares> ===
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

#include "JobQueue.h"

#include "Job.h"
#include "GlobalStorage.h"
#include "utils/Logger.h"

#include "CalamaresConfig.h"
#ifdef WITH_PYTHON
#include "PythonHelper.h"
#endif

#include <QThread>

namespace Calamares
{

class JobThread : public QThread
{
    Q_OBJECT
public:
    JobThread( JobQueue* queue )
        : QThread( queue )
        , m_queue( queue )
        , m_jobIndex( 0 )
    {
    }

    void setJobs( const JobList& jobs )
    {
        m_jobs = jobs;
    }

    void run() override
    {
        m_jobIndex = 0;
        for( auto job : m_jobs )
        {
            emitProgress();
            cLog() << "Starting job" << job->prettyName();
            connect( job.data(), &Job::progress, this, &JobThread::emitProgress );
            JobResult result = job->exec();
            if ( !result )
            {
                emitFailed( result.message(), result.details() );
                emitFinished();
                return;
            }
            ++m_jobIndex;
        }
        emitProgress();
        emitFinished();
    }

private:
    JobList m_jobs;
    JobQueue* m_queue;
    int m_jobIndex;

    void emitProgress( qreal jobPercent = 0 )
    {
        // Make sure jobPercent is reasonable, in case a job messed up its
        // percentage computations.
        jobPercent = qBound( qreal( 0 ), jobPercent, qreal( 1 ) );

        int jobCount = m_jobs.size();
        QString message = m_jobIndex < jobCount
            ? m_jobs.at( m_jobIndex )->prettyStatusMessage()
            : tr( "Done" );

        qreal percent = ( m_jobIndex + jobPercent ) / qreal( jobCount );

        QMetaObject::invokeMethod( m_queue, "progress", Qt::QueuedConnection,
            Q_ARG( qreal, percent ),
            Q_ARG( QString, message )
        );
    }

    void emitFailed( const QString& message, const QString& details )
    {
        QMetaObject::invokeMethod( m_queue, "failed", Qt::QueuedConnection,
            Q_ARG( QString, message ),
            Q_ARG( QString, details )
        );
    }

    void emitFinished()
    {
        QMetaObject::invokeMethod( m_queue, "finished", Qt::QueuedConnection );
    }
};


JobQueue* JobQueue::s_instance = nullptr;


JobQueue*
JobQueue::instance()
{
    return s_instance;
}


GlobalStorage*
JobQueue::globalStorage() const
{
    return m_storage;
}


JobQueue::JobQueue( QObject* parent )
    : QObject( parent )
    , m_thread( new JobThread( this ) )
    , m_storage( new GlobalStorage() )
{
    Q_ASSERT( !s_instance );
    s_instance = this;
}


JobQueue::~JobQueue()
{
    delete m_storage;
}


void
JobQueue::start()
{
    Q_ASSERT( !m_thread->isRunning() );
    m_thread->setJobs( m_jobs );
    m_jobs.clear();
    m_thread->start();
}


void
JobQueue::enqueue( const job_ptr& job )
{
    Q_ASSERT( !m_thread->isRunning() );
    m_jobs.append( job );
    emit queueChanged( m_jobs );
}


void
JobQueue::enqueue( const JobList& jobs )
{
    Q_ASSERT( !m_thread->isRunning() );
    m_jobs.append( jobs );
    emit queueChanged( m_jobs );
}

} // namespace Calamares

#include "JobQueue.moc"
