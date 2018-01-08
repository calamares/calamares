/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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

#ifndef LOCALEPAGE_H
#define LOCALEPAGE_H

#include "Typedefs.h"

#include "LocaleConfiguration.h"

#include <QWidget>

class QComboBox;
class QLabel;
class QPushButton;
class TimeZoneWidget;

class LocalePage : public QWidget
{
    Q_OBJECT
public:
    explicit LocalePage( QWidget* parent = nullptr );
    virtual ~LocalePage();

    void init( const QString& initialRegion,
               const QString& initialZone,
               const QString& localeGenPath );

    QString prettyStatus() const;

    QList< Calamares::job_ptr > createJobs();

    QMap< QString, QString > localesMap();

    void onActivate();

private:
    LocaleConfiguration guessLocaleConfiguration() const;
    QString prettyLCLocale( const QString& localesMap ) const;

    // For the given locale config, return two strings describing
    // the settings for language and numbers.
    std::pair< QString, QString > prettyLocaleStatus( const LocaleConfiguration& ) const;

    void updateGlobalStorage();
    void updateLocaleLabels();

    TimeZoneWidget* m_tzWidget;
    QComboBox* m_regionCombo;
    QComboBox* m_zoneCombo;

    QLabel* m_regionLabel;
    QLabel* m_zoneLabel;
    QLabel* m_localeLabel;
    QPushButton* m_localeChangeButton;
    QLabel* m_formatsLabel;
    QPushButton* m_formatsChangeButton;

    LocaleConfiguration m_selectedLocaleConfiguration;

    QStringList m_localeGenLines;

    bool m_blockTzWidgetSet;
};

#endif // LOCALEPAGE_H
