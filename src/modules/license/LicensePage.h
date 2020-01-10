/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2015, Anke Boersma <demm@kaosx.us>
 *   Copyright 2015, Alexandre Arnt <qtgzmanager@gmail.com>
 *   Copyright 2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2018, Adriaan de Groot <groot@kde.org>
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
