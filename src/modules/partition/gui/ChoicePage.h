/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018-2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2019 Collabora Ltd
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef CHOICEPAGE_H
#define CHOICEPAGE_H

#include "ui_ChoicePage.h"


#include "Config.h"
#include "core/OsproberEntry.h"

#include <QMutex>
#include <QPointer>
#include <QSet>
#include <QWidget>

class QBoxLayout;
class QComboBox;
class QLabel;
class QListView;

namespace Calamares
{
namespace Widgets
{
class PrettyRadioButton;
}
}  // namespace Calamares

class Config;
class DeviceInfoWidget;
class PartitionBarsView;
class PartitionSplitterWidget;
class PartitionLabelsView;
class PartitionCoreModule;

class Device;

using SwapChoiceSet = Config::SwapChoiceSet;

/**
 * @brief The ChoicePage class is the first page of the partitioning interface.
 * It offers a choice between partitioning operations and initiates all automated
 * partitioning modes. For manual partitioning, see PartitionPage.
 */
class ChoicePage : public QWidget, private Ui::ChoicePage
{
    Q_OBJECT
public:
    explicit ChoicePage( Config* config, QWidget* parent = nullptr );
    ~ChoicePage() override;

    /**
     * @brief init runs when the PartitionViewStep and the PartitionCoreModule are
     *      ready. Sets up the rest of the UI based on os-prober output.
     * @param core the PartitionCoreModule pointer.
     */
    void init( PartitionCoreModule* core );

    /**
     * @brief isNextEnabled answers whether the current state of the page is such
     * that progressing to the next page should be allowed.
     * @return true if next is allowed, otherwise false.
     */
    bool isNextEnabled() const;

    /**
     * @brief onLeave runs when control passes from this page to another one.
     */
    void onLeave();

    /**
     * @brief applyActionChoice reacts to a choice of partitioning mode.
     * @param choice the partitioning action choice.
     */
    void applyActionChoice( Config::InstallChoice choice );

    int lastSelectedDeviceIndex();
    void setLastSelectedDeviceIndex( int index );

signals:
    void nextStatusChanged( bool );
    void actionChosen();
    void deviceChosen();

private slots:
    void onPartitionToReplaceSelected( const QModelIndex& current, const QModelIndex& previous );
    void doReplaceSelectedPartition( const QModelIndex& current );
    void doAlongsideSetupSplitter( const QModelIndex& current, const QModelIndex& previous );
    void onEncryptWidgetStateChanged();
    void onHomeCheckBoxStateChanged();

    /// @brief Calls applyActionChoice() as needed.
    void onActionChanged();
    /// @brief Calls onActionChanged() as needed.
    void onEraseSwapChoiceChanged();

    void retranslate();

private:
    bool calculateNextEnabled() const;
    void updateNextEnabled();
    void setupChoices();
    void checkInstallChoiceRadioButton( Config::InstallChoice choice );  ///< Sets the chosen button to "on"
    /** @brief Create a panel with "boot loader location:"
     *
     * Panel + dropdown and handling for model updates. Returns a pointer
     * to the panel's widget.
     */
    QWidget* createBootloaderPanel();
    Device* selectedDevice();

    /* Change the UI depending on the device selected. */
    void hideButtons();  // Hide everything when no device
    void applyDeviceChoice();  // Start scanning new device
    void continueApplyDeviceChoice();  // .. called after scan

    void updateDeviceStatePreview();
    void updateActionChoicePreview( Config::InstallChoice choice );
    void setupActions();
    OsproberEntryList getOsproberEntriesForDevice( Device* device ) const;
    void doAlongsideApply();
    void setupEfiSystemPartitionSelector();

    // Translations support
    void updateSwapChoicesTr();
    void updateChoiceButtonsTr();

    Config* m_config;
    bool m_nextEnabled;
    PartitionCoreModule* m_core;

    QMutex m_previewsMutex;

    bool m_isEfi;
    QComboBox* m_drivesCombo;

    QButtonGroup* m_grp;
    Calamares::Widgets::PrettyRadioButton* m_alongsideButton;
    Calamares::Widgets::PrettyRadioButton* m_eraseButton;
    Calamares::Widgets::PrettyRadioButton* m_replaceButton;
    Calamares::Widgets::PrettyRadioButton* m_somethingElseButton;
    QComboBox* m_eraseSwapChoiceComboBox = nullptr;  // UI, see also Config's swap choice
    QComboBox* m_eraseFsTypesChoiceComboBox = nullptr;  // UI, see also Config's erase-mode FS


    DeviceInfoWidget* m_deviceInfoWidget;

    QPointer< PartitionBarsView > m_beforePartitionBarsView;
    QPointer< PartitionLabelsView > m_beforePartitionLabelsView;
    QPointer< PartitionBarsView > m_afterPartitionBarsView;
    QPointer< PartitionLabelsView > m_afterPartitionLabelsView;
    QPointer< PartitionSplitterWidget > m_afterPartitionSplitterWidget;
    QPointer< QComboBox > m_bootloaderComboBox;
    QPointer< QLabel > m_efiLabel;
    QPointer< QComboBox > m_efiComboBox;

    int m_lastSelectedDeviceIndex = -1;
    int m_lastSelectedActionIndex = -1;

    bool m_enableEncryptionWidget;

    QMutex m_coreMutex;
};

#endif  // CHOICEPAGE_H
