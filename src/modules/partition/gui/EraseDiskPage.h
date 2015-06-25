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

#ifndef ERASEDISKPAGE_H
#define ERASEDISKPAGE_H

#include <QMutex>
#include <QWidget>

class PartitionCoreModule;
class QListView;
class Device;

class EraseDiskPage : public QWidget
{
    Q_OBJECT
public:
    explicit EraseDiskPage( QWidget* parent = nullptr );

    void init( PartitionCoreModule* core );

    bool isNextEnabled() const;

signals:
    void nextStatusChanged( bool );

private:
    void setNextEnabled( bool enabled );
    void doAutopartition( Device* dev );
    void updatePreviews();
    qint64 swapSuggestion( const qint64 availableSpaceB ) const;

    QListView* m_drivesView;
    PartitionCoreModule* m_core;
    QWidget* m_previewFrame;

    QMutex m_previewsMutex;

    bool m_nextEnabled;
};

#endif // ERASEDISKPAGE_H
