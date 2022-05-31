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

class ShellProcessTests : public QObject
{
    Q_OBJECT
public:
    ShellProcessTests();
    ~ShellProcessTests() override;

private Q_SLOTS:
    void initTestCase();
    // Check the sample config file is processed correctly
    void testProcessListSampleConfig();
    // Create from a YAML list
    void testProcessListFromList();
    // Create from a simple YAML string
    void testProcessListFromString();
    // Create from a single complex YAML
    void testProcessFromObject();
    // Create from a complex YAML list
    void testProcessListFromObject();
    // Check variable substitution
    void testRootSubstitution();
};

#endif
