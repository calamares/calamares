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

#ifndef ALONGSIDEPAGE_H
#define ALONGSIDEPAGE_H

#include <QWidget>

#include "core/OsproberEntry.h"

class QComboBox;
class QLabel;
class PartitionCoreModule;
class PartitionSplitterWidget;
class Partition;
class PartitionBarsView;
class PartitionLabelsView;
class Device;

class AlongsidePage : public QWidget
{
    Q_OBJECT
public:
    explicit AlongsidePage( QWidget* parent = nullptr );

    void init( PartitionCoreModule* core );

    bool isNextEnabled() const;

    void applyChanges();

signals:
    void nextStatusChanged( bool );

private slots:
    void onPartitionSelected( int comboBoxIndex );

private:
    void setNextEnabled( bool enabled );

    QComboBox* m_partitionsComboBox;
    PartitionSplitterWidget* m_splitterWidget;
    PartitionBarsView* m_previewWidget;
    PartitionLabelsView* m_previewLabels;
    QLabel* m_sizeLabel;

    QLabel* m_efiLabel;
    QComboBox* m_efiComboBox;

    PartitionCoreModule* m_core;

    bool m_isEfi;

    bool m_nextEnabled;
};

#endif // ALONGSIDEPAGE_H
