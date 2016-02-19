/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2016, Teo Mrnjavac <teo@kde.org>
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

#include <QWidget>

#include "core/OsproberEntry.h"

#include <QMutex>
#include <QPointer>

class QBoxLayout;
class QComboBox;
class QLabel;
class QListView;

class PartitionBarsView;
class PartitionSplitterWidget;
class PartitionLabelsView;
class PartitionCoreModule;
class PrettyRadioButton;
class DeviceInfoWidget;

class Device;

class ChoicePage : public QWidget, private Ui::ChoicePage
{
    Q_OBJECT
public:
    enum Choice
    {
        NoChoice,
        Alongside,
        Erase,
        Replace,
        Manual
    };

    explicit ChoicePage( QWidget* parent = nullptr );
    virtual ~ChoicePage();

    void init( PartitionCoreModule* core );

    bool isNextEnabled() const;

    Choice currentChoice() const;

    void onLeave();

signals:
    void nextStatusChanged( bool );
    void actionChosen();
    void deviceChosen();

private slots:
    void doReplaceSelectedPartition( const QModelIndex& current, const QModelIndex& previous );
    void doAlongsideSetupSplitter( const QModelIndex& current, const QModelIndex& previous );

private:
    void setNextEnabled( bool enabled );
    void setupChoices();
    QComboBox* createBootloaderComboBox( QWidget* parentButton );
    Device* selectedDevice();
    void applyDeviceChoice();
    void continueApplyDeviceChoice();
    void updateDeviceStatePreview();
    void applyActionChoice( ChoicePage::Choice choice );
    void updateActionChoicePreview( ChoicePage::Choice choice );
    void setupActions();
    OsproberEntryList getOsproberEntriesForDevice( Device* device ) const;
    void doAlongsideApply();
    void setupEfiSystemPartitionSelector();

    bool m_nextEnabled;
    PartitionCoreModule* m_core;

    QMutex m_previewsMutex;

    Choice m_choice;

    bool m_isEfi;
    QComboBox* m_drivesCombo;

    QButtonGroup* m_grp;
    PrettyRadioButton* m_alongsideButton;
    PrettyRadioButton* m_eraseButton;
    PrettyRadioButton* m_replaceButton;
    PrettyRadioButton* m_somethingElseButton;

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

    QMutex m_coreMutex;
};

#endif // CHOICEPAGE_H
