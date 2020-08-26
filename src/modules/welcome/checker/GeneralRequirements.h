/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2017 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef GENERALREQUIREMENTS_H
#define GENERALREQUIREMENTS_H

#include <QObject>
#include <QStringList>

#include "modulesystem/Requirement.h"

class GeneralRequirements : public QObject
{
    Q_OBJECT
public:
    explicit GeneralRequirements( QObject* parent = nullptr );

    void setConfigurationMap( const QVariantMap& configurationMap );

    Calamares::RequirementsList checkRequirements();

private:
    QStringList m_entriesToCheck;
    QStringList m_entriesToRequire;

    bool checkEnoughStorage( qint64 requiredSpace );
    bool checkEnoughRam( qint64 requiredRam );
    bool checkBatteryExists();
    bool checkHasPower();
    bool checkHasInternet();
    bool checkIsRoot();

    qreal m_requiredStorageGiB;
    qreal m_requiredRamGiB;
};

#endif  // REQUIREMENTSCHECKER_H
