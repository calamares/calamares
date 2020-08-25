/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2015 Anke Boersma <demm@kaosx.us>
 *   SPDX-FileCopyrightText: 2015 Alexandre Arnt <qtgzmanager@gmail.com>
 *   SPDX-FileCopyrightText: 2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef LICENSEPAGE_H
#define LICENSEPAGE_H

#include "utils/NamedEnum.h"

#include <QUrl>
#include <QWidget>

namespace Ui
{
class LicensePage;
}

class LicenseWidget;

struct LicenseEntry
{
    enum class Type
    {
        Software = 0,
        Driver,
        GpuDriver,
        BrowserPlugin,
        Codec,
        Package
    };

    /// @brief Lookup table for the enums
    const NamedEnumTable< Type >& typeNames();

    LicenseEntry( const QVariantMap& conf );
    LicenseEntry( const LicenseEntry& ) = default;
    LicenseEntry& operator=( const LicenseEntry& ) = default;

    bool isValid() const { return !m_id.isEmpty(); }
    bool isRequired() const { return m_required; }
    bool isLocal() const;
    bool expandByDefault() const { return m_expand; }

    QString m_id;
    QString m_prettyName;
    QString m_prettyVendor;
    Type m_type = Type::Software;
    QUrl m_url;
    bool m_required = false;
    bool m_expand = false;
};

class LicensePage : public QWidget
{
    Q_OBJECT
public:
    explicit LicensePage( QWidget* parent = nullptr );

    void setEntries( const QList< LicenseEntry >& entriesList );

    bool isNextEnabled() const;

public slots:
    /** @brief Check if the user can continue
     *
     * The user can continue if
     *  - none of the licenses are required, or
     *  - the user has ticked the "OK" box.
     * This function calls updateGlobalStorage() as needed, and updates
     * the appearance of the page as needed. @p checked indicates whether
     * the checkbox has been ticked or not. (e.g. when @p checked is true,
     * you can continue regardless)
     */
    void checkAcceptance( bool checked );

    void retranslate();

signals:
    void nextStatusChanged( bool status );

private:
    /** @brief Update the global storage "licenseAgree" key. */
    void updateGlobalStorage( bool v );

    bool m_isNextEnabled;
    bool m_allLicensesOptional;  ///< @brief all the licenses passed to setEntries are not-required

    Ui::LicensePage* ui;
    QList< LicenseWidget* > m_entries;
};

#endif  //LICENSEPAGE_H
