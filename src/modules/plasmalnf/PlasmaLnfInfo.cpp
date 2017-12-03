/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
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

#include "PlasmaLnfInfo.h"

#include <QDateTime>
#include <QDir>
#include <QProcess>
#include <QStandardPaths>
#include <QThread>

#include <KService>
#include <KServiceTypeTrader>
#include <KPluginLoader>  // Future

#include <Plasma/PluginLoader>  // TODO: port to KPluginLoader
#include <KPackage/Package>
#include <KPackage/PackageLoader>

#include "utils/Logger.h"


namespace Calamares
{

static QString *p_lnfPath = nullptr;

QString lnftool()
{
    if ( !p_lnfPath )
        p_lnfPath = new QString("/usr/bin/lookandfeeltool");

    return *p_lnfPath;
}

void set_lnftool( const QString& lnfPath )
{
    if (p_lnfPath)
        delete p_lnfPath;
    p_lnfPath = new QString( lnfPath );
}

}  // namespace Calamares
