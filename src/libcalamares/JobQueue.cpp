/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2018, Adriaan de Groot <groot@kde.org>
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
public:
    JobThread( JobQueue* queue )
        : QThread( queue )
        , m_queue( queue )
        , m_jobIndex( 0 )
    {
    }

    virtual ~JobThread() override;

    void setJobs( const JobList& jobs )
    {
        m_jobs = jobs;
    }

    void run() override
    {
        bool anyFailed = false;
        QString message;
        QString details;

        m_jobIndex = 0;
        for( auto job : m_jobs )
        {
            if ( anyFailed && !job->isEmergency() )
            {
                cDebug() << "Skipping non-emergency job" << job->prettyName();
                continue;
            }

            emitProgress();
            cDebug() << "Starting" << ( anyFailed ? "EMERGENCY JOB" : "job" ) << job->prettyName();
            connect( job.data(), &Job::progress, this, &JobThread::emitProgress );
            JobResult result = job->exec();
            if ( !anyFailed && !result )
            {
                anyFailed = true;
                message = result.message();
                details = result.details();
            }
            if ( !anyFailed )
                ++m_jobIndex;
        }
        if ( anyFailed )
            emitFailed( message, details );
        else
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

JobThread::~JobThread()
{
}


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
    if ( m_thread->isRunning() )
    {
        m_thread->terminate();
        if ( !m_thread->wait(300) )
            cError() << "Could not terminate job thread (expect a crash now).";
        delete m_thread;
    }

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
