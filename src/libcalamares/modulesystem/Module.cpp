/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017-2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#include "Module.h"

#include "CalamaresConfig.h"
#include "Settings.h"

#include "utils/Dirs.h"
#include "utils/Logger.h"
#include "utils/NamedEnum.h"
#include "utils/Yaml.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QString>

static const char EMERGENCY[] = "emergency";

namespace Calamares
{

Module::Module()
    : m_loaded( false )
{
}

Module::~Module() {}

void
Module::initFrom( const Calamares::ModuleSystem::Descriptor& moduleDescriptor, const QString& id )
{
    m_key = ModuleSystem::InstanceKey( moduleDescriptor.name(), id );
    if ( moduleDescriptor.isEmergency() )
    {
        m_maybe_emergency = true;
    }
}

static QStringList
moduleConfigurationCandidates( bool assumeBuildDir, const QString& moduleName, const QString& configFileName )
{
    QStringList paths;

    if ( CalamaresUtils::isAppDataDirOverridden() )
    {
        paths << CalamaresUtils::appDataDir().absoluteFilePath( QString( "modules/%1" ).arg( configFileName ) );
    }
    else
    {
        // If an absolute path is given, in debug mode, look for it
        // first. The case contains('/'), below, will add the absolute
        // path a second time, though.
        if ( assumeBuildDir && configFileName.startsWith( '/' ) )
        {
            paths << configFileName;
        }
        if ( assumeBuildDir )
        {
            paths << QDir().absoluteFilePath( QString( "src/modules/%1/%2" ).arg( moduleName ).arg( configFileName ) );
        }
        if ( assumeBuildDir && configFileName.contains( '/' ) )
        {
            paths << QDir().absoluteFilePath( configFileName );
        }

        if ( CalamaresUtils::haveExtraDirs() )
            for ( auto s : CalamaresUtils::extraConfigDirs() )
            {
                paths << ( s + QString( "modules/%1" ).arg( configFileName ) );
            }

        paths << QString( "/etc/calamares/modules/%1" ).arg( configFileName );
        paths << CalamaresUtils::appDataDir().absoluteFilePath( QString( "modules/%1" ).arg( configFileName ) );
    }

    return paths;
}

void
Module::loadConfigurationFile( const QString& configFileName )  //throws YAML::Exception
{
    QStringList configCandidates
        = moduleConfigurationCandidates( Settings::instance()->debugMode(), name(), configFileName );
    for ( const QString& path : configCandidates )
    {
        QFile configFile( path );
        if ( configFile.exists() && configFile.open( QFile::ReadOnly | QFile::Text ) )
        {
            QByteArray ba = configFile.readAll();

            YAML::Node doc = YAML::Load( ba.constData() );
            if ( doc.IsNull() )
            {
                cWarning() << "Found empty module configuration" << path;
                // Special case: empty config files are valid,
                // but aren't a map.
                return;
            }
            if ( !doc.IsMap() )
            {
                cWarning() << "Bad module configuration format" << path;
                return;
            }

            m_configurationMap = CalamaresUtils::yamlMapToVariant( doc );
            m_emergency = m_maybe_emergency && m_configurationMap.contains( EMERGENCY )
                && m_configurationMap[ EMERGENCY ].toBool();
            return;
        }
    }
    cWarning() << "No config file for" << name() << "found anywhere at" << Logger::DebugList( configCandidates );
}


QString
Module::typeString() const
{
    bool ok = false;
    QString v = Calamares::ModuleSystem::typeNames().find( type(), ok );
    return ok ? v : QString();
}


QString
Module::interfaceString() const
{
    bool ok = false;
    QString v = Calamares::ModuleSystem::interfaceNames().find( interface(), ok );
    return ok ? v : QString();
}


QVariantMap
Module::configurationMap()
{
    return m_configurationMap;
}


RequirementsList
Module::checkRequirements()
{
    return RequirementsList();
}

}  // namespace Calamares
