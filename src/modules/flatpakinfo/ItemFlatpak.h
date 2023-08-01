/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef ITEMFLATPAK_H
#define ITEMFLATPAK_H

#include <QString>
#include <QVector>
#include <QVariant>

class PackageItem
{
public:
    PackageItem(QString appstreamid):
       appstreamid(appstreamid),
       installed(false)
    {

    }
    QString& getAppStreamId(void)
    {
        return this->appstreamid;
    }
    void setInstalled(bool installed)
    {
        this->installed = installed;
    }
    bool getInstalled(void)
    {
        return this->installed;
    }
private:
    QString appstreamid;
    bool installed;
};



PackageItem fromFlatpak( const QVariantMap& map );

#endif
