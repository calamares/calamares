/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2019 Gabriel Craciunescu <crazy@frugalware.org>
 *   SPDX-FileCopyrightText: 2019 Dominic Hayes <ferenosdev@outlook.com>
 *   SPDX-FileCopyrightText: 2017-2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#include "Settings.h"

#include "CalamaresConfig.h"
#include "utils/Dirs.h"
#include "utils/Logger.h"
#include "utils/Yaml.h"

#include <QDir>
#include <QFile>
#include <QPair>

static bool
hasValue( const YAML::Node& v )
{
    return v.IsDefined() && !v.IsNull();
}

/** @brief Helper function to grab a QString out of the config, and to warn if not present. */
static QString
requireString( const YAML::Node& config, const char* key )
{
    auto v = config[ key ];
    if ( hasValue( v ) )
    {
        return QString::fromStdString( v.as< std::string >() );
    }
    else
    {
        cWarning() << Logger::SubEntry << "Required settings.conf key" << key << "is missing.";
        return QString();
    }
}

/** @brief Helper function to grab a bool out of the config, and to warn if not present. */
static bool
requireBool( const YAML::Node& config, const char* key, bool d )
{
    auto v = config[ key ];
    if ( hasValue( v ) )
    {
        return v.as< bool >();
    }
    else
    {
        cWarning() << Logger::SubEntry << "Required settings.conf key" << key << "is missing.";
        return d;
    }
}

namespace Calamares
{

InstanceDescription::InstanceDescription( const Calamares::ModuleSystem::InstanceKey& key )
    : m_instanceKey( key )
    , m_weight( -1 )
{
    if ( !isValid() )
    {
        m_weight = 0;
    }
    else
    {
        m_configFileName = key.module() + QStringLiteral( ".conf" );
    }
}

InstanceDescription
InstanceDescription::fromSettings( const QVariantMap& m )
{
    InstanceDescription r(
        Calamares::ModuleSystem::InstanceKey( m.value( "module" ).toString(), m.value( "id" ).toString() ) );
    if ( r.isValid() )
    {
        if ( m.value( "weight" ).isValid() )
        {
            int w = qBound( 1, m.value( "weight" ).toInt(), 100 );
            r.m_weight = w;
        }

        QString c = m.value( "config" ).toString();
        if ( !c.isEmpty() )
        {
            r.m_configFileName = c;
        }
    }
    return r;
}

Settings* Settings::s_instance = nullptr;

Settings*
Settings::instance()
{
    if ( !s_instance )
    {
        cWarning() << "Getting nullptr Settings instance.";
    }
    return s_instance;
}

static void
interpretModulesSearch( const bool debugMode, const QStringList& rawPaths, QStringList& output )
{
    for ( const auto& path : rawPaths )
    {
        if ( path == "local" )
        {
            // If we're running in debug mode, we assume we might also be
            // running from the build dir, so we add a maximum priority
            // module search path in the build dir.
            if ( debugMode )
            {
                QString buildDirModules
                    = QDir::current().absolutePath() + QDir::separator() + "src" + QDir::separator() + "modules";
                if ( QDir( buildDirModules ).exists() )
                {
                    output.append( buildDirModules );
                }
            }

            // Install path is set in CalamaresAddPlugin.cmake
            output.append( CalamaresUtils::systemLibDir().absolutePath() + QDir::separator() + "calamares"
                           + QDir::separator() + "modules" );
        }
        else
        {
            QDir d( path );
            if ( d.exists() && d.isReadable() )
            {
                output.append( d.absolutePath() );
            }
            else
            {
                cDebug() << Logger::SubEntry << "module-search entry non-existent" << path;
            }
        }
    }
}

static void
interpretInstances( const YAML::Node& node, Settings::InstanceDescriptionList& customInstances )
{
    // Parse the custom instances section
    if ( node )
    {
        QVariant instancesV = CalamaresUtils::yamlToVariant( node ).toList();
        if ( instancesV.type() == QVariant::List )
        {
            const auto instances = instancesV.toList();
            for ( const QVariant& instancesVListItem : instances )
            {
                if ( instancesVListItem.type() != QVariant::Map )
                {
                    continue;
                }
                auto description = InstanceDescription::fromSettings( instancesVListItem.toMap() );
                if ( !description.isValid() )
                {
                    cWarning() << "Invalid entry in *instances*" << instancesVListItem;
                }
                // Append it **anyway**, since this will bail out after Settings is constructed
                customInstances.append( description );
            }
        }
    }
}

static void
interpretSequence( const YAML::Node& node, Settings::ModuleSequence& moduleSequence )
{
    // Parse the modules sequence section
    if ( node )
    {
        QVariant sequenceV = CalamaresUtils::yamlToVariant( node );
        if ( !( sequenceV.type() == QVariant::List ) )
        {
            throw YAML::Exception( YAML::Mark(), "sequence key does not have a list-value" );
        }

        const auto sequence = sequenceV.toList();
        for ( const QVariant& sequenceVListItem : sequence )
        {
            if ( sequenceVListItem.type() != QVariant::Map )
            {
                continue;
            }
            QString thisActionS = sequenceVListItem.toMap().firstKey();
            ModuleSystem::Action thisAction;
            if ( thisActionS == "show" )
            {
                thisAction = ModuleSystem::Action::Show;
            }
            else if ( thisActionS == "exec" )
            {
                thisAction = ModuleSystem::Action::Exec;
            }
            else
            {
                cDebug() << "Unknown action in *sequence*" << thisActionS;
                continue;
            }

            QStringList thisActionRoster = sequenceVListItem.toMap().value( thisActionS ).toStringList();
            Calamares::ModuleSystem::InstanceKeyList roster;
            roster.reserve( thisActionRoster.count() );
            for ( const auto& s : thisActionRoster )
            {
                auto instanceKey = Calamares::ModuleSystem::InstanceKey::fromString( s );
                if ( !instanceKey.isValid() )
                {
                    cWarning() << "Invalid instance in *sequence*" << s;
                }
                roster.append( instanceKey );
            }
            moduleSequence.append( qMakePair( thisAction, roster ) );
        }
    }
    else
    {
        throw YAML::Exception( YAML::Mark(), "sequence key is missing" );
    }
}

Settings::Settings( bool debugMode )
    : QObject()
    , m_debug( debugMode )
    , m_doChroot( true )
    , m_promptInstall( false )
    , m_disableCancel( false )
    , m_disableCancelDuringExec( false )
{
    cWarning() << "Using bogus Calamares settings in"
               << ( debugMode ? QStringLiteral( "debug" ) : QStringLiteral( "regular" ) ) << "mode";
    s_instance = this;
}

Settings::Settings( const QString& settingsFilePath, bool debugMode )
    : QObject()
    , m_debug( debugMode )
    , m_doChroot( true )
    , m_promptInstall( false )
    , m_disableCancel( false )
    , m_disableCancelDuringExec( false )
{
    cDebug() << "Using Calamares settings file at" << settingsFilePath;
    QFile file( settingsFilePath );
    if ( file.exists() && file.open( QFile::ReadOnly | QFile::Text ) )
    {
        setConfiguration( file.readAll(), file.fileName() );
    }
    else
    {
        cWarning() << "Cannot read settings file" << file.fileName();
    }

    s_instance = this;
}

bool
Settings::isModuleEnabled( const QString& module ) const
{
    // Iterate over the list of modules searching for a match
    for ( const auto& moduleInstance : qAsConst( m_moduleInstances ) )
    {
        if ( moduleInstance.key().module() == module )
        {
            return true;
        }
    }

    return false;
}

void
Settings::reconcileInstancesAndSequence()
{
    // Since moduleFinder captures targetKey by reference, we can
    //   update targetKey to change what the finder lambda looks for.
    Calamares::ModuleSystem::InstanceKey targetKey;
    auto moduleFinder = [ &targetKey ]( const InstanceDescription& d ) { return d.isValid() && d.key() == targetKey; };

    // Check the sequence against the existing instances (which so far are only custom)
    for ( const auto& step : m_modulesSequence )
    {
        for ( const auto& instanceKey : step.second )
        {
            targetKey = instanceKey;
            const auto it = std::find_if( m_moduleInstances.constBegin(), m_moduleInstances.constEnd(), moduleFinder );
            if ( it == m_moduleInstances.constEnd() )
            {
                if ( instanceKey.isCustom() )
                {
                    cWarning() << "Custom instance key" << instanceKey << "is not listed in the *instances*";
                }
                m_moduleInstances.append( InstanceDescription( instanceKey ) );
            }
        }
    }
}

void
Settings::setConfiguration( const QByteArray& ba, const QString& explainName )
{
    try
    {
        YAML::Node config = YAML::Load( ba.constData() );
        Q_ASSERT( config.IsMap() );

        interpretModulesSearch(
            debugMode(), CalamaresUtils::yamlToStringList( config[ "modules-search" ] ), m_modulesSearchPaths );
        interpretInstances( config[ "instances" ], m_moduleInstances );
        interpretSequence( config[ "sequence" ], m_modulesSequence );

        m_brandingComponentName = requireString( config, "branding" );
        m_promptInstall = requireBool( config, "prompt-install", false );
        m_doChroot = !requireBool( config, "dont-chroot", false );
        m_isSetupMode = requireBool( config, "oem-setup", !m_doChroot );
        m_disableCancel = requireBool( config, "disable-cancel", false );
        m_disableCancelDuringExec = requireBool( config, "disable-cancel-during-exec", false );
        m_hideBackAndNextDuringExec = requireBool( config, "hide-back-and-next-during-exec", false );
        m_quitAtEnd = requireBool( config, "quit-at-end", false );

        reconcileInstancesAndSequence();
    }
    catch ( YAML::Exception& e )
    {
        CalamaresUtils::explainYamlException( e, ba, explainName );
    }
}

QStringList
Settings::modulesSearchPaths() const
{
    return m_modulesSearchPaths;
}


Settings::InstanceDescriptionList
Settings::moduleInstances() const
{
    return m_moduleInstances;
}


Settings::ModuleSequence
Settings::modulesSequence() const
{
    return m_modulesSequence;
}


QString
Settings::brandingComponentName() const
{
    return m_brandingComponentName;
}

static QStringList
settingsFileCandidates( bool assumeBuilddir )
{
    static const char settings[] = "settings.conf";

    QStringList settingsPaths;
    if ( CalamaresUtils::isAppDataDirOverridden() )
    {
        settingsPaths << CalamaresUtils::appDataDir().absoluteFilePath( settings );
    }
    else
    {
        if ( assumeBuilddir )
        {
            settingsPaths << QDir::current().absoluteFilePath( settings );
        }
        if ( CalamaresUtils::haveExtraDirs() )
            for ( auto s : CalamaresUtils::extraConfigDirs() )
            {
                settingsPaths << ( s + settings );
            }
        settingsPaths << CMAKE_INSTALL_FULL_SYSCONFDIR "/calamares/settings.conf";  // String concat
        settingsPaths << CalamaresUtils::appDataDir().absoluteFilePath( settings );
    }

    return settingsPaths;
}

Settings*
Settings::init( bool debugMode )
{
    if ( s_instance )
    {
        cWarning() << "Calamares::Settings already created";
        return s_instance;
    }

    QStringList settingsFileCandidatesByPriority = settingsFileCandidates( debugMode );

    QFileInfo settingsFile;
    bool found = false;

    foreach ( const QString& path, settingsFileCandidatesByPriority )
    {
        QFileInfo pathFi( path );
        if ( pathFi.exists() && pathFi.isReadable() )
        {
            settingsFile = pathFi;
            found = true;
            break;
        }
    }

    if ( !found || !settingsFile.exists() || !settingsFile.isReadable() )
    {
        cError() << "Cowardly refusing to continue startup without settings."
                 << Logger::DebugList( settingsFileCandidatesByPriority );
        if ( CalamaresUtils::isAppDataDirOverridden() )
        {
            cError() << "FATAL: explicitly configured application data directory is missing settings.conf";
        }
        else
        {
            cError() << "FATAL: none of the expected configuration file paths exist.";
        }
        ::exit( EXIT_FAILURE );
    }

    auto* settings = new Calamares::Settings( settingsFile.absoluteFilePath(), debugMode );  // Creates singleton
    if ( settings->modulesSequence().count() < 1 )
    {
        cError() << "FATAL: no sequence set.";
        ::exit( EXIT_FAILURE );
    }

    return settings;
}

Settings*
Settings::init( const QString& path )
{
    if ( s_instance )
    {
        cWarning() << "Calamares::Settings already created";
        return s_instance;
    }
    return new Calamares::Settings( path, true );
}

bool
Settings::isValid() const
{
    if ( brandingComponentName().isEmpty() )
    {
        cWarning() << "No branding component is set";
        return false;
    }

    const auto invalidDescriptor = []( const InstanceDescription& d ) { return !d.isValid(); };
    const auto invalidDescriptorIt
        = std::find_if( m_moduleInstances.constBegin(), m_moduleInstances.constEnd(), invalidDescriptor );
    if ( invalidDescriptorIt != m_moduleInstances.constEnd() )
    {
        cWarning() << "Invalid module instance in *instances* or *sequence*";
        return false;
    }

    return true;
}

}  // namespace Calamares
