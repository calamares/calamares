/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef LOCALEPAGE_H
#define LOCALEPAGE_H

#include "LocaleConfiguration.h"

#include "Job.h"
#include "locale/TimeZone.h"

#include <QWidget>

#include <memory>

class QComboBox;
class QLabel;
class QPushButton;

class Config;
class TimeZoneWidget;

class LocalePage : public QWidget
{
    Q_OBJECT
public:
    explicit LocalePage( class Config* config, QWidget* parent = nullptr );
    ~LocalePage() override;

    void onActivate();

private:
    /// @brief Non-owning pointer to the ViewStep's config
    Config* m_config;

    void updateLocaleLabels();

    void regionChanged( int currentIndex );
    void zoneChanged( int currentIndex );
    void locationChanged( const CalamaresUtils::Locale::TimeZoneData* location );
    void changeLocale();
    void changeFormats();

    TimeZoneWidget* m_tzWidget;
    QComboBox* m_regionCombo;
    QComboBox* m_zoneCombo;

    QLabel* m_regionLabel;
    QLabel* m_zoneLabel;
    QLabel* m_localeLabel;
    QPushButton* m_localeChangeButton;
    QLabel* m_formatsLabel;
    QPushButton* m_formatsChangeButton;


    bool m_blockTzWidgetSet;
};

#endif  // LOCALEPAGE_H
