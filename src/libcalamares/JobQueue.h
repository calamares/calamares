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

    void enqueue( const job_ptr& job );
    void enqueue( const JobList& jobs );
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

    JobList m_jobs;
    JobThread* m_thread;
    GlobalStorage* m_storage;
    bool m_finished = true;  ///< Initially, not running
};

}  // namespace Calamares

#endif  // CALAMARES_JOBQUEUE_H
