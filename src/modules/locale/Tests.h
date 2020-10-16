/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2019-2020, Adriaan de Groot <groot@kde.org>
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

class LocaleTests : public QObject
{
    Q_OBJECT
public:
    LocaleTests();
    ~LocaleTests() override;

private Q_SLOTS:
    void initTestCase();
    // Check the sample config file is processed correctly
    void testEmptyLocaleConfiguration();
    void testDefaultLocaleConfiguration();
    void testSplitLocaleConfiguration();

    // Check the TZ images for consistency
    void testTZImages();  // No overlaps in images
    void testTZLocations();  // No overlaps in locations
    void testSpecificLocations();
};

#endif
