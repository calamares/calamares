/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2015, Anke Boersma <demm@kaosx.us>
 *   Copyright 2015, Alexandre Arnt <qtgzmanager@gmail.com>
 *   Copyright 2015, Teo Mrnjavac <teo@kde.org>
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

#include <QWidget>
#include <QUrl>

namespace Ui
{
class LicensePage;
}

struct LicenseEntry
{
    enum Type
    {
        Software = 0,
        Driver,
        GpuDriver,
        BrowserPlugin,
        Codec,
        Package
    };

    QString id;
    QString prettyName;
    QString prettyVendor;
    Type type;
    QUrl url;
    bool required;
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
