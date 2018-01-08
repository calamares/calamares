/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2016, Teo Mrnjavac <teo@kde.org>
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

#ifndef PYTHONQTJOB_H
#define PYTHONQTJOB_H

#include "Job.h"

#include <PythonQt.h>

namespace Calamares
{
class PythonQtViewStep;
}

class PythonQtJobResult : public QObject, public Calamares::JobResult
{
    Q_OBJECT
public:
    explicit PythonQtJobResult( bool ok,
                                const QString& message,
                                const QString& details )
        : QObject( nullptr )
        , Calamares::JobResult( ok, message, details )
    {}
};


class PythonQtJob : public Calamares::Job
{
    Q_OBJECT
public:
    virtual ~PythonQtJob() {}

    QString prettyName() const override;
    QString prettyDescription() const override;
    QString prettyStatusMessage() const override;
    Calamares::JobResult exec() override;

private:
    explicit PythonQtJob( PythonQtObjectPtr cxt,
                          PythonQtObjectPtr pyJob,
                          QObject* parent = nullptr );
    friend class Calamares::PythonQtViewStep; // only this one can call the ctor

    PythonQtObjectPtr m_cxt;
    PythonQtObjectPtr m_pyJob;
};

#endif // PYTHONQTJOB_H
