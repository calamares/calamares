/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
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

#ifndef PARTITIONSIZEWIDGET_H
#define PARTITIONSIZEWIDGET_H

#include <QSpinBox>

class Device;
class Partition;

class PartitionSizeWidget : public QSpinBox
{
public:
    typedef QPair< qint64, qint64 > SectorRange;

    explicit PartitionSizeWidget( QWidget* parent = nullptr );
    void init( Device* device, Partition* partition );

    SectorRange sectorRange() const;

    bool isDirty() const;

private:
    Device* m_device = nullptr;
    Partition* m_partition = nullptr;
    int m_initialValue;

    qint64 mbSizeForSectorRange( qint64 first, qint64 last ) const;

    qint64 computeMinSector() const;
    qint64 computeMaxSector() const;
};

#endif /* PARTITIONSIZEWIDGET_H */
