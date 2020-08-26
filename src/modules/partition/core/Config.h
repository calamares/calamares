/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef PARTITION_CONFIG_H
#define PARTITION_CONFIG_H

#include "core/PartitionActions.h"

#include <QObject>
#include <QSet>

class Config : public QObject
{
    Q_OBJECT

public:
    Config( QObject* parent );
    virtual ~Config() = default;

    void setConfigurationMap( const QVariantMap& );
    void updateGlobalStorage() const;

    PartitionActions::Choices::SwapChoiceSet swapChoices() const { return m_swapChoices; }

    /**
     * @brief What kind of installation (partitioning) is requested **initially**?
     *
     * @return the partitioning choice (may by @c NoChoice)
     */
    PartitionActions::Choices::InstallChoice initialInstallChoice() const { return m_initialInstallChoice; }

private:
    PartitionActions::Choices::SwapChoiceSet m_swapChoices;
    PartitionActions::Choices::InstallChoice m_initialInstallChoice = PartitionActions::Choices::NoChoice;
    qreal m_requiredStorageGiB = 0.0;  // May duplicate setting in the welcome module
};


#endif
