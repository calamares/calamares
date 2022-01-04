/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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
    explicit PythonQtJobResult( bool ok, const QString& message, const QString& details )
        : QObject( nullptr )
        , Calamares::JobResult( message, details, ok ? 0 : Calamares::JobResult::GenericError )
    {
    }
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
    explicit PythonQtJob( PythonQtObjectPtr cxt, PythonQtObjectPtr pyJob, QObject* parent = nullptr );
    friend class Calamares::PythonQtViewStep;  // only this one can call the ctor

    PythonQtObjectPtr m_cxt;
    PythonQtObjectPtr m_pyJob;
};

#endif  // PYTHONQTJOB_H
