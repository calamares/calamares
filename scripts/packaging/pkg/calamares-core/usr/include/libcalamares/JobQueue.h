/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef CALAMARES_JOBQUEUE_H
#define CALAMARES_JOBQUEUE_H

#include "DllMacro.h"
#include "Job.h"

#include <QObject>

namespace Calamares
{
class GlobalStorage;
class JobThread;

class DLLEXPORT JobQueue : public QObject
{
    Q_OBJECT
public:
    explicit JobQueue( QObject* parent = nullptr );
    ~JobQueue() override;

    /** @brief Returns the most-recently-created instance.
     *
     * It is possible for instance() to be @c nullptr, since you must
     * call the constructor explicitly first.
     */
    static JobQueue* instance();
    /* @brief Returns the GlobalStorage object for the instance.
     *
     * It is possible for instanceGlobalStorage() to be @c nullptr,
     * since there might not be an instance to begin with.
     */
    static GlobalStorage* instanceGlobalStorage()
    {
        auto* jq = instance();
        return jq ? jq->globalStorage() : nullptr;
    }

    GlobalStorage* globalStorage() const;

    /** @brief Queues up jobs from a single module source
     *
     * The total weight of the jobs is spread out to fill the weight
     * of the module.
     */
    void enqueue( int moduleWeight, const JobList& jobs );
    /** @brief Starts all the jobs that are enqueued.
     *
     * After this, isRunning() returns @c true until
     * finished() is emitted.
     */
    void start();

    bool isRunning() const { return !m_finished; }

signals:
    /** @brief Report progress of the whole queue, with a status message
     *
     * The @p percent is a value between 0.0 and 1.0 (100%) of the
     * overall queue progress (not of the current job), while
     * @p prettyName is the status message from the job -- often
     * just the name of the job, but some jobs include more information.
     */
    void progress( qreal percent, const QString& prettyName );
    /** @brief Indicate that the queue is empty, after calling start()
     *
     * Emitted when the queue empties. The queue may also emit
     * failed(), if something went wrong, but finished() is always
     * the last one.
     */
    void finished();
    /** @brief A job in the queue failed.
     *
     * Contains the (already-translated) text from the job describing
     * the failure.
     */
    void failed( const QString& message, const QString& details );

    /** @brief Reports the names of jobs in the queue.
     *
     * When jobs are added via enqueue(), or when the queue otherwise
     * changes, the **names** of the jobs are reported. This is
     * primarily for debugging purposes.
     */
    void queueChanged( const QStringList& jobNames );

public slots:
    /** @brief Implementation detail
     *
     * This is a private implementation detail for the job thread,
     * which should not be called by other core.
     */
    void finish();

private:
    static JobQueue* s_instance;

    JobThread* m_thread;
    GlobalStorage* m_storage;
    bool m_finished = true;  ///< Initially, not running
};

}  // namespace Calamares

#endif  // CALAMARES_JOBQUEUE_H
