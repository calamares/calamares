/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef PLASMALNF_CONFIG_H
#define PLASMALNF_CONFIG_H

#include <QObject>

class Config : public QObject
{
    Q_OBJECT

    Q_PROPERTY( QString theme READ theme WRITE setTheme NOTIFY themeChanged )

public:
    Config( QObject* parent = nullptr );
    virtual ~Config() override = default;

    void setConfigurationMap( const QVariantMap& );

    /** @brief Full path to the lookandfeeltool (if it exists)
     *
     * This can be configured, or defaults to `lookandfeeltool` to find
     * it in $PATH.
     */
    QString lnfToolPath() const { return m_lnfPath; }
    /** @brief For OEM mode, the name of the (current) live user
     *
     */
    QString liveUser() const { return m_liveUser; }

    /** @brief The id (in reverse-DNS notation) of the current theme.
     */
    QString theme() const { return m_themeId; }

public slots:
    void setTheme( const QString& id );

signals:
    void themeChanged( const QString& id );

private:
    QString m_lnfPath;  // Path to the lnf tool
    QString m_liveUser;  // Name of the live user (for OEM mode)

    QString m_themeId;  // Id of selected theme
};

#endif
