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

#include "CalamaresConfig.h"
#include "GlobalStorage.h"
#include "Job.h"
#include "utils/Logger.h"

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

    void setJobs( JobList&& jobs )
    {
        m_jobs = jobs;

        qreal totalJobsWeight = 0.0;
        for ( auto job : m_jobs )
        {
            totalJobsWeight += job->getJobWeight();
        }
        for ( auto job : m_jobs )
        {
            qreal jobWeight = qreal( job->getJobWeight() / totalJobsWeight );
            m_jobWeights.append( jobWeight );
        }
    }

    void run() override
    {
        bool anyFailed = false;
        QString message;
        QString details;

        m_jobIndex = 0;
        for ( auto job : m_jobs )
        {
            if ( anyFailed && !job->isEmergency() )
            {
                cDebug() << "Skipping non-emergency job" << job->prettyName();
                ++m_jobIndex;
                continue;
            }

            emitProgress();
            cDebug() << "Starting" << ( anyFailed ? "EMERGENCY JOB" : "job" ) << job->prettyName() << " (there are"
                     << m_jobs.count() << " left)";
            connect( job.data(), &Job::progress, this, &JobThread::emitProgress );
            JobResult result = job->exec();
            if ( !anyFailed && !result )
            {
                anyFailed = true;
                message = result.message();
                details = result.details();
            }
            emitProgress( 1.0 );
            ++m_jobIndex;
        }
        if ( anyFailed )
        {
            emitFailed( message, details );
        }
        else
        {
            emitProgress();
        }
        emitFinished();
    }

private:
    JobList m_jobs;
    QList< qreal > m_jobWeights;
    JobQueue* m_queue;
    int m_jobIndex;

    void emitProgress( qreal jobPercent = 0 )
    {
        // Make sure jobPercent is reasonable, in case a job messed up its
        // percentage computations.
        jobPercent = qBound( qreal( 0 ), jobPercent, qreal( 1 ) );

        int jobCount = m_jobs.size();
        QString message = m_jobIndex < jobCount ? m_jobs.at( m_jobIndex )->prettyStatusMessage() : tr( "Done" );

        qreal percent = 1.0;  // Pretend we're done, since the if will reset it
        if ( m_jobIndex < jobCount )
        {
            qreal cumulativeProgress = 0.0;
            for ( auto jobWeight : m_jobWeights.mid( 0, m_jobIndex ) )
            {
                cumulativeProgress += jobWeight;
            }
            percent = cumulativeProgress + ( ( m_jobWeights.at( m_jobIndex ) ) * jobPercent );

            Logger::CDebug( Logger::LOGVERBOSE )
                << "[JOBQUEUE]: Progress for Job[" << m_jobIndex << "]: " << ( jobPercent * 100 ) << "% completed";
            Logger::CDebug( Logger::LOGVERBOSE )
                << "[JOBQUEUE]: Progress Overall: " << ( cumulativeProgress * 100 ) << "% (accumulated) + "
                << ( ( ( m_jobWeights.at( m_jobIndex ) ) * jobPercent ) * 100 )
                << "% (this job) = " << ( percent * 100 ) << "% (total)";
        }
        QMetaObject::invokeMethod(
            m_queue, "progress", Qt::QueuedConnection, Q_ARG( qreal, percent ), Q_ARG( QString, message ) );
    }

    void emitFailed( const QString& message, const QString& details )
    {
        QMetaObject::invokeMethod(
            m_queue, "failed", Qt::QueuedConnection, Q_ARG( QString, message ), Q_ARG( QString, details ) );
    }

    void emitFinished() { QMetaObject::invokeMethod( m_queue, "finish", Qt::QueuedConnection ); }
};

JobThread::~JobThread() {}


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
        if ( !m_thread->wait( 300 ) )
        {
            cError() << "Could not terminate job thread (expect a crash now).";
        }
        delete m_thread;
    }

    delete m_storage;
}


void
JobQueue::start()
{
    Q_ASSERT( !m_thread->isRunning() );
    m_thread->setJobs( std::move( m_jobs ) );
    m_jobs.clear();
    m_finished = false;
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

void
JobQueue::finish()
{
    m_finished = true;
    emit finished();
}

}  // namespace Calamares
