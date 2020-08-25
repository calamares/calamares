/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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
