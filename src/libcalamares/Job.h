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

#ifndef CALAMARES_JOB_H
#define CALAMARES_JOB_H

#include "DllMacro.h"
#include "Typedefs.h"

#include <QObject>

namespace Calamares {

class DLLEXPORT Job : public QObject
{
    Q_OBJECT
public:
    enum State
    {
        Pending = 0,
        Running,
        Finished
    };

    explicit Job( QObject* parent = nullptr );
    virtual ~Job();

    virtual QString prettyName() = 0;
    virtual void exec() = 0;
signals:
    void running( const Calamares::job_ptr& );
    void finished( const Calamares::job_ptr& );
};

} // namespace Calamares

#endif // CALAMARES_JOB_H
