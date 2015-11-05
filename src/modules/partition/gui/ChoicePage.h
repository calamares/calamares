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

class QBoxLayout;
class QLabel;
class QListView;

class PartitionCoreModule;
class PrettyRadioButton;

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

    explicit ChoicePage( bool compactMode = false, QWidget* parent = nullptr );
    virtual ~ChoicePage();

    void init( PartitionCoreModule* core,
               const OsproberEntryList& osproberEntries );

    bool isNextEnabled() const;

    Choice currentChoice() const;

signals:
    void nextStatusChanged( bool );
    void actionChosen();

private:
    bool compact();
    void setNextEnabled( bool enabled );
    void setupChoices();
    Device* selectedDevice();
    void applyDeviceChoice();
    void updateDeviceStatePreview( Device* currentDevice );
    void applyActionChoice( Device* currentDevice, ChoicePage::Choice choice );
    void updateActionChoicePreview( Device* currentDevice, ChoicePage::Choice choice );
    void setupActions( Device* currentDevice );

    bool m_nextEnabled;
    PartitionCoreModule* m_core;
    OsproberEntryList m_osproberEntries;

    QMutex m_previewsMutex;

    Choice m_choice;

    bool m_compactMode;
    QWidget* m_drivesView;

    PrettyRadioButton* m_alongsideButton;
    PrettyRadioButton* m_eraseButton;
    PrettyRadioButton* m_replaceButton;
    PrettyRadioButton* m_somethingElseButton;

    int m_lastSelectedDeviceIndex;
};

#endif // CHOICEPAGE_H
