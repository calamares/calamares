/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef LOCALE_CONFIG_H
#define LOCALE_CONFIG_H

#include "LocaleConfiguration.h"

#include "Job.h"
#include "geoip/Handler.h"
#include "geoip/Interface.h"
#include "locale/TimeZone.h"

#include <QFutureWatcher>
#include <QObject>

#include <memory>

class Config : public QObject
{
    Q_OBJECT
    Q_PROPERTY( const QStringList& supportedLocales READ supportedLocales CONSTANT FINAL )
    Q_PROPERTY( CalamaresUtils::Locale::RegionsModel* regionModel READ regionModel CONSTANT FINAL )
    Q_PROPERTY( CalamaresUtils::Locale::ZonesModel* zonesModel READ zonesModel CONSTANT FINAL )
    Q_PROPERTY( QAbstractItemModel* regionalZonesModel READ regionalZonesModel CONSTANT FINAL )

    Q_PROPERTY(
        CalamaresUtils::Locale::TimeZoneData* currentLocation READ currentLocation_c NOTIFY currentLocationChanged )

    // Status are complete, human-readable, messages
    Q_PROPERTY( QString currentLocationStatus READ currentLocationStatus NOTIFY currentLanguageStatusChanged )
    Q_PROPERTY( QString currentLanguageStatus READ currentLanguageStatus NOTIFY currentLanguageStatusChanged )
    Q_PROPERTY( QString currentLCStatus READ currentLCStatus NOTIFY currentLCStatusChanged )
    // Name are shorter human-readable names
    //   .. main difference is that status is a full sentence, like "Timezone is America/New York"
    //      while name is just "America/New York" (and the code, below, is "America/New_York")
    Q_PROPERTY( QString currentTimezoneName READ currentTimezoneName NOTIFY currentTimezoneNameChanged )
    // Code are internal identifiers, like "en_US.UTF-8"
    Q_PROPERTY( QString currentTimezoneCode READ currentTimezoneCode NOTIFY currentTimezoneCodeChanged )
    Q_PROPERTY( QString currentLanguageCode READ currentLanguageCode WRITE setLanguageExplicitly NOTIFY
                    currentLanguageCodeChanged )
    Q_PROPERTY( QString currentLCCode READ currentLCCode WRITE setLCLocaleExplicitly NOTIFY currentLCCodeChanged )

    // This is a long human-readable string with all three statuses
    Q_PROPERTY( QString prettyStatus READ prettyStatus NOTIFY prettyStatusChanged FINAL )

public:
    Config( QObject* parent = nullptr );
    ~Config() override;

    void setConfigurationMap( const QVariantMap& );
    void finalizeGlobalStorage() const;
    Calamares::JobList createJobs();

    /// locale configuration (LC_* and LANG) based solely on the current location.
    LocaleConfiguration automaticLocaleConfiguration() const;
    /// locale configuration that takes explicit settings into account
    LocaleConfiguration localeConfiguration() const;

    /// The human-readable description of what timezone is used
    QString currentLocationStatus() const;
    /// The human-readable description of what language is used
    QString currentLanguageStatus() const;
    /// The human-readable description of what locale (LC_*) is used
    QString currentLCStatus() const;

    /// The human-readable summary of what the module will do
    QString prettyStatus() const;

    // A long list of locale codes (e.g. en_US.UTF-8)
    const QStringList& supportedLocales() const { return m_localeGenLines; }
    // All the regions (Africa, America, ...)
    CalamaresUtils::Locale::RegionsModel* regionModel() const { return m_regionModel.get(); }
    // All of the timezones in the world, according to zone.tab
    CalamaresUtils::Locale::ZonesModel* zonesModel() const { return m_zonesModel.get(); }
    // This model can be filtered by region
    CalamaresUtils::Locale::RegionalZonesModel* regionalZonesModel() const { return m_regionalZonesModel.get(); }

    const CalamaresUtils::Locale::TimeZoneData* currentLocation() const { return m_currentLocation; }


    /// Special case, set location from starting timezone if not already set
    void setCurrentLocation();

private:
    CalamaresUtils::Locale::TimeZoneData* currentLocation_c() const
    {
        return const_cast< CalamaresUtils::Locale::TimeZoneData* >( m_currentLocation );
    }

public Q_SLOTS:
    /// Set the language, but do not mark it as user-choice
    void setLanguage( const QString& language );
    /// Set a language by user-choice, overriding future location changes
    void setLanguageExplicitly( const QString& language );
    /// Set LC (formats) by user-choice, overriding future location changes
    void setLCLocaleExplicitly( const QString& locale );

    /** @brief Sets a location by full name
     *
     * @p regionzone should be an identifier from zone.tab, e.g. "Africa/Abidjan",
     * which is split into regon and zone. Invalid names will **not**
     * change the actual location.
     */
    void setCurrentLocation( const QString& regionzone );
    /** @brief Sets a location by split name
     *
     * @p region should be "America" or the like, while @p zone
     * names a zone within that region.
     */
    void setCurrentLocation( const QString& region, const QString& zone );

    /** @brief Sets a location by pointer to zone data.
     *
     */
    void setCurrentLocation( const CalamaresUtils::Locale::TimeZoneData* tz );

    QString currentLanguageCode() const { return localeConfiguration().language(); }
    QString currentLCCode() const { return localeConfiguration().lc_numeric; }
    QString currentTimezoneName() const;  // human-readable
    QString currentTimezoneCode() const;

signals:
    void currentLocationChanged( const CalamaresUtils::Locale::TimeZoneData* location ) const;
    void currentLocationStatusChanged( const QString& ) const;
    void currentLanguageStatusChanged( const QString& ) const;
    void currentLCStatusChanged( const QString& ) const;
    void prettyStatusChanged( const QString& ) const;
    void currentLanguageCodeChanged( const QString& ) const;
    void currentLCCodeChanged( const QString& ) const;
    void currentTimezoneCodeChanged( const QString& ) const;
    void currentTimezoneNameChanged( const QString& ) const;

private:
    /// A list of supported locale identifiers (e.g. "en_US.UTF-8")
    QStringList m_localeGenLines;

    /// The regions (America, Asia, Europe ..)
    std::unique_ptr< CalamaresUtils::Locale::RegionsModel > m_regionModel;
    std::unique_ptr< CalamaresUtils::Locale::ZonesModel > m_zonesModel;
    std::unique_ptr< CalamaresUtils::Locale::RegionalZonesModel > m_regionalZonesModel;

    const CalamaresUtils::Locale::TimeZoneData* m_currentLocation = nullptr;

    /** @brief Specific locale configurations
     *
     * "Automatic" locale configuration based on the location (e.g.
     * Europe/Amsterdam means Dutch language and Dutch locale) leave
     * this empty; if the user explicitly sets something, then
     * this configuration is non-empty and takes precedence over the
     * automatic location settings (so a user in Amsterdam can still
     * pick Ukranian settings, for instance).
     */
    LocaleConfiguration m_selectedLocaleConfiguration;

    /** @brief Should we adjust the "live" timezone when the location changes?
     *
     * In the Widgets UI, clicking around on the world map adjusts the
     * timezone, and the live system can be made to follow that.
     */
    bool m_adjustLiveTimezone;

    /** @brief The initial timezone (region, zone) specified in the config.
     *
     * This may be overridden by setting *useSystemTimezone* or by
     * GeoIP settings.
     */
    CalamaresUtils::GeoIP::RegionZonePair m_startingTimezone;

    /** @brief Handler for GeoIP lookup (if configured)
     *
     * The GeoIP lookup needs to be started at some suitable time,
     * by explicitly calling *TODO*
     */
    std::unique_ptr< CalamaresUtils::GeoIP::Handler > m_geoip;

    // Implementation details for doing GeoIP lookup
    void startGeoIP();
    void completeGeoIP();
    std::unique_ptr< QFutureWatcher< CalamaresUtils::GeoIP::RegionZonePair > > m_geoipWatcher;
};


#endif
