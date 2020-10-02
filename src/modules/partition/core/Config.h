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
    /** @brief The installation choice (Erase, Alongside, ...)
     *
     * This is an int because exposing the enum values is slightly complicated
     * by the source layout.
     */
    Q_PROPERTY( InstallChoice installChoice READ installChoice WRITE setInstallChoice NOTIFY installChoiceChanged )

public:
    Config( QObject* parent );
    virtual ~Config() = default;

    enum InstallChoice
    {
        NoChoice,
        Alongside,
        Erase,
        Replace,
        Manual
    };
    Q_ENUM( InstallChoice )
    static const NamedEnumTable< InstallChoice >& installChoiceNames();

    void setConfigurationMap( const QVariantMap& );
    void updateGlobalStorage() const;

    PartitionActions::Choices::SwapChoiceSet swapChoices() const { return m_swapChoices; }

    /** @brief What kind of installation (partitioning) is requested **initially**?
     *
     * @return the partitioning choice (may be @c NoChoice)
     */
    InstallChoice initialInstallChoice() const { return m_initialInstallChoice; }

    /** @brief What kind of installation (partition) is requested **now**?
     *
     * This changes depending on what the user selects (unlike the initial choice,
     * which is fixed by the configuration).
     *
     * @return the partitioning choice (may be @c NoChoice)
     */
    InstallChoice installChoice() const { return m_installChoice; }


    /** @brief What kind of swap selection is requested **initially**?
     *
     * @return The swap choice (may be @c NoSwap )
     */
    PartitionActions::Choices::SwapChoice initialSwapChoice() const { return m_initialSwapChoice; }

public Q_SLOTS:
    void setInstallChoice( int );
    void setInstallChoice( InstallChoice );

Q_SIGNALS:
    void installChoiceChanged( InstallChoice );

private:
    PartitionActions::Choices::SwapChoice m_initialSwapChoice;
    PartitionActions::Choices::SwapChoiceSet m_swapChoices;
    InstallChoice m_initialInstallChoice = NoChoice;
    InstallChoice m_installChoice = NoChoice;
    qreal m_requiredStorageGiB = 0.0;  // May duplicate setting in the welcome module
};


#endif
