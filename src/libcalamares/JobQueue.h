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
    virtual ~JobQueue();

    static JobQueue* instance();

    GlobalStorage* globalStorage() const;

    /** @brief Queues up jobs from a single module source
     *
     * The total weight of the jobs is spread out to fill the weight
     * of the module.
     */
    void enqueue( int moduleWeight, const JobList& jobs );
    void start();

    bool isRunning() const { return !m_finished; }

public slots:
    void finish();

signals:
    void queueChanged( const JobList& jobs );
    void progress( qreal percent, const QString& prettyName );
    void finished();
    void failed( const QString& message, const QString& details );

private:
    static JobQueue* s_instance;

    JobThread* m_thread;
    GlobalStorage* m_storage;
    bool m_finished = true;  ///< Initially, not running
};

}  // namespace Calamares

#endif  // CALAMARES_JOBQUEUE_H
