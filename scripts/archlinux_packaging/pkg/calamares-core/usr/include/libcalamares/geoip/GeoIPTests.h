/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
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
