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

#ifndef PARTITIONSIZECONTROLLER_H
#define PARTITIONSIZECONTROLLER_H

#include <QObject>
#include <QPointer>

class QSpinBox;

class Device;
class Partition;
class PartResizerWidget;

/**
 * Synchronize a PartResizerWidget and a QSpinBox
 */
class PartitionSizeController : public QObject
{
    Q_OBJECT
public:
    explicit PartitionSizeController( QObject* parent = nullptr );
    void setPartResizerWidget( PartResizerWidget* widget );
    void setSpinBox( QSpinBox* spinBox );
    void init( Device* device, Partition* partition );

private:
    QPointer< PartResizerWidget > m_partResizerWidget;
    QPointer< QSpinBox > m_spinBox;
    Device* m_device = nullptr;
    Partition* m_partition = nullptr;
    bool m_updating = false;

    void updateConnections();
    void doUpdateSpinBox();

private Q_SLOTS:
    void updatePartResizerWidget();
    void updateSpinBox();
};

#endif /* PARTITIONSIZECONTROLLER_H */
