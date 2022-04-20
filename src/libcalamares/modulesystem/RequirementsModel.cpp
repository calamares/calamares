/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019-2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#include "RequirementsModel.h"

#include "utils/Logger.h"

namespace Calamares
{

void
RequirementsModel::clear()
{
    QMutexLocker l( &m_addLock );
    beginResetModel();
    m_requirements.clear();
    endResetModel();
    reCheckList();
}

void
RequirementsModel::addRequirementsList( const Calamares::RequirementsList& requirements )
{
    QMutexLocker l( &m_addLock );

    beginResetModel();
    for ( const auto& r : requirements )
    {
        auto it = std::find_if( m_requirements.begin(),
                                m_requirements.end(),
                                [ &r ]( const Calamares::RequirementEntry& re ) { return r.name == re.name; } );
        if ( it != m_requirements.end() )
        {
            *it = r;
        }
        else
        {
            m_requirements.append( r );
        }
    }
    endResetModel();
    reCheckList();
}

void
RequirementsModel::reCheckList()
{
    auto isUnSatisfied = []( const Calamares::RequirementEntry& e ) { return !e.satisfied; };
    auto isMandatoryAndUnSatisfied = []( const Calamares::RequirementEntry& e ) { return e.mandatory && !e.satisfied; };

    m_satisfiedRequirements = std::none_of( m_requirements.begin(), m_requirements.end(), isUnSatisfied );
    m_satisfiedMandatory = std::none_of( m_requirements.begin(), m_requirements.end(), isMandatoryAndUnSatisfied );

    Q_EMIT satisfiedRequirementsChanged( m_satisfiedRequirements );
    Q_EMIT satisfiedMandatoryChanged( m_satisfiedMandatory );
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
    int count = 0;
    for ( const auto& r : m_requirements )
    {
        cDebug() << Logger::SubEntry << "requirement" << count << r.name << "satisfied?" << r.satisfied << "mandatory?"
                 << r.mandatory;
        ++count;
    }
}

void
RequirementsModel::setProgressMessage( const QString& m )
{
    m_progressMessage = m;
    Q_EMIT progressMessageChanged( m_progressMessage );
}

}  // namespace Calamares
