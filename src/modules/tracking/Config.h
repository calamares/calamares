/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef TRACKING_CONFIG_H
#define TRACKING_CONFIG_H

#include <QObject>
#include <QString>
#include <QVariantMap>

/** @brief Base class for configuring a specific kind of tracking.
 *
 * All tracking types have a policy URL, which is used to explain what
 * kind of tracking is involved, what data is sent, etc. The content
 * of that URL is the responsibility of the distro.
 *
 * A tracking type is disabled by default: if it isn't specifically
 * enabled (for configuration) in the config file, it will always be disabled.
 * If it is enabled (for configuration) in the config file, it still
 * defaults to disabled, but the user can choose to enable it.
 */
class TrackingStyleConfig : public QObject
{
    Q_OBJECT

    Q_PROPERTY( TrackingState trackingStatus READ tracking WRITE setTracking NOTIFY trackingChanged FINAL )
    Q_PROPERTY( bool isEnabled READ isEnabled NOTIFY trackingChanged FINAL )
    Q_PROPERTY( bool isConfigurable READ isConfigurable NOTIFY trackingChanged FINAL )
    Q_PROPERTY( QString policy READ policy NOTIFY policyChanged FINAL )

public:
    TrackingStyleConfig( QObject* parent );
    ~TrackingStyleConfig() override;

    void setConfigurationMap( const QVariantMap& );

    enum TrackingState
    {
        DisabledByConfig,
        DisabledByUser,
        EnabledByUser
    };
    Q_ENUM( TrackingState )

public Q_SLOTS:
    TrackingState tracking() const { return m_state; }
    /// @brief Has the user specifically enabled this kind of tracking?
    bool isEnabled() const { return m_state == EnabledByUser; }
    /// @brief Is this tracking enabled for configuration?
    bool isConfigurable() const { return m_state != DisabledByConfig; }
    /** @brief Sets the tracking state
     *
     * Unless the tracking is enabled for configuration, it always
     * remains disabled.
     */
    void setTracking( TrackingState );
    /** @brief Sets the tracking state
     *
     * Use @c true for @c EnabledByUser, @c false for DisabledByUser,
     * but keep in mind that if the tracking is not enabled for
     * configuration, it will always remain disabled.
     */
    void setTracking( bool );

    /// @brief URL for the policy explaining this tracking
    QString policy() const { return m_policy; }

signals:
    void trackingChanged();
    void policyChanged( QString );

protected:
    /// @brief Validates the @p urlString, disables tracking if invalid
    void validateUrl( QString& urlString );
    /// @brief Validates the @p string, disables tracking if invalid
    void validate( QString& s, std::function< bool( const QString& s ) >&& pred );

private:
    TrackingState m_state = DisabledByConfig;
    QString m_policy;  // URL
};

/** @brief Install tracking pings a URL at the end of installation
 *
 * Install tracking will do a single GET on the given URL at
 * the end of installation. The information included in the GET
 * request depends on the URL configuration, see also the tracking
 * jobs.
 */
class InstallTrackingConfig : public TrackingStyleConfig
{
public:
    InstallTrackingConfig( QObject* parent );
    ~InstallTrackingConfig() override;
    void setConfigurationMap( const QVariantMap& configurationMap );

    QString installTrackingUrl() { return m_installTrackingUrl; }

private:
    QString m_installTrackingUrl;
};

/** @brief Machine tracking reports from the installed system
 *
 * When machine tracking is on, the installed system will report
 * back ("call home") at some point. This can mean Debian pop-con,
 * or updatemanager maching tracking, or something else. The kind
 * of configuration depends on the style of tracking that is enabled.
 */
class MachineTrackingConfig : public TrackingStyleConfig
{
public:
    MachineTrackingConfig( QObject* parent );
    ~MachineTrackingConfig() override;
    void setConfigurationMap( const QVariantMap& configurationMap );

    QString machineTrackingStyle() { return m_machineTrackingStyle; }

private:
    QString m_machineTrackingStyle;
};

/** @brief User tracking reports user actions
 *
 * When user tracking is on, it is enabled for the user configured
 * in Calamares -- not for users created afterwards in the target
 * system, unless the target system defaults to tracking them.
 * The kind of user tracking depends on the target system and
 * environment; KDE user tracking is one example, which can be
 * configured in a fine-grained way and defaults to off.
 */
class UserTrackingConfig : public TrackingStyleConfig
{
public:
    UserTrackingConfig( QObject* parent );
    ~UserTrackingConfig() override;
    void setConfigurationMap( const QVariantMap& configurationMap );

    QString userTrackingStyle() { return m_userTrackingStyle; }
    QStringList userTrackingAreas() const { return m_userTrackingAreas; }

private:
    QString m_userTrackingStyle;
    QStringList m_userTrackingAreas;  // fine-grained areas
};

class Config : public QObject
{
    Q_OBJECT
    Q_PROPERTY( QString generalPolicy READ generalPolicy NOTIFY generalPolicyChanged FINAL )
    Q_PROPERTY( TrackingStyleConfig* installTracking READ installTracking FINAL )
    Q_PROPERTY( TrackingStyleConfig* machineTracking READ machineTracking FINAL )
    Q_PROPERTY( TrackingStyleConfig* userTracking READ userTracking FINAL )

public:
    Config( QObject* parent = nullptr );
    void setConfigurationMap( const QVariantMap& );

public Q_SLOTS:
    QString generalPolicy() const;

    InstallTrackingConfig* installTracking() const { return m_installTracking; }
    MachineTrackingConfig* machineTracking() const { return m_machineTracking; }
    UserTrackingConfig* userTracking() const { return m_userTracking; }

    /// @brief Call with @c true to turn off all the trackings
    void noTracking( bool );

signals:
    void generalPolicyChanged( QString );

private:
    QString m_generalPolicy;

    InstallTrackingConfig* m_installTracking;
    MachineTrackingConfig* m_machineTracking;
    UserTrackingConfig* m_userTracking;
};

#endif
