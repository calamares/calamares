/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef LIBCALAMARES_NETWORK_TESTS_H
#define LIBCALAMARES_NETWORK_TESTS_H

#include <QObject>

class NetworkTests : public QObject
{
    Q_OBJECT
public:
    NetworkTests();
    ~NetworkTests() override;

private Q_SLOTS:
    void initTestCase();

    void testInstance();
    void testPing();

    void testCheckUrl();
    void testCheckMultiUrl();
};

#endif
