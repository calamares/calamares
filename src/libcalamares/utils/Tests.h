/* === This file is part of Calamares - <https://github.com/calamares> ===
 * 
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *
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

#ifndef TESTS_H
#define TESTS_H

#include <QObject>

class LibCalamaresTests : public QObject
{
    Q_OBJECT
public:
    LibCalamaresTests();
    ~LibCalamaresTests() override;

private Q_SLOTS:
    void initTestCase();
    void testDebugLevels();

    void testLoadSaveYaml();  // Just settings.conf
    void testLoadSaveYamlExtended();  // Do a find() in the src dir

    void testCommands();

    /** @brief Test that all the UMask objects work correctly. */
    void testUmask();

    /** @brief Tests the entropy functions. */
    void testEntropy();
    void testPrintableEntropy();
    void testOddSizedPrintable();

private:
    void recursiveCompareMap( const QVariantMap& a, const QVariantMap& b, int depth );
};

#endif
