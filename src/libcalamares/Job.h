/* === This file is part of Calamares - <https://github.com/calamares> ===
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

#ifndef CALAMARES_JOB_H
#define CALAMARES_JOB_H

#include "DllMacro.h"

#include <QList>
#include <QObject>
#include <QSharedPointer>

namespace Calamares
{

class DLLEXPORT JobResult
{
public:
    /** @brief Distinguish classes of errors
     *
     * All "ok result" have errorCode 0 (NoError).
     * Errors returned from job execution have values < 0.
     * Errors before job execution, or not returned by the job execution
     * itself, have values > 0.
     */
    enum
    {
        NoError = 0,
        GenericError = -1,
        PythonUncaughtException = 1,
        InvalidConfiguration = 2
    };

    // Can't copy, but you can keep a temporary
    JobResult( const JobResult& rhs ) = delete;
    JobResult( JobResult&& rhs );

    virtual ~JobResult() {}

    /** @brief Is this JobResult a success?
     *
     * Equivalent to errorCode() == 0, might be named  isValid().
     */
    virtual operator bool() const;

    virtual QString message() const;
    virtual void setMessage( const QString& message );

    virtual QString details() const;
    virtual void setDetails( const QString& details );

    int errorCode() const { return m_number; }

    /// @brief an "ok status" result
    static JobResult ok();
    /** @brief an "error" result resulting from the execution of the job
     *
     * The error code is set to GenericError.
     */
    static JobResult error( const QString& message, const QString& details = QString() );
    /** @brief an "internal error" meaning the job itself has a problem (usually for python)
     *
     * Pass in a suitable error code; using 0 (which would normally mean "ok") instead
     * gives you a GenericError code.
     */
    static JobResult internalError( const QString&, const QString& details, int errorCode );

protected:
    explicit JobResult( const QString& message, const QString& details, int errorCode );

private:
    QString m_message;
    QString m_details;
    int m_number;
};

class DLLEXPORT Job : public QObject
{
    Q_OBJECT
public:
    explicit Job( QObject* parent = nullptr );
    virtual ~Job();

    virtual qreal getJobWeight() const;
    virtual QString prettyName() const = 0;
    virtual QString prettyDescription() const;
    virtual QString prettyStatusMessage() const;
    virtual JobResult exec() = 0;

    bool isEmergency() const { return m_emergency; }
    void setEmergency( bool e ) { m_emergency = e; }

signals:
    void progress( qreal percent );

private:
    bool m_emergency = false;
};

using job_ptr = QSharedPointer< Job >;
using JobList = QList< job_ptr >;

}  // namespace Calamares

#endif  // CALAMARES_JOB_H
