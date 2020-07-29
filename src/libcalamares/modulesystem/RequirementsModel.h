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

#ifndef CALAMARES_REQUIREMENTSMODEL_H
#define CALAMARES_REQUIREMENTSMODEL_H

#include "Requirement.h"

#include "DllMacro.h"

#include <QAbstractListModel>
#include <QMutex>

namespace Calamares
{
class RequirementsChecker;

/** @brief System requirements from each module and their checked-status
 *
 * A Calamares module can have system requirements (e.g. check for
 * internet, or amount of RAM, or an available disk) which can
 * be stated and checked.
 *
 * This model collects those requirements, can run the checks, and
 * reports on the overall status of those checks.
 */
class DLLEXPORT RequirementsModel : public QAbstractListModel
{
    friend class RequirementsChecker;

    Q_OBJECT
    Q_PROPERTY( bool satisfiedRequirements READ satisfiedRequirements NOTIFY satisfiedRequirementsChanged FINAL )
    Q_PROPERTY( bool satisfiedMandatory READ satisfiedMandatory NOTIFY satisfiedMandatoryChanged FINAL )
    Q_PROPERTY( QString progressMessage READ progressMessage NOTIFY progressMessageChanged FINAL )

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

    ///@brief Are all the requirements satisfied?
    bool satisfiedRequirements() const { return m_satisfiedRequirements; }
    ///@brief Are all the **mandatory** requirements satisfied?
    bool satisfiedMandatory() const { return m_satisfiedMandatory; }
    ///@brief Message (from an ongoing check) about progress
    QString progressMessage() const { return m_progressMessage; }


    QVariant data( const QModelIndex& index, int role ) const override;
    int rowCount( const QModelIndex& ) const override;
    int count() const { return m_requirements.count(); }

    ///@brief Debugging tool, describe the checking-state
    void describe() const;

signals:
    void satisfiedRequirementsChanged( bool value );
    void satisfiedMandatoryChanged( bool value );
    void progressMessageChanged( QString message );

protected:
    QHash< int, QByteArray > roleNames() const override;

    ///@brief Append some requirements; resets the model
    void addRequirementsList( const Calamares::RequirementsList& requirements );

    ///@brief Update progress message (called by the checker)
    void setProgressMessage( const QString& m );

private:
    ///@brief Implementation for {set,add}RequirementsList
    void changeRequirementsList();

    QString m_progressMessage;
    QMutex m_addLock;
    RequirementsList m_requirements;
    bool m_satisfiedRequirements = false;
    bool m_satisfiedMandatory = false;
};

}  // namespace Calamares

#endif
