/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2017, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
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
