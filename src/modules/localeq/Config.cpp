/* === This file is part of Calamares - <https://github.com/calamares> ===
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

#include "Config.h"

#include <QDebug>

#include "SetTimezoneJob.h"
#include "timezonewidget/timezonewidget.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "LCLocaleDialog.h"
#include "Settings.h"

#include "locale/Label.h"
#include "locale/TimeZone.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"
#include "utils/Retranslator.h"


QHash<int, QByteArray>
ZonesModel::roleNames() const
{
    return {{Qt::DisplayRole,"label"}, {Qt::UserRole, "key"}};
}

QVariant
ZonesModel::data(const QModelIndex& index, int role) const
{
    if ( !index.isValid() )
    {
        return QVariant();
    }

    const auto* item = m_zones.at( index.row() );
    return item ? ( role == Qt::DisplayRole ? item->tr() : item->key() ) : QVariant();
}

int
ZonesModel::rowCount(const QModelIndex&) const
{
   return m_zones.count();
}

void
ZonesModel::setZones(const CalamaresUtils::Locale::CStringPairList& zones)
{
    beginResetModel();
    m_zones = zones;
    endResetModel();
}

void
ZonesModel::setZone(const QString& key)
{
    const auto index = indexOf(key);

    if(index >= m_zones.count() || index < 0)
        return;

    m_currentZone = index;
    emit currentZoneChanged();
}

Config::Config(const QString& initialRegion, const QString& initialZone, const QString& localeGenPath, QObject *parent) : QObject(parent)
, m_regionList( CalamaresUtils::Locale::TZRegion::fromZoneTab() )
, m_regionModel( new CalamaresUtils::Locale::CStringListModel ( m_regionList ) )
, m_zonesModel( new ZonesModel(this))
, m_blockTzWidgetSet( false )
{
    using namespace CalamaresUtils::Locale;

    cDebug()<< "REGION MODEL SIZE" << m_regionModel->rowCount(QModelIndex()) << m_regionList.size();
//     auto* region = m_regionList.find< TZRegion >( initialRegion );
//     if ( region && region->zones().find< TZZone >( initialZone ) )
//     {
//         this->m_zonesModel->setZones(region->zones());
//         this->m_zonesModel->setZone(initialZone);
//     }
//     else
//     {
        this->m_zonesModel->setZones(m_regionList.find< TZRegion >( "America" )->zones());
        this->m_zonesModel->setZone("New_York");
//     }

}

ZonesModel * Config::zonesModel() const
{
    return m_zonesModel;
}

CalamaresUtils::Locale::CStringListModel *
Config::regionModel() const
{
    return m_regionModel;
}

void
Config::setCurrentRegion(const int &index)
{
    if(index >= m_regionModel->rowCount(QModelIndex()) || index < 0)
        return;

    m_currentRegion = index;
    emit currentRegionChanged();

    using namespace CalamaresUtils::Locale;
   const auto zoneKey=  this->m_regionModel->data(m_regionModel->index(index, 0), Qt::UserRole).toString();

   cDebug() << "REGIONS" << zoneKey << index;

   if(auto region = m_regionList.find< TZRegion >(zoneKey))
       m_zonesModel->setZones(region->zones());
}

int
Config::currentRegion() const
{
    return m_currentRegion;
}


