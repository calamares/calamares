/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2021 Anke Boersma <demm@kaosx.us>
 *   SPDX-FileCopyrightText: 2021 shivanandvp <shivanandvp@rebornos.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef PACKAGECHOOSERQ_CONFIG_H
#define PACKAGECHOOSERQ_CONFIG_H

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
    NetAdd,  // adds packages to the netinstall module
    NetSelect,  // makes selections in the netinstall module
};

const NamedEnumTable< PackageChooserMethod >& PackageChooserMethodNames();

class Config : public Calamares::ModuleSystem::Config
{
    Q_OBJECT

    Q_ENUM( PackageChooserMode )

    Q_PROPERTY( QString prettyStatus READ prettyStatus NOTIFY prettyStatusChanged FINAL )

    Q_PROPERTY( PackageChooserMode mode MEMBER m_mode )
    Q_PROPERTY( QString promptMessage MEMBER m_promptMessage )

    Q_PROPERTY( QStringList displayedEntryIds MEMBER m_displayedEntryIds NOTIFY displayedEntryIdsChanged )
    Q_PROPERTY( QStringList displayedEntryNames MEMBER m_displayedEntryNames NOTIFY displayedEntryNamesChanged )
    Q_PROPERTY( QStringList displayedEntryDescriptions MEMBER m_displayedEntryDescriptions NOTIFY
                    displayedEntryDescriptionsChanged )
    Q_PROPERTY( QVector< QString > displayedEntryScreenshots MEMBER m_displayedEntryScreenshots NOTIFY
                    displayedEntryScreenshotsChanged )
    Q_PROPERTY( QVector< QStringList > displayedEntryPackages MEMBER m_displayedEntryPackages NOTIFY
                    displayedEntryPackagesChanged )
    Q_PROPERTY( QVector< bool > displayedEntrySelectedStates MEMBER m_displayedEntrySelectedStates NOTIFY
                    displayedEntrySelectedStatesChanged )

    Q_PROPERTY( QStringList selections MEMBER m_selections )

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
    void pageLeavingTasks();

    QStringList m_displayedEntryIds;
    QStringList m_displayedEntryNames;
    QStringList m_displayedEntryDescriptions;
    QVector< QString > m_displayedEntryScreenshots;
    QVector< QStringList > m_displayedEntryPackages;
    QVector< bool > m_displayedEntrySelectedStates;

    QStringList m_selections;

    Q_INVOKABLE void addSelection( const QString& selection );
    Q_INVOKABLE void removeSelection( const QString& selection );
    void updateDisplayedData();
    bool refreshNextButtonStatus();

    QString prettyName() const;
    QString prettyStatus() const;

signals:
    void prettyStatusChanged();
    void nextStatusChanged( bool );

    // void displayedEntryIdsChanged(QStringList &a_displayedEntryIds);
    // void displayedEntryNamesChanged(QStringList &a_displayedEntryNames);
    // void displayedEntryDescriptionsChanged(QStringList &a_displayedEntryDescriptions);
    // void displayedEntryScreenshotsChanged(QVector<QString> &a_displayedEntryScreenshots);
    // void displayedEntryPackagesChanged(QVector<QStringList> &a_displayedEntryPackages);
    // void displayedEntrySelectedStatesChanged(QVector<bool> &a_displayedEntrySelectedStates);

    void displayedEntryIdsChanged();
    void displayedEntryNamesChanged();
    void displayedEntryDescriptionsChanged();
    void displayedEntryScreenshotsChanged();
    void displayedEntryPackagesChanged();
    void displayedEntrySelectedStatesChanged();

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
    /// Name of the output condition
    QString m_outputConditionKey;
    QString m_promptMessage;
    bool m_configurationMapSet = false;
    CalamaresUtils::Locale::TranslatedString* m_stepName;  // As it appears in the sidebar
};

#endif
