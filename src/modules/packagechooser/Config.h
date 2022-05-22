/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2021 Anke Boersma <demm@kaosx.us>
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
#include <optional>

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
    NetAdd,  // adds packages to the netinstall module
    NetSelect,  // makes selections in the netinstall module
};

const NamedEnumTable< PackageChooserMethod >& PackageChooserMethodNames();

class Config : public Calamares::ModuleSystem::Config
{
    Q_OBJECT

    /** @brief This is the single-select package-choice
     *
     * For (QML) modules that support only a single selection and
     * just want to do things in a straightforward pick-this-one
     * way, the packageChoice property is a (the) way to go.
     *
     * Writing to this property means that any other form of package-
     * choice or selection is ignored.
     */
    Q_PROPERTY( QString packageChoice READ packageChoice WRITE setPackageChoice NOTIFY packageChoiceChanged )
    Q_PROPERTY( QString prettyStatus READ prettyStatus NOTIFY prettyStatusChanged FINAL )

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
    /** @brief Write selection to global storage
     *
     * Updates the GS keys for this packagechooser, marking **only**
     * the package choice as selected. This assumes that the single-
     * selection QML code is in use.
     */
    void updateGlobalStorage() const;

    QString packageChoice() const { return m_packageChoice.value_or( QString() ); }
    void setPackageChoice( const QString& packageChoice );

    QString prettyName() const;
    QString prettyStatus() const;

signals:
    void packageChoiceChanged( QString packageChoice );
    void prettyStatusChanged();

private:
    PackageListModel* m_model = nullptr;
    QModelIndex m_defaultModelIndex;

    /// Selection mode for this module
    PackageChooserMode m_mode = PackageChooserMode::Optional;
    /// How this module stores to GS
    PackageChooserMethod m_method = PackageChooserMethod::Legacy;
    /// Value to use for id if none is set in the config file
    Calamares::ModuleSystem::InstanceKey m_defaultId;
    /** @brief QML selection (for single-selection approaches)
     *
     * If there is no value, then there has been no selection.
     * Reading the property will return an empty QString.
     */
    std::optional< QString > m_packageChoice;
    CalamaresUtils::Locale::TranslatedString* m_stepName;  // As it appears in the sidebar
};


#endif
