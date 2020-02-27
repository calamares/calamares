/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2017-2020, Adriaan de Groot <groot@kde.org>
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

/* This file isn't public API, but is used to express the API that
 * the tests for ContextualProcess can work with.
 */
#ifndef CONTEXTUALPROCESSJOB_BINDING_H
#define CONTEXTUALPROCESSJOB_BINDING_H

#include "Job.h"

#include <QList>
#include <QPair>
#include <QString>

namespace CalamaresUtils
{
class CommandList;
}
namespace Calamares
{
class GlobalStorage;
}

struct ValueCheck : public QPair< QString, CalamaresUtils::CommandList* >
{
    ValueCheck( const QString& value, CalamaresUtils::CommandList* commands )
        : QPair< QString, CalamaresUtils::CommandList* >( value, commands )
    {
    }

    // ~ValueCheck()
    //
    // There is no destructor.
    //
    // We don't own the commandlist, the binding holding this valuecheck
    // does, so don't delete. This is closely tied to (temporaries created
    // by) pass-by-value in QList::append().

    QString value() const { return first; }
    CalamaresUtils::CommandList* commands() const { return second; }
};

class ContextualProcessBinding
{
public:
    ContextualProcessBinding( const QString& varname )
        : m_variable( varname )
    {
    }

    ~ContextualProcessBinding();

    QString variable() const { return m_variable; }
    int count() const { return m_checks.count(); }

    /**
     * @brief add commands to be executed when @p value is matched.
     *
     * Ownership of the CommandList passes to this binding.
     */
    void append( const QString& value, CalamaresUtils::CommandList* commands );

    ///@brief The bound variable has @p value , run the associated commands.
    Calamares::JobResult run( const QString& value ) const;

    /** @brief Tries to obtain this binding's value from GS
     *
     * Stores the value in @p value and returns true if a value
     * was found (e.g. @p storage contains the variable this binding
     * is for) and false otherwise.
     */
    bool fetch( Calamares::GlobalStorage* storage, QString& value ) const;

private:
    QString m_variable;
    QList< ValueCheck > m_checks;
    CalamaresUtils::CommandList* m_wildcard = nullptr;
};


#endif
