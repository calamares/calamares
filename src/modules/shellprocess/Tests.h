/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2018, Adriaan de Groot <groot@kde.org>
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
};

#endif
