/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef PACKAGECHOOSERTESTS_H
#define PACKAGECHOOSERTESTS_H

#include <QObject>

class PackageChooserTests : public QObject
{
    Q_OBJECT
public:
    PackageChooserTests();
    ~PackageChooserTests() override;

private Q_SLOTS:
    void initTestCase();
    void testBogus();
    void testAppData();
};

#endif
