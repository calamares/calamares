/* === This file is part of Calamares - <https://github.com/calamares> ===
 * 
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
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

#ifndef GEOIPTESTS_H
#define GEOIPTESTS_H

#include <QObject>

class GeoIPTests : public QObject
{
    Q_OBJECT
public:
    GeoIPTests();
    ~GeoIPTests() override;

private Q_SLOTS:
    void initTestCase();
    void testFixed();
    void testJSON();
    void testJSONalt();
    void testJSONbad();
    void testXML();
    void testXML2();
    void testXMLalt();
    void testXMLbad();
    void testSplitTZ();

    void testGet();
};

#endif
