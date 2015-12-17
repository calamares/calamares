/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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

class ExpandableRadioButton;
class PartitionBarsView;
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

signals:
    void nextStatusChanged( bool );
    void actionChosen();
    void deviceChosen();

private:
    void setNextEnabled( bool enabled );
    void setupChoices();
    QComboBox* createBootloaderComboBox( ExpandableRadioButton* parentButton );
    ExpandableRadioButton* createEraseButton();
    ExpandableRadioButton* createReplaceButton();
    Device* selectedDevice();
    void applyDeviceChoice();
    void updateDeviceStatePreview();
    void applyActionChoice( ChoicePage::Choice choice );
    void updateActionChoicePreview( ChoicePage::Choice choice );
    void setupActions();
    OsproberEntryList getOsproberEntriesForDevice( Device* device ) const;

    bool m_nextEnabled;
    PartitionCoreModule* m_core;

    QMutex m_previewsMutex;

    Choice m_choice;

    bool m_isEfi;
    QComboBox* m_drivesCombo;

    PrettyRadioButton* m_alongsideButton;
    ExpandableRadioButton* m_eraseButton;
    ExpandableRadioButton* m_replaceButton;
    PrettyRadioButton* m_somethingElseButton;

    DeviceInfoWidget* m_deviceInfoWidget;

    QPointer< PartitionBarsView > m_beforePartitionBarsView;
    QPointer< PartitionLabelsView > m_beforePartitionLabelsView;

    int m_lastSelectedDeviceIndex;
};

#endif // CHOICEPAGE_H
