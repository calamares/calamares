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

#ifndef LOCALE_CONFIG_H
#define LOCALE_CONFIG_H

#include <QObject>
#include <QUrl>
#include <QAbstractListModel>
#include "Job.h"
#include "locale/TimeZone.h"
#include "LocaleConfiguration.h"
#include "timezonewidget/localeglobal.h"
#include <memory>

class ZonesModel : public QAbstractListModel
{
    Q_OBJECT
    using QAbstractListModel::QAbstractListModel;
    Q_PROPERTY(int currentZone READ currentZone WRITE setCurrentZone NOTIFY currentZoneChanged)

public:
    void setZones( const CalamaresUtils::Locale::CStringPairList &zones );
    void setZone( const QString &key);
    int rowCount(const QModelIndex&) const override;
    QVariant data(const QModelIndex& index, int role) const override;

    const CalamaresUtils::Locale::CStringPair *item(const int &index) const;

    inline int indexOf(const QString &key)
    {
        const auto it = std::find_if(m_zones.constBegin(), m_zones.constEnd(), [&](const  CalamaresUtils::Locale::CStringPair *item) -> bool
        {
            return item->key() == key;

        });

        if(it != m_zones.constEnd())
            return std::distance(m_zones.constBegin(), it);
        else return -1;
    }

    const CalamaresUtils::Locale::TZZone* currentLocation();

    void setCurrentZone(const int &index);
    int currentZone() const;

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    CalamaresUtils::Locale::CStringPairList m_zones;
    int m_currentZone = -1;


signals:
    void currentZoneChanged();
};


class Config : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ZonesModel * zonesModel READ zonesModel CONSTANT FINAL)
    Q_PROPERTY(int currentRegion READ currentRegion WRITE setCurrentRegion NOTIFY currentRegionChanged)
    Q_PROPERTY(CalamaresUtils::Locale::CStringListModel * regionModel READ regionModel CONSTANT FINAL)

public:
    Config( QObject* parent = nullptr );
    ~Config();
    CalamaresUtils::Locale::CStringListModel* regionModel() const;

    void setLocaleInfo(const QString& initialRegion, const QString& initialZone, const QString& localeGenPath);

    void setCurrentRegion(const int &index);
    int currentRegion() const;

    ZonesModel * zonesModel() const;

    Calamares::JobList createJobs();
    QMap< QString, QString > localesMap();

    QString prettyStatus() const;

private:
    CalamaresUtils::Locale::CStringPairList m_regionList;
    CalamaresUtils::Locale::CStringListModel * m_regionModel;
    ZonesModel * m_zonesModel;

    LocaleConfiguration m_selectedLocaleConfiguration;

    QStringList m_localeGenLines;
    int m_currentRegion = -1;

    bool m_blockTzWidgetSet;

    LocaleConfiguration guessLocaleConfiguration() const;

    // For the given locale config, return two strings describing
    // the settings for language and numbers.
    std::pair< QString, QString > prettyLocaleStatus( const LocaleConfiguration& ) const;

    /** @brief Update the GS *locale* key with the selected system language.
     *
     * This uses whatever is set in m_selectedLocaleConfiguration as the language,
     * and writes it to GS *locale* key (as a string, in BCP47 format).
     */
    void updateGlobalLocale();
    void updateGlobalStorage();
    void updateLocaleLabels();

signals:
    void currentRegionChanged();
};


#endif
