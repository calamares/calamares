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

#include "PlasmaLnfJob.h"

#include <QDateTime>
#include <QDir>
#include <QProcess>
#include <QStandardPaths>
#include <QThread>

#include <KService>
#include <KServiceTypeTrader>
#include <KPluginLoader>  // Future

#include <Plasma/PluginLoader>  // TODO: port to KPluginLoader

#include "CalamaresVersion.h"
#include "JobQueue.h"
#include "GlobalStorage.h"

#include "utils/Logger.h"

PlasmaLnfJob::PlasmaLnfJob( QObject* parent )
    : Calamares::CppJob( parent )
{
}


PlasmaLnfJob::~PlasmaLnfJob()
{
}


QString
PlasmaLnfJob::prettyName() const
{
    return tr( "Plasma Look-and-Feel Job" );
}

static void _themes_by_service()
{
    KService::List services;
    KServiceTypeTrader* trader = KServiceTypeTrader::self();

    services = trader->query("Plasma/Theme");
    int c = 0;
    for ( const auto s : services )
    {
        cDebug() << "Plasma theme '" << s->name() << '\'';
        c++;
    }
    cDebug() << "Plasma themes by service found" << c;
}

static void _themes_by_kcm()
{
    QString component;
    QList<Plasma::Package> packages;
    QStringList paths;
    const QStringList dataPaths = QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation);

    for (const QString &path : dataPaths) {
        QDir dir(path + "/plasma/look-and-feel");
        paths << dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);
    }

    for (const QString &path : paths) {
        Plasma::Package pkg = Plasma::PluginLoader::self()->loadPackage(QStringLiteral("Plasma/LookAndFeel"));
        pkg.setPath(path);
        pkg.setFallbackPackage(Plasma::Package());
        if (component.isEmpty() || !pkg.filePath(component.toUtf8()).isEmpty()) {
            packages << pkg;
            cDebug() << "Plasma theme '" << pkg.metadata().pluginName() << '\'';
        }
    }
    cDebug() << "Plasma themes by kcm found" << packages.length();
}


Calamares::JobResult
PlasmaLnfJob::exec()
{
    cDebug() << "Plasma Look-and-Feel Job";

    _themes_by_service();
    _themes_by_kcm();

    return Calamares::JobResult::ok();
}


void
PlasmaLnfJob::setConfigurationMap( const QVariantMap& configurationMap )
{
    m_configurationMap = configurationMap;
}

CALAMARES_PLUGIN_FACTORY_DEFINITION( PlasmaLnfJobFactory, registerPlugin<PlasmaLnfJob>(); )
