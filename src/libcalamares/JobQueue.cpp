/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "JobQueue.h"

#include "CalamaresConfig.h"
#include "GlobalStorage.h"
#include "Job.h"
#include "compat/Mutex.h"
#include "utils/Logger.h"

#include <QApplication>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusPendingCall>
#include <QDBusPendingReply>
#include <QMutex>
#include <QThread>

#include <memory>

namespace
{
// This power-management code is largely cribbed from KDE Discover,
// https://invent.kde.org/plasma/discover/-/blob/master/discover/PowerManagementInterface.cpp
//
// Upstream license text says:
//
//   SPDX-FileCopyrightText: 2019 (c) Matthieu Gallien <matthieu_gallien@yahoo.fr>
//   SPDX-License-Identifier: LGPL-3.0-or-later


/** @brief Class to manage sleep / suspend on inactivity
 *
 * Create an object of this class on the heap. Call inhibitSleep()
 * to (try to) stop system sleep / suspend. Call uninhibitSleep()
 * when the object is no longer needed. The object self-deletes
 * after uninhibitSleep() completes.
 */
class PowerManagementInterface : public QObject
{
    Q_OBJECT
public:
    PowerManagementInterface( QObject* parent = nullptr );
    ~PowerManagementInterface() override;

public Q_SLOTS:
    void inhibitSleep();
    void uninhibitSleep();

private Q_SLOTS:
    void hostSleepInhibitChanged();
    void inhibitDBusCallFinished( QDBusPendingCallWatcher* aWatcher );
    void uninhibitDBusCallFinished( QDBusPendingCallWatcher* aWatcher );

private:
    uint m_inhibitSleepCookie = 0;
    bool m_inhibitedSleep = false;
};

PowerManagementInterface::PowerManagementInterface( QObject* parent )
    : QObject( parent )
{
    auto sessionBus = QDBusConnection::sessionBus();

    sessionBus.connect( QStringLiteral( "org.freedesktop.PowerManagement.Inhibit" ),
                        QStringLiteral( "/org/freedesktop/PowerManagement/Inhibit" ),
                        QStringLiteral( "org.freedesktop.PowerManagement.Inhibit" ),
                        QStringLiteral( "HasInhibitChanged" ),
                        this,
                        SLOT( hostSleepInhibitChanged() ) );
}

PowerManagementInterface::~PowerManagementInterface() = default;

void
PowerManagementInterface::hostSleepInhibitChanged()
{
    // We don't actually care
}

void
PowerManagementInterface::inhibitDBusCallFinished( QDBusPendingCallWatcher* aWatcher )
{
    QDBusPendingReply< uint > reply = *aWatcher;
    if ( reply.isError() )
    {
        cError() << "Could not inhibit sleep:" << reply.error();
        // m_inhibitedSleep = false; // unchanged
    }
    else
    {
        m_inhibitSleepCookie = reply.argumentAt< 0 >();
        m_inhibitedSleep = true;
        cDebug() << "Sleep inhibited, cookie" << m_inhibitSleepCookie;
    }
    aWatcher->deleteLater();
}

void
PowerManagementInterface::uninhibitDBusCallFinished( QDBusPendingCallWatcher* aWatcher )
{
    QDBusPendingReply<> reply = *aWatcher;
    if ( reply.isError() )
    {
        cError() << "Could not uninhibit sleep:" << reply.error();
    }
    else
    {
        m_inhibitedSleep = false;
        m_inhibitSleepCookie = 0;
        cDebug() << "Sleep uninhibited.";
    }
    aWatcher->deleteLater();
    this->deleteLater();
}

void
PowerManagementInterface::inhibitSleep()
{
    if ( m_inhibitedSleep )
    {
        cDebug() << "Sleep is already inhibited.";
        return;
    }

    auto sessionBus = QDBusConnection::sessionBus();
    auto inhibitCall = QDBusMessage::createMethodCall( QStringLiteral( "org.freedesktop.PowerManagement.Inhibit" ),
                                                       QStringLiteral( "/org/freedesktop/PowerManagement/Inhibit" ),
                                                       QStringLiteral( "org.freedesktop.PowerManagement.Inhibit" ),
                                                       QStringLiteral( "Inhibit" ) );
    inhibitCall.setArguments(
        { { tr( "Calamares" ) }, { tr( "Installation in progress", "@status" ) } } );

    auto asyncReply = sessionBus.asyncCall( inhibitCall );
    auto* replyWatcher = new QDBusPendingCallWatcher( asyncReply, this );
    QObject::connect(
        replyWatcher, &QDBusPendingCallWatcher::finished, this, &PowerManagementInterface::inhibitDBusCallFinished );
}

void
PowerManagementInterface::uninhibitSleep()
{
    if ( !m_inhibitedSleep )
    {
        cDebug() << "Sleep was never inhibited.";
        this->deleteLater();
        return;
    }

    auto sessionBus = QDBusConnection::sessionBus();
    auto uninhibitCall = QDBusMessage::createMethodCall( QStringLiteral( "org.freedesktop.PowerManagement.Inhibit" ),
                                                         QStringLiteral( "/org/freedesktop/PowerManagement/Inhibit" ),
                                                         QStringLiteral( "org.freedesktop.PowerManagement.Inhibit" ),
                                                         QStringLiteral( "UnInhibit" ) );
    uninhibitCall.setArguments( { { m_inhibitSleepCookie } } );

    auto asyncReply = sessionBus.asyncCall( uninhibitCall );
    auto replyWatcher = new QDBusPendingCallWatcher( asyncReply, this );
    QObject::connect(
        replyWatcher, &QDBusPendingCallWatcher::finished, this, &PowerManagementInterface::uninhibitDBusCallFinished );
}

}  // namespace

namespace Calamares
{
SleepInhibitor::SleepInhibitor()
{
    // Create a PowerManagementInterface object with intentionally no parent
    // so it is not destroyed along with this. Instead, when this
    // is destroyed, **start** the uninhibit-sleep call which will (later)
    // destroy the PowerManagementInterface object.
    auto* p = new PowerManagementInterface( nullptr );
    p->inhibitSleep();
    connect( this, &QObject::destroyed, p, &PowerManagementInterface::uninhibitSleep );
}

SleepInhibitor::~SleepInhibitor() = default;

struct WeightedJob
{
    /** @brief Cumulative weight **before** this job starts
     *
     * This is calculated as jobs come in.
     */
    qreal cumulative = 0.0;
    /** @brief Weight of the job within the module's jobs
     *
     * When a list of jobs is added from a particular module,
     * the jobs are weighted relative to that module's overall weight
     * **and** the other jobs in the list, so that each job
     * gets its share:
     *      ( job-weight / total-job-weight ) * module-weight
     */
    qreal weight = 0.0;

    job_ptr job;
};
using WeightedJobList = QList< WeightedJob >;

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

    ~JobThread() override;

    void finalize()
    {
        Q_ASSERT( m_runningJobs->isEmpty() );
        Calamares::MutexLocker qlock( &m_enqueMutex );
        Calamares::MutexLocker rlock( &m_runMutex );
        std::swap( m_runningJobs, m_queuedJobs );
        m_overallQueueWeight
            = m_runningJobs->isEmpty() ? 0.0 : ( m_runningJobs->last().cumulative + m_runningJobs->last().weight );
        if ( m_overallQueueWeight < 1 )
        {
            m_overallQueueWeight = 1.0;
        }

        cDebug() << "There are" << m_runningJobs->count() << "jobs, total weight" << m_overallQueueWeight;
        int c = 0;
        for ( const auto& j : *m_runningJobs )
        {
            cDebug() << Logger::SubEntry << "Job" << ( c + 1 ) << j.job->prettyName() << "+wt" << j.weight << "tot.wt"
                     << ( j.cumulative + j.weight );
            c++;
        }
    }

    void enqueue( int moduleWeight, const JobList& jobs )
    {
        Calamares::MutexLocker qlock( &m_enqueMutex );

        qreal cumulative
            = m_queuedJobs->isEmpty() ? 0.0 : ( m_queuedJobs->last().cumulative + m_queuedJobs->last().weight );

        qreal totalJobWeight
            = std::accumulate( jobs.cbegin(),
                               jobs.cend(),
                               qreal( 0.0 ),
                               []( qreal total, const job_ptr& j ) { return total + j->getJobWeight(); } );
        if ( totalJobWeight < 1 )
        {
            totalJobWeight = 1.0;
        }

        for ( const auto& j : jobs )
        {
            qreal jobContribution = ( j->getJobWeight() / totalJobWeight ) * moduleWeight;
            m_queuedJobs->append( WeightedJob { cumulative, jobContribution, j } );
            cumulative += jobContribution;
        }
    }

    void run() override
    {
        Calamares::MutexLocker rlock( &m_runMutex );
        bool failureEncountered = false;
        QString message;  ///< Filled in with errors
        QString details;

        Logger::Once o;
        m_jobIndex = 0;
        for ( const auto& jobitem : *m_runningJobs )
        {
            if ( failureEncountered && !jobitem.job->isEmergency() )
            {
                cDebug() << o << "Skipping non-emergency job" << jobitem.job->prettyName();
            }
            else
            {
                cDebug() << o << "Starting" << ( failureEncountered ? "EMERGENCY JOB" : "job" )
                         << jobitem.job->prettyName() << '(' << ( m_jobIndex + 1 ) << '/' << m_runningJobs->count()
                         << ')';
                o.refresh();  // So next time it shows the function header again
                emitProgress( 0.0 );  // 0% for *this job*
                connect( jobitem.job.data(), &Job::progress, this, &JobThread::emitProgress );
                auto result = jobitem.job->exec();
                if ( !failureEncountered && !result )
                {
                    // so this is the first failure
                    failureEncountered = true;
                    message = result.message();
                    details = result.details();
                }
                QThread::msleep( 16 );  // Very brief rest before reporting the job as complete
                emitProgress( 1.0 );  // 100% for *this job*
            }
            m_jobIndex++;
        }
        if ( failureEncountered )
        {
            QMetaObject::invokeMethod(
                m_queue, "failed", Qt::QueuedConnection, Q_ARG( QString, message ), Q_ARG( QString, details ) );
        }
        else
        {
            emitProgress( 1.0 );
        }
        m_runningJobs->clear();
        QMetaObject::invokeMethod( m_queue, "finish", Qt::QueuedConnection );
    }

    /** @brief The names of the queued (not running!) jobs.
     */
    QStringList queuedJobs() const
    {
        Calamares::MutexLocker qlock( &m_enqueMutex );
        QStringList l;
        l.reserve( m_queuedJobs->count() );
        for ( const auto& j : *m_queuedJobs )
        {
            l << j.job->prettyName();
        }
        return l;
    }

private:
    /* This is called **only** from run(), while m_runMutex is
     * already locked, so we can use the m_runningJobs member safely.
     */
    void emitProgress( qreal percentage ) const
    {
        percentage = qBound( 0.0, percentage, 1.0 );

        QString message;
        qreal progress = 0.0;
        if ( m_jobIndex < m_runningJobs->count() )
        {
            const auto& jobitem = m_runningJobs->at( m_jobIndex );
            progress = ( jobitem.cumulative + jobitem.weight * percentage ) / m_overallQueueWeight;
            message = jobitem.job->prettyStatusMessage();
            // In progress reports at the start of a job (e.g. when the queue
            // starts the job, or if the job itself reports 0.0) be more
            // accepting in what gets reported: jobs with no status fall
            // back to description and name, whichever is non-empty.
            //
            // Later calls (e.g. when percentage > 0) use the status unchanged.
            // It may be empty, but the ExecutionViewStep knows about empty
            // status messages and does not update the text in that case.
            //
            // This means that a Job can implement just prettyName() and get
            // a reasonable "status" message which will update only once.
            if ( percentage == 0.0 && message.isEmpty() )
            {
                message = jobitem.job->prettyDescription();
                if ( message.isEmpty() )
                {
                    message = jobitem.job->prettyName();
                }
            }
        }
        else
        {
            progress = 1.0;
            message = tr( "Done" );
        }
        QMetaObject::invokeMethod(
            m_queue, "progress", Qt::QueuedConnection, Q_ARG( qreal, progress ), Q_ARG( QString, message ) );
    }

    mutable QMutex m_runMutex;
    mutable QMutex m_enqueMutex;

    std::unique_ptr< WeightedJobList > m_runningJobs = std::make_unique< WeightedJobList >();
    std::unique_ptr< WeightedJobList > m_queuedJobs = std::make_unique< WeightedJobList >();

    JobQueue* m_queue;
    int m_jobIndex = 0;  ///< Index into m_runningJobs
    qreal m_overallQueueWeight = 0.0;  ///< cumulation when **all** the jobs are done
};

JobThread::~JobThread() {}


JobQueue* JobQueue::s_instance = nullptr;

JobQueue*
JobQueue::instance()
{
    if ( !s_instance )
    {
        cWarning() << "Getting nullptr JobQueue instance.";
    }
    return s_instance;
}


JobQueue::JobQueue( QObject* parent )
    : QObject( parent )
    , m_thread( new JobThread( this ) )
    , m_storage( new GlobalStorage( this ) )
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
    s_instance = nullptr;
}


void
JobQueue::start()
{
    Q_ASSERT( !m_thread->isRunning() );
    m_thread->finalize();
    m_finished = false;
    m_thread->start();

    auto* inhibitor = new PowerManagementInterface( this );
    inhibitor->inhibitSleep();
    connect( this, &JobQueue::finished, inhibitor, &PowerManagementInterface::uninhibitSleep );
}


void
JobQueue::enqueue( int moduleWeight, const JobList& jobs )
{
    Q_ASSERT( !m_thread->isRunning() );
    m_thread->enqueue( moduleWeight, jobs );
    emit queueChanged( m_thread->queuedJobs() );
}

void
JobQueue::finish()
{
    m_finished = true;
    emit finished();
    emit queueChanged( m_thread->queuedJobs() );
}

GlobalStorage*
JobQueue::globalStorage() const
{
    return m_storage;
}

}  // namespace Calamares

#include "utils/moc-warnings.h"

#include "JobQueue.moc"
