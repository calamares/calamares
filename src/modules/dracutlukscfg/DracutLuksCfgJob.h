/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2016 Kevin Kofler <kevin.kofler@chello.at>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef DRACUTLUKSCFGJOB_H
#define DRACUTLUKSCFGJOB_H

#include <QObject>
#include <QVariantMap>

#include "CppJob.h"

#include "utils/PluginFactory.h"

#include "DllMacro.h"

class PLUGINDLLEXPORT DracutLuksCfgJob : public Calamares::CppJob
{
    Q_OBJECT

public:
    explicit DracutLuksCfgJob( QObject* parent = nullptr );
    virtual ~DracutLuksCfgJob() override;

    QString prettyName() const override;

    Calamares::JobResult exec() override;

private:
    static const QLatin1String CONFIG_FILE;
    static const char* CONFIG_FILE_HEADER;
    static const char* CONFIG_FILE_CRYPTTAB_KEYFILE_LINE;
    static const char* CONFIG_FILE_CRYPTTAB_LINE;
    static const QLatin1String CONFIG_FILE_SWAPLINE;

    static QString rootMountPoint();
    static QVariantList partitions();
    static bool isRootEncrypted();
    static bool hasUnencryptedSeparateBoot();
    static QString swapOuterUuid();
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( DracutLuksCfgJobFactory )

#endif  // DRACUTLUKSCFGJOB_H
