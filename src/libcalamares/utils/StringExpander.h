/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2022 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#ifndef UTILS_STRINGEXPANDER_H
#define UTILS_STRINGEXPANDER_H

#include "DllMacro.h"

#include <KMacroExpander>

#include <QString>
#include <QStringList>

#include <memory>

namespace Calamares
{
namespace String
{

/** @brief Expand variables in a string against a dictionary.
 *
 * This class provides a convenience API for building up a dictionary
 * and using it to expand strings. Use the `expand()` method to
 * do standard word-based expansion with `$` as macro-symbol.
 *
 * Unlike straight-up `KMacroExpander::expandMacros()`, this
 * provides an API to find out which variables were missing
 * from the dictionary during expansion. Use `hasErrors()` and
 * `errorNames()` to find out which variables those were.
 *
 * Call `clearErrors()` to reset the stored errors. Calling
 * `expand()` implicitly clears the errors before starting
 * a new expansion, as well.
 */
class DictionaryExpander : public KWordMacroExpander
{
public:
    DictionaryExpander();
    DictionaryExpander( DictionaryExpander&& );
    virtual ~DictionaryExpander() override;

    void insert( const QString& key, const QString& value );

    void clearErrors();
    bool hasErrors() const;
    QStringList errorNames() const;

    QString expand( QString s );

protected:
    virtual bool expandMacro( const QString& str, QStringList& ret ) override;

private:
    struct Private;
    std::unique_ptr< Private > d;
};

}  // namespace String
}  // namespace Calamares

#endif
