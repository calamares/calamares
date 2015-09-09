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

#ifndef CALAMARES_JOBQUEUE_H
#define CALAMARES_JOBQUEUE_H

#include "DllMacro.h"
#include "Typedefs.h"

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
    void enqueue( const QList< job_ptr >& jobs );
    void start();

signals:
    void queueChanged( const QList< job_ptr >& jobs );
    void progress( qreal percent, const QString& prettyName );
    void finished();
    void failed( const QString& message, const QString& details );

private:
    static JobQueue* s_instance;

    QList< job_ptr > m_jobs;
    JobThread* m_thread;
    GlobalStorage* m_storage;
};

}

#endif // CALAMARES_JOBQUEUE_H
