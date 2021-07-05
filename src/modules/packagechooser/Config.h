/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef PACKAGECHOOSER_CONFIG_H
#define PACKAGECHOOSER_CONFIG_H

#include "PackageModel.h"

#include "modulesystem/Config.h"
#include "modulesystem/InstanceKey.h"

#include <memory>

enum class PackageChooserMode
{
    Optional,  // zero or one
    Required,  // exactly one
    OptionalMultiple,  // zero or more
    RequiredMultiple  // one or more
};

const NamedEnumTable< PackageChooserMode >& packageChooserModeNames();

enum class PackageChooserMethod
{
    Legacy,  // use contextualprocess or other custom
    Packages,  // use the packages module
};

const NamedEnumTable< PackageChooserMethod >& PackageChooserMethodNames();

class Config : public Calamares::ModuleSystem::Config
{
    Q_OBJECT

public:
    Config( QObject* parent = nullptr );
    ~Config() override;

    /** @brief Sets the default Id for this Config
     *
     * The default Id is the (owning) module identifier for the config,
     * and it is used when the Id read from the config file is empty.
     * The **usual** configuration when using method *packages* is
     * to rely on the default Id.
     */
    void setDefaultId( const Calamares::ModuleSystem::InstanceKey& defaultId ) { m_defaultId = defaultId; }
    void setConfigurationMap( const QVariantMap& ) override;

    PackageChooserMode mode() const { return m_mode; }
    PackageListModel* model() const { return m_model; }
    QModelIndex defaultSelectionIndex() const { return m_defaultModelIndex; }

    /** @brief Returns an "introductory package" which describes packagechooser
     *
     * If the model contains a "none" package, returns that one on
     * the assumption that it is one to describe the whole; otherwise
     * returns a totally generic description.
     */
    const PackageItem& introductionPackage() const;

    /** @brief Write selection to global storage
     *
     * Updates the GS keys for this packagechooser, marking all
     * (and only) the packages in @p selected as selected.
     */
    void updateGlobalStorage( const QStringList& selected ) const;
    /// As updateGlobalStorage() with an empty selection list
    void fillGSSecondaryConfiguration() const { updateGlobalStorage( QStringList() ); }

private:
    PackageListModel* m_model = nullptr;
    QModelIndex m_defaultModelIndex;

    /// Selection mode for this module
    PackageChooserMode m_mode = PackageChooserMode::Optional;
    /// How this module stores to GS
    PackageChooserMethod m_method = PackageChooserMethod::Legacy;
    /// Id (used to identify settings from this module in GS)
    QString m_id;
    /// Value to use for id if none is set in the config file
    Calamares::ModuleSystem::InstanceKey m_defaultId;
};


#endif
