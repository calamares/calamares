/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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

#include <QWidget>

#include "OsproberEntry.h"

class QBoxLayout;
class QLabel;

class PartitionCoreModule;

class ChoicePage : public QWidget
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

    void init( PartitionCoreModule* core, const OsproberEntryList& osproberEntries );

    bool isNextEnabled();

    Choice currentChoice();

signals:
    void nextStatusChanged( bool );

private:
    void setNextEnabled( bool enabled );

    bool m_nextEnabled;
    PartitionCoreModule* m_core;
    QBoxLayout* m_itemsLayout;
    QLabel* m_messageLabel;

    Choice m_choice;
};

#endif // CHOICEPAGE_H
