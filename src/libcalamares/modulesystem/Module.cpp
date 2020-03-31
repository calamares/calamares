/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017-2018, Adriaan de Groot <groot@kde.org>
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
    m_key = ModuleSystem::InstanceKey( moduleDescriptor.value( "name" ).toString(), id );
    if ( moduleDescriptor.contains( EMERGENCY ) )
    {
        m_maybe_emergency = moduleDescriptor[ EMERGENCY ].toBool();
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
                cDebug() << "Found empty module configuration" << path;
                // Special case: empty config files are valid,
                // but aren't a map.
                return;
            }
            if ( !doc.IsMap() )
            {
                cWarning() << "Bad module configuration format" << path;
                return;
            }

            cDebug() << "Loaded module configuration" << path;
            m_configurationMap = CalamaresUtils::yamlMapToVariant( doc );
            m_emergency = m_maybe_emergency && m_configurationMap.contains( EMERGENCY )
                && m_configurationMap[ EMERGENCY ].toBool();
            return;
        }
    }
    cDebug() << "No config file for" << name() << "found anywhere at" << Logger::DebugList( configCandidates );
}


static const NamedEnumTable< Module::Type >&
typeNames()
{
    using Type = Module::Type;
    // *INDENT-OFF*
    // clang-format off
    static const NamedEnumTable< Type > table{
        { QStringLiteral( "job" ), Type::Job },
        { QStringLiteral( "view" ), Type::View },
        { QStringLiteral( "viewmodule" ), Type::View },
        { QStringLiteral( "jobmodule" ), Type::Job }
    };
    // *INDENT-ON*
    // clang-format on
    return table;
}

QString
Module::typeString() const
{
    bool ok = false;
    QString v = typeNames().find( type(), ok );
    return ok ? v : QString();
}


static const NamedEnumTable< Module::Interface >&
interfaceNames()
{
    using Interface = Module::Interface;
    // *INDENT-OFF*
    // clang-format off
    static const NamedEnumTable< Interface > table {
        { QStringLiteral("process"), Interface::Process },
        { QStringLiteral("qtplugin"), Interface::QtPlugin },
        { QStringLiteral("python"), Interface::Python },
        { QStringLiteral("pythonqt"), Interface::PythonQt }
    };
    // *INDENT-ON*
    // clang-format on
    return table;
}

QString
Module::interfaceString() const
{
    bool ok = false;
    QString v = interfaceNames().find( interface(), ok );
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
