/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef TESTS_H
#define TESTS_H

#include <QObject>

class ContextualProcessTests : public QObject
{
    Q_OBJECT
public:
    ContextualProcessTests();
    ~ContextualProcessTests() override;

private Q_SLOTS:
    void initTestCase();
    // Check the sample config file is processed correctly
    void testProcessListSampleConfig();

    // Variable binding lookup
    void testFetch();
};

#endif
