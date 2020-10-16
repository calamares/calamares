/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2016, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2018-2019, Adriaan de Groot <groot@kde.org>
 *   Copyright 2019, Collabora Ltd
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

#ifndef CHOICEPAGE_H
#define CHOICEPAGE_H

#include "ui_ChoicePage.h"


#include "core/OsproberEntry.h"
#include "core/PartitionActions.h"

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
class PrettyRadioButton;
}

class PartitionBarsView;
class PartitionSplitterWidget;
class PartitionLabelsView;
class PartitionCoreModule;
class DeviceInfoWidget;

class Device;

using SwapChoiceSet = QSet< PartitionActions::Choices::SwapChoice >;

/**
 * @brief The ChoicePage class is the first page of the partitioning interface.
 * It offers a choice between partitioning operations and initiates all automated
 * partitioning modes. For manual partitioning, see PartitionPage.
 */
class ChoicePage : public QWidget, private Ui::ChoicePage
{
    Q_OBJECT
public:
    enum InstallChoice
    {
        NoChoice,
        Alongside,
        Erase,
        Replace,
        Manual
    };

    explicit ChoicePage( const SwapChoiceSet& swapChoices, QWidget* parent = nullptr );
    virtual ~ChoicePage();

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
     * @brief currentChoice returns the enum Choice value corresponding to the
     * currently selected partitioning mode (with a PrettyRadioButton).
     * @return the enum Choice value.
     */
    InstallChoice currentChoice() const;

    /**
     * @brief onLeave runs when control passes from this page to another one.
     */
    void onLeave();

    /**
     * @brief applyActionChoice reacts to a choice of partitioning mode.
     * @param choice the partitioning action choice.
     */
    void applyActionChoice( ChoicePage::InstallChoice choice );

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

private:
    void updateNextEnabled();
    void setupChoices();
    QComboBox* createBootloaderComboBox( QWidget* parentButton );
    Device* selectedDevice();

    /* Change the UI depending on the device selected. */
    void hideButtons();  // Hide everything when no device
    void applyDeviceChoice();  // Start scanning new device
    void continueApplyDeviceChoice();  // .. called after scan

    void updateDeviceStatePreview();
    void updateActionChoicePreview( ChoicePage::InstallChoice choice );
    void setupActions();
    OsproberEntryList getOsproberEntriesForDevice( Device* device ) const;
    void doAlongsideApply();
    void setupEfiSystemPartitionSelector();

    // Translations support
    void updateSwapChoicesTr( QComboBox* box );

    bool m_nextEnabled;
    PartitionCoreModule* m_core;

    QMutex m_previewsMutex;

    InstallChoice m_choice;

    bool m_isEfi;
    QComboBox* m_drivesCombo;

    QButtonGroup* m_grp;
    Calamares::PrettyRadioButton* m_alongsideButton;
    Calamares::PrettyRadioButton* m_eraseButton;
    Calamares::PrettyRadioButton* m_replaceButton;
    Calamares::PrettyRadioButton* m_somethingElseButton;
    QComboBox* m_eraseSwapChoiceComboBox;  // UI, see also m_eraseSwapChoice

    DeviceInfoWidget* m_deviceInfoWidget;

    QPointer< PartitionBarsView > m_beforePartitionBarsView;
    QPointer< PartitionLabelsView > m_beforePartitionLabelsView;
    QPointer< PartitionBarsView > m_afterPartitionBarsView;
    QPointer< PartitionLabelsView > m_afterPartitionLabelsView;
    QPointer< PartitionSplitterWidget > m_afterPartitionSplitterWidget;
    QPointer< QComboBox > m_bootloaderComboBox;
    QPointer< QLabel > m_efiLabel;
    QPointer< QComboBox > m_efiComboBox;

    int m_lastSelectedDeviceIndex;

    QString m_defaultFsType;
    bool m_enableEncryptionWidget;
    SwapChoiceSet m_availableSwapChoices;  // What is available
    PartitionActions::Choices::SwapChoice m_eraseSwapChoice;  // what is selected

    bool m_allowManualPartitioning;

    QMutex m_coreMutex;
};

#endif  // CHOICEPAGE_H
