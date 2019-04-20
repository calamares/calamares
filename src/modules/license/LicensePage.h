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

#include <QWidget>
#include <QUrl>

namespace Ui
{
class LicensePage;
}

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

    bool isValid() const { return !m_id.isEmpty(); }

    QString m_id;
    QString m_prettyName;
    QString m_prettyVendor;
    Type m_type;
    QUrl m_url;
    bool m_required;
};

class LicensePage : public QWidget
{
    Q_OBJECT
public:
    explicit LicensePage( QWidget* parent = nullptr );

    void setEntries( const QList< LicenseEntry >& entriesList );

    bool isNextEnabled() const;
signals:
    void nextStatusChanged( bool status );

private:
    Ui::LicensePage* ui;

    bool m_isNextEnabled;
};

#endif //LICENSEPAGE_H
