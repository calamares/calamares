/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019-2020, Adriaan de Groot <groot@kde.org>
 *   Copyright 2020, Camilo Higuita <milo.h@aol.com>
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

#include "LocaleConfiguration.h"

#include "Job.h"
#include "locale/TimeZone.h"

#include <QAbstractListModel>
#include <QObject>

#include <memory>

class Config : public QObject
{
    Q_OBJECT
    Q_PROPERTY( CalamaresUtils::Locale::CStringListModel* zonesModel READ zonesModel CONSTANT FINAL )
    Q_PROPERTY( CalamaresUtils::Locale::CStringListModel* regionModel READ regionModel CONSTANT FINAL )
    Q_PROPERTY( QString prettyStatus READ prettyStatus NOTIFY prettyStatusChanged FINAL )

public:
    Config( QObject* parent = nullptr );
    ~Config();
    CalamaresUtils::Locale::CStringListModel* regionModel() const;
    CalamaresUtils::Locale::CStringListModel* zonesModel() const;

    void setLocaleInfo( const QString& initialRegion, const QString& initialZone, const QString& localeGenPath );

    Calamares::JobList createJobs();
    QMap< QString, QString > localesMap();
    QString prettyStatus() const;

private:
    CalamaresUtils::Locale::CStringPairList m_regionList;
    CalamaresUtils::Locale::CStringListModel* m_regionModel;
    CalamaresUtils::Locale::CStringListModel* m_zonesModel;

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

    const CalamaresUtils::Locale::TZZone* currentLocation() const;

signals:
    void prettyStatusChanged();
};


#endif
