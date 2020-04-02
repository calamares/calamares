/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2018-2019, Adriaan de Groot <groot@kde.org>
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
#ifndef MODULESYSTEM_INSTANCEKEY_H
#define MODULESYSTEM_INSTANCEKEY_H

#include <QDebug>
#include <QPair>
#include <QString>

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
class InstanceKey : public QPair< QString, QString >
{
public:
    /// @brief Create an instance key from explicit module and id.
    InstanceKey( const QString& module, const QString& id )
        : QPair( module, id )
    {
        if ( second.isEmpty() )
        {
            second = first;
        }
        validate();
    }

    /// @brief Create unusual, invalid instance key
    InstanceKey()
        : QPair( QString(), QString() )
    {
    }

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
};

QDebug& operator<<( QDebug& s, const Calamares::ModuleSystem::InstanceKey& i );

}  // namespace ModuleSystem
}  // namespace Calamares

#endif
