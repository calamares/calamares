/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2017-2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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
