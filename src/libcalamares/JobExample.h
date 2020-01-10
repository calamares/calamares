/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019, Adriaan de Groot <groot.org>
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
public:
    explicit FailJob( const QString& name, QObject* parent = nullptr )
        : NamedJob( name, parent )
    {
    }

    virtual JobResult exec() override;
};

}  // namespace Calamares

#endif  // CALAMARES_JOB_EXAMPLE_H
