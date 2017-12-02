/* === This file is part of Calamares - <http://github.com/calamares> ===
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

#ifndef REQUIREMENTSCHECKER_H
#define REQUIREMENTSCHECKER_H

#include <QObject>
#include <QStringList>

#include "modulesystem/Requirement.h"

class RequirementsChecker : public QObject
{
    Q_OBJECT
public:
    explicit RequirementsChecker( QObject* parent = nullptr );

    void setConfigurationMap( const QVariantMap& configurationMap );

    Calamares::RequirementsList checkRequirements( QWidget* some_widget );

private:
    QStringList m_entriesToCheck;
    QStringList m_entriesToRequire;

    bool checkEnoughStorage( qint64 requiredSpace );
    bool checkEnoughRam( qint64 requiredRam );
    bool checkBatteryExists();
    bool checkHasPower();
    bool checkHasInternet();
    bool checkIsRoot();
    void detectFirmwareType();

    qreal m_requiredStorageGB;
    qreal m_requiredRamGB;
    QString m_checkHasInternetUrl;
};

#endif // REQUIREMENTSCHECKER_H
