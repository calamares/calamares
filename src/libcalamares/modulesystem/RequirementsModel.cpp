/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   SPDX-FileCopyrightText: 2019-2020 Adriaan de Groot <groot@kde.org>
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
 *
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *   License-Filename: LICENSE
 *
 */

#include "RequirementsModel.h"

#include "utils/Logger.h"

namespace Calamares
{

void
RequirementsModel::addRequirementsList( const Calamares::RequirementsList& requirements )
{
    QMutexLocker l( &m_addLock );
    emit beginResetModel();
    m_requirements.append( requirements );
    changeRequirementsList();
    emit endResetModel();
}

void
RequirementsModel::changeRequirementsList()
{
    auto isUnSatisfied = []( const Calamares::RequirementEntry& e ) { return !e.satisfied; };
    auto isMandatoryAndUnSatisfied = []( const Calamares::RequirementEntry& e ) { return e.mandatory && !e.satisfied; };

    m_satisfiedRequirements = std::none_of( m_requirements.begin(), m_requirements.end(), isUnSatisfied );
    m_satisfiedMandatory = std::none_of( m_requirements.begin(), m_requirements.end(), isMandatoryAndUnSatisfied );

    emit satisfiedRequirementsChanged( m_satisfiedRequirements );
    emit satisfiedMandatoryChanged( m_satisfiedMandatory );
}

int
RequirementsModel::rowCount( const QModelIndex& ) const
{
    return m_requirements.count();
}

QVariant
RequirementsModel::data( const QModelIndex& index, int role ) const
{
    const auto requirement = m_requirements.at( index.row() );

    switch ( role )
    {
    case Roles::Name:
        return requirement.name;
    case Roles::Details:
        return requirement.enumerationText();
    case Roles::NegatedText:
        return requirement.negatedText();
    case Roles::Satisfied:
        return requirement.satisfied;
    case Roles::Mandatory:
        return requirement.mandatory;
    case Roles::HasDetails:
        return requirement.hasDetails();
    default:
        return QVariant();
    }
}

QHash< int, QByteArray >
RequirementsModel::roleNames() const
{
    static QHash< int, QByteArray > roles;
    roles[ Roles::Name ] = "name";
    roles[ Roles::Details ] = "details";
    roles[ Roles::NegatedText ] = "negatedText";
    roles[ Roles::Satisfied ] = "satisfied";
    roles[ Roles::Mandatory ] = "mandatory";
    roles[ Roles::HasDetails ] = "hasDetails";
    return roles;
}

void
RequirementsModel::describe() const
{
    cDebug() << "Requirements model has" << m_requirements.count() << "items";
    bool acceptable = true;
    int count = 0;
    for ( const auto& r : m_requirements )
    {
        cDebug() << Logger::SubEntry << "requirement" << count << r.name
            << "satisfied?" << r.satisfied
            << "mandatory?" << r.mandatory;
        if ( r.mandatory && !r.satisfied )
        {
            acceptable = false;
        }
        ++count;
    }
}

void
RequirementsModel::setProgressMessage( const QString& m )
{
    m_progressMessage = m;
    emit progressMessageChanged( m_progressMessage );
}

}  // namespace Calamares
