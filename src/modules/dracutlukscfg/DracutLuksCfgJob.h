/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2016, Kevin Kofler <kevin.kofler@chello.at>
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

#ifndef DRACUTLUKSCFGJOB_H
#define DRACUTLUKSCFGJOB_H

#include <QObject>
#include <QVariantMap>

#include <CppJob.h>

#include <utils/PluginFactory.h>

#include <PluginDllMacro.h>

class PLUGINDLLEXPORT DracutLuksCfgJob : public Calamares::CppJob
{
    Q_OBJECT

public:
    explicit DracutLuksCfgJob( QObject* parent = nullptr );
    virtual ~DracutLuksCfgJob() override;

    QString prettyName() const override;

    Calamares::JobResult exec() override;

private:
    static const QLatin1Literal CONFIG_FILE;
    static const char *CONFIG_FILE_HEADER;
    static const char *CONFIG_FILE_CRYPTTAB_KEYFILE_LINE;
    static const char *CONFIG_FILE_CRYPTTAB_LINE;
    static const QLatin1Literal CONFIG_FILE_SWAPLINE;

    static QString rootMountPoint();
    static QVariantList partitions();
    static bool isRootEncrypted();
    static bool hasUnencryptedSeparateBoot();
    static QString swapOuterUuid();
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( DracutLuksCfgJobFactory )

#endif // DRACUTLUKSCFGJOB_H
