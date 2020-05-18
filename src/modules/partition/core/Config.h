/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2020, Adriaan de Groot <groot@kde.org>
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

#ifndef PARTITION_CONFIG_H
#define PARTITION_CONFIG_H

#include "core/PartitionActions.h"

#include <QObject>
#include <QSet>

class Config : public QObject
{
    Q_OBJECT

public:
    Config( QObject* parent );
    virtual ~Config() = default;

    void setConfigurationMap( const QVariantMap& );

    void updateGlobalStorage() const;

private:
    PartitionActions::Choices::SwapChoiceSet m_swapChoices;
    qreal m_requiredStorageGiB = 0.0;  // May duplicate setting in the welcome module
};


#endif
