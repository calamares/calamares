/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
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
        InvalidConfiguration = 2,
        MissingRequirements = 3,
    };

    // Can't copy, but you can keep a temporary
    JobResult( const JobResult& rhs ) = delete;
    JobResult( JobResult&& rhs );

    virtual ~JobResult() {}

    /** @brief Is this JobResult a success?
     *
     * Equivalent to errorCode() == 0, see succeeded().
     */
    virtual operator bool() const;

    virtual QString message() const;
    virtual void setMessage( const QString& message );

    virtual QString details() const;
    virtual void setDetails( const QString& details );

    int errorCode() const { return m_number; }
    /** @brief Is this JobResult a success?
     *
     * Equivalent to errorCode() == 0.
     */
    bool succeeded() const { return this->operator bool(); }

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
    ~Job() override;

    /** @brief The job's (relative) weight.
     *
     * The default implementation returns 1, which gives all jobs
     * the same weight, so they advance the overall progress the same
     * amount. This is nonsense, since some jobs take much longer than
     * others; it's up to the individual jobs to say something about
     * how much work is (relatively) done.
     *
     * Since jobs are caused by **modules** from the sequence, the
     * overall weight of the module is taken into account: its weight
     * is divided among the jobs based on each jobs relative weight.
     * This can be used in a module that runs a bunch of jobs to indicate
     * which of the jobs is "heavy" and which is not.
     */
    virtual int getJobWeight() const;
    /** @brief The human-readable name of this job
     *
     * This should be a very short statement of what the job does.
     * For status and state information, see prettyStatusMessage().
     */
    virtual QString prettyName() const = 0;
    /** @brief a longer human-readable description of what the job will do
     *
     * This **may** be used by view steps to fill in the summary
     * messages for the summary page; at present, only the *partition*
     * module does so.
     *
     * The default implementation returns an empty string.
     */
    virtual QString prettyDescription() const;
    /** @brief A human-readable status for progress reporting
     *
     * This is called from the JobQueue when progress is made, and should
     * return a not-too-long description of the job's status. This
     * is made visible in the progress bar of the execution view step.
     */
    virtual QString prettyStatusMessage() const;
    virtual JobResult exec() = 0;

    bool isEmergency() const { return m_emergency; }
    void setEmergency( bool e ) { m_emergency = e; }

signals:
    /** @brief Signals that the job has made progress
     *
     * The parameter @p percent should be between 0 (0%) and 1 (100%).
     * Values outside of this range will be clamped.
     */
    void progress( qreal percent );

private:
    bool m_emergency = false;
};

using job_ptr = QSharedPointer< Job >;
using JobList = QList< job_ptr >;

}  // namespace Calamares

#endif  // CALAMARES_JOB_H
