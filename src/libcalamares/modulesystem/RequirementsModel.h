/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019-2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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
    Q_OBJECT
    Q_PROPERTY( bool satisfiedRequirements READ satisfiedRequirements NOTIFY satisfiedRequirementsChanged FINAL )
    Q_PROPERTY( bool satisfiedMandatory READ satisfiedMandatory NOTIFY satisfiedMandatoryChanged FINAL )
    Q_PROPERTY( QString progressMessage READ progressMessage NOTIFY progressMessageChanged FINAL )

public:
    using QAbstractListModel::QAbstractListModel;

    enum Roles : short
    {
        NegatedText = Qt::DisplayRole,
        Details = Qt::ToolTipRole,
        Name = Qt::UserRole,
        Satisfied,
        Mandatory,
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

    ///@brief Update progress message (called by the checker)
    void setProgressMessage( const QString& m );

    ///@brief Append some requirements; resets the model
    void addRequirementsList( const Calamares::RequirementsList& requirements );

    ///@brief Check the whole list, emit signals satisfied...()
    void reCheckList();

signals:
    void satisfiedRequirementsChanged( bool value );
    void satisfiedMandatoryChanged( bool value );
    void progressMessageChanged( QString message );

protected:
    QHash< int, QByteArray > roleNames() const override;

    ///@brief Clears the requirements; resets the model
    void clear();

private:
    QString m_progressMessage;
    QMutex m_addLock;
    RequirementsList m_requirements;
    bool m_satisfiedRequirements = false;
    bool m_satisfiedMandatory = false;
};

}  // namespace Calamares

#endif
