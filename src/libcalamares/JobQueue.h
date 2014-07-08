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

#ifndef CALAMARES_JOBQUEUE_H
#define CALAMARES_JOBQUEUE_H

#include "DllMacro.h"
#include "Typedefs.h"

#include <QObject>

namespace Calamares
{

class JobThread;

class DLLEXPORT JobQueue : public QObject
{
    Q_OBJECT
public:
    explicit JobQueue( QObject* parent = nullptr );

    static JobQueue* instance();

    void enqueue( const Calamares::job_ptr& job );
    void enqueue( const QList< Calamares::job_ptr >& jobs );
    void start();

signals:
    void progress( int current, int total, const QString& prettyName );

private:
    static JobQueue* s_instance;

    QList< Calamares::job_ptr > m_jobs;
    JobThread* m_thread;
};

}

#endif // CALAMARES_JOBQUEUE_H
