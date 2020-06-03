/* === This file is part of Calamares - <https://github.com/calamares> ===
 * 
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
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
 *
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *   License-Filename: LICENSE
 *
 */

#ifndef LIBCALAMARES_PARTITION_TESTS_H
#define LIBCALAMARES_PARTITION_TESTS_H

#include <QObject>

class PartitionSizeTests : public QObject
{
    Q_OBJECT
public:
    PartitionSizeTests();
    ~PartitionSizeTests() override;

private Q_SLOTS:
    void initTestCase();

    void testUnitComparison_data();
    void testUnitComparison();

    void testUnitNormalisation_data();
    void testUnitNormalisation();
};

#endif
