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

#include "utils/NamedEnum.h"

#include <QObject>
#include <QSet>

class Config : public QObject
{
    Q_OBJECT
    ///@brief The installation choice (Erase, Alongside, ...)
    Q_PROPERTY( InstallChoice installChoice READ installChoice WRITE setInstallChoice NOTIFY installChoiceChanged )

    ///@brief The swap choice (None, Small, Hibernate, ...) which only makes sense when Erase is chosen
    Q_PROPERTY( SwapChoice swapChoice READ swapChoice WRITE setSwapChoice NOTIFY swapChoiceChanged )

    Q_PROPERTY( bool allowManualPartitioning READ allowManualPartitioning CONSTANT FINAL )

public:
    Config( QObject* parent );
    ~Config() override = default;

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

    /** @brief Choice of swap (size and type) */
    enum SwapChoice
    {
        NoSwap,  // don't create any swap, don't use any
        ReuseSwap,  // don't create, but do use existing
        SmallSwap,  // up to 8GiB of swap
        FullSwap,  // ensureSuspendToDisk -- at least RAM size
        SwapFile  // use a file (if supported)
    };
    Q_ENUM( SwapChoice )
    static const NamedEnumTable< SwapChoice >& swapChoiceNames();
    using SwapChoiceSet = QSet< SwapChoice >;

    void setConfigurationMap( const QVariantMap& );
    void updateGlobalStorage() const;

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

    /** @brief The set of swap choices enabled for this install
     *
     * Not all swap choices are supported by each distro, so they
     * can choose to enable or disable them. This method
     * returns a set (hopefully non-empty) of configured swap choices.
     */
    SwapChoiceSet swapChoices() const { return m_swapChoices; }

    /** @brief What kind of swap selection is requested **initially**?
     *
     * @return The swap choice (may be @c NoSwap )
     */
    SwapChoice initialSwapChoice() const { return m_initialSwapChoice; }

    /** @brief What kind of swap selection is requested **now**?
     *
     * A choice of swap only makes sense when install choice Erase is made.
     *
     * @return The swap choice (may be @c NoSwap).
     */
    SwapChoice swapChoice() const { return m_swapChoice; }

    ///@brief Is manual partitioning allowed (not explicitly disnabled in the config file)?
    bool allowManualPartitioning() const;

public Q_SLOTS:
    void setInstallChoice( int );  ///< Translates a button ID or so to InstallChoice
    void setInstallChoice( InstallChoice );
    void setSwapChoice( int );  ///< Translates a button ID or so to SwapChoice
    void setSwapChoice( SwapChoice );

Q_SIGNALS:
    void installChoiceChanged( InstallChoice );
    void swapChoiceChanged( SwapChoice );

private:
    SwapChoiceSet m_swapChoices;
    SwapChoice m_initialSwapChoice = NoSwap;
    SwapChoice m_swapChoice = NoSwap;
    InstallChoice m_initialInstallChoice = NoChoice;
    InstallChoice m_installChoice = NoChoice;
    qreal m_requiredStorageGiB = 0.0;  // May duplicate setting in the welcome module
    QStringList m_requiredPartitionTableType;
};

/** @brief Given a set of swap choices, return a sensible value from it.
 *
 * "Sensible" here means: if there is one value, use it; otherwise, use
 * NoSwap if there are no choices, or if NoSwap is one of the choices, in the set.
 * If that's not possible, any value from the set.
 */
Config::SwapChoice pickOne( const Config::SwapChoiceSet& s );


#endif
