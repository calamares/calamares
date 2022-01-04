/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef CALAMARES_JOB_EXAMPLE_H
#define CALAMARES_JOB_EXAMPLE_H

#include "Job.h"

namespace Calamares
{

/** @brief A Job with a name
 *
 * This includes a default implementation of prettyName(),
 * but is only used as a base for FailJob and GoodJob,
 * which are support / bogus classes.
 */
class DLLEXPORT NamedJob : public Job
{
    Q_OBJECT
public:
    explicit NamedJob( const QString& name, QObject* parent = nullptr )
        : Job( parent )
        , m_name( name )
    {
    }

    virtual QString prettyName() const override;

protected:
    const QString m_name;
};

/// @brief Job does nothing, always succeeds
class DLLEXPORT GoodJob : public NamedJob
{
    Q_OBJECT
public:
    explicit GoodJob( const QString& name, QObject* parent = nullptr )
        : NamedJob( name, parent )
    {
    }

    virtual JobResult exec() override;
};


/// @brief Job does nothing, always fails
class DLLEXPORT FailJob : public NamedJob
{
    Q_OBJECT
public:
    explicit FailJob( const QString& name, QObject* parent = nullptr )
        : NamedJob( name, parent )
    {
    }

    virtual JobResult exec() override;
};

}  // namespace Calamares

#endif  // CALAMARES_JOB_EXAMPLE_H
