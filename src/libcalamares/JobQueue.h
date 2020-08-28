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
    virtual ~JobQueue();

    static JobQueue* instance();

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

private:
    void finish();

    static JobQueue* s_instance;

    JobThread* m_thread;
    GlobalStorage* m_storage;
    bool m_finished = true;  ///< Initially, not running
};

}  // namespace Calamares

#endif  // CALAMARES_JOBQUEUE_H
