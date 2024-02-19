/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018-2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */
#ifndef MODULESYSTEM_INSTANCEKEY_H
#define MODULESYSTEM_INSTANCEKEY_H

#include "DllMacro.h"

#include <QDebug>
#include <QList>
#include <QString>

#include <tuple>
#include <utility>

namespace Calamares
{
namespace ModuleSystem
{

/** @brief A module instance's key (`module@id`)
 *
 * A module instance is identified by both the module's name
 * (a Calamares module, e.g. `users`) and an instance id.
 * Usually, the instance id is the same as the module name
 * and the whole module instance key is `users@users`, but
 * it is possible to use the same module more than once
 * and then you distinguish those module instances by their
 * secondary id (e.g. `users@one`).
 *
 * This is supported by the *instances* configuration entry
 * in `settings.conf`.
 */
class DLLEXPORT InstanceKey
{
public:
    /// @brief Create an instance key from explicit module and id.
    InstanceKey( const QString& module, const QString& id )
        : first( module )
        , second( id )
    {
        if ( second.isEmpty() )
        {
            second = first;
        }
        validate();
    }

    /// @brief Create unusual, invalid instance key
    InstanceKey() = default;

    /// @brief A valid module has both name and id
    bool isValid() const { return !first.isEmpty() && !second.isEmpty(); }

    /// @brief A custom module has a non-default id
    bool isCustom() const { return first != second; }

    QString module() const { return first; }
    QString id() const { return second; }

    /// @brief Create instance key from stringified version
    static InstanceKey fromString( const QString& s );

    QString toString() const
    {
        if ( isValid() )
        {
            return first + '@' + second;
        }
        return QString();
    }

    friend bool operator==( const InstanceKey& lhs, const InstanceKey& rhs ) noexcept
    {
        return std::tie( lhs.first, lhs.second ) == std::tie( rhs.first, rhs.second );
    }

    friend bool operator<( const InstanceKey& lhs, const InstanceKey& rhs ) noexcept
    {
        return std::tie( lhs.first, lhs.second ) < std::tie( rhs.first, rhs.second );
    }

private:
    /** @brief Check validity and reset module and id if needed. */
    void validate()
    {
        if ( first.contains( '@' ) || second.contains( '@' ) )
        {
            first = QString();
            second = QString();
        }
    }

    QString first;
    QString second;
};

using InstanceKeyList = QList< InstanceKey >;

DLLEXPORT QDebug& operator<<( QDebug& s, const Calamares::ModuleSystem::InstanceKey& i );
inline QDebug&
operator<<( QDebug&& s, const Calamares::ModuleSystem::InstanceKey& i )
{
    return s << i;
}

}  // namespace ModuleSystem
}  // namespace Calamares

#endif
