/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef PLASMALNF_CONFIG_H
#define PLASMALNF_CONFIG_H

#include <QObject>

class Config : public QObject
{
    Q_OBJECT

public:
    Config( QObject* parent = nullptr );
    virtual ~Config() override = default;

    void setConfigurationMap( const QVariantMap& );
};

#endif
