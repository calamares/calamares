/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019-2020, Adriaan de Groot <groot@kde.org>
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

#ifndef CALAMARES_REQUIREMENTSMODEL_H
#define CALAMARES_REQUIREMENTSMODEL_H

#include "Requirement.h"

#include "DllMacro.h"

#include <QAbstractListModel>

namespace Calamares
{

class DLLEXPORT RequirementsModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY( bool satisfiedRequirements READ satisfiedRequirements NOTIFY satisfiedRequirementsChanged FINAL )
    Q_PROPERTY( bool satisfiedMandatory READ satisfiedMandatory NOTIFY satisfiedMandatoryChanged FINAL )

public:
    using QAbstractListModel::QAbstractListModel;

    enum Roles : short
    {
        Name,
        Satisfied,
        Mandatory,
        Details,
        NegatedText,
        HasDetails
    };
    // No Q_ENUM because these are exposed through roleNames()

    bool satisfiedRequirements() const { return m_satisfiedRequirements; }
    bool satisfiedMandatory() const { return m_satisfiedMandatory; }

    const Calamares::RequirementEntry& getEntry( int index ) const
    {
        return m_requirements.at( index );
    }

    void setRequirementsList( const Calamares::RequirementsList& requirements );

    QVariant data( const QModelIndex& index, int role ) const override;
    int rowCount( const QModelIndex& ) const override;
    int count() const { return m_requirements.count(); }

signals:
    void satisfiedRequirementsChanged( bool value );
    void satisfiedMandatoryChanged( bool value );

protected:
    QHash< int, QByteArray > roleNames() const override;

private:
    Calamares::RequirementsList m_requirements;
    bool m_satisfiedRequirements = false;
    bool m_satisfiedMandatory = false;

};

}  // namespace Calamares

#endif
