/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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

#include "Settings.h"

#include "utils/CalamaresUtils.h"
#include "utils/Logger.h"
#include "utils/YamlUtils.h"

#include <QDir>
#include <QFile>
#include <QPair>

#include <yaml-cpp/yaml.h>


namespace Calamares
{

Settings* Settings::s_instance = nullptr;

Settings*
Settings::instance()
{
    return s_instance;
}


Settings::Settings( const QString& settingsFilePath,
                    bool debugMode,
                    QObject* parent )
    : QObject( parent )
    , m_debug( debugMode )
    , m_doChroot( true )
    , m_promptInstall( false )
{
    cDebug() << "Using Calamares settings file at" << settingsFilePath;
    QFile file( settingsFilePath );
    if ( file.exists() && file.open( QFile::ReadOnly | QFile::Text ) )
    {
        QByteArray ba = file.readAll();

        try
        {
            YAML::Node config = YAML::Load( ba.constData() );
            Q_ASSERT( config.IsMap() );

            QStringList rawPaths;
            config[ "modules-search" ] >> rawPaths;
            for ( int i = 0; i < rawPaths.length(); ++i )
            {
                if ( rawPaths[ i ] == "local" )
                {
                    // If we're running in debug mode, we assume we might also be
                    // running from the build dir, so we add a maximum priority
                    // module search path in the build dir.
                    if ( debugMode )
                    {
                        QString buildDirModules = QDir::current().absolutePath() +
                                                  QDir::separator() + "src" +
                                                  QDir::separator() + "modules";
                        if ( QDir( buildDirModules ).exists() )
                            m_modulesSearchPaths.append( buildDirModules );
                    }

                    // Install path is set in CalamaresAddPlugin.cmake
                    m_modulesSearchPaths.append( CalamaresUtils::systemLibDir().absolutePath() +
                                                 QDir::separator() + "calamares" +
                                                 QDir::separator() + "modules" );
                }
                else
                {
                    QDir path( rawPaths[ i ] );
                    if ( path.exists() && path.isReadable() )
                        m_modulesSearchPaths.append( path.absolutePath() );
                }
            }

            // Parse the custom instances section
            if ( config[ "instances" ] )
            {
                QVariant instancesV
                        = CalamaresUtils::yamlToVariant( config[ "instances" ] ).toList();
                if ( instancesV.type() == QVariant::List )
                {
                    const auto instances = instancesV.toList();
                    for ( const QVariant& instancesVListItem : instances )
                    {
                        if ( instancesVListItem.type() != QVariant::Map )
                            continue;
                        QVariantMap instancesVListItemMap =
                                instancesVListItem.toMap();
                        QMap< QString, QString > instanceMap;
                        for ( auto it = instancesVListItemMap.constBegin();
                              it != instancesVListItemMap.constEnd(); ++it )
                        {
                            if ( it.value().type() != QVariant::String )
                                continue;
                            instanceMap.insert( it.key(), it.value().toString() );
                        }
                        m_customModuleInstances.append( instanceMap );
                    }
                }
            }

            // Parse the modules sequence section
            Q_ASSERT( config[ "sequence" ] ); // It better exist!
            {
                QVariant sequenceV
                        = CalamaresUtils::yamlToVariant( config[ "sequence" ] );
                Q_ASSERT( sequenceV.type() == QVariant::List );
                const auto sequence = sequenceV.toList();
                for ( const QVariant& sequenceVListItem : sequence )
                {
                    if ( sequenceVListItem.type() != QVariant::Map )
                        continue;
                    QString thisActionS = sequenceVListItem.toMap().firstKey();
                    ModuleAction thisAction;
                    if ( thisActionS == "show" )
                        thisAction = ModuleAction::Show;
                    else if ( thisActionS == "exec" )
                        thisAction = ModuleAction::Exec;
                    else
                        continue;

                    QStringList thisActionRoster = sequenceVListItem
                                                   .toMap()
                                                   .value( thisActionS )
                                                   .toStringList();
                    m_modulesSequence.append( qMakePair( thisAction,
                                                         thisActionRoster ) );
                }
            }

            m_brandingComponentName = QString::fromStdString( config[ "branding" ]
                                                              .as< std::string >() );
            m_promptInstall = config[ "prompt-install" ].as< bool >();

            m_doChroot = config[ "dont-chroot" ] ? !config[ "dont-chroot" ].as< bool >() : true;
        }
        catch ( YAML::Exception& e )
        {
            cDebug() << "WARNING: YAML parser error " << e.what() << "in" << file.fileName();
        }
    }
    else
    {
        cDebug() << "WARNING: Cannot read " << file.fileName();
    }

    s_instance = this;
}


QStringList
Settings::modulesSearchPaths() const
{
    return m_modulesSearchPaths;
}


QList<QMap<QString, QString> >
Settings::customModuleInstances() const
{
    return m_customModuleInstances;
}


QList< QPair< ModuleAction, QStringList > >
Settings::modulesSequence() const
{
    return m_modulesSequence;
}


QString
Settings::brandingComponentName() const
{
    return m_brandingComponentName;
}


bool
Settings::showPromptBeforeExecution() const
{
    return m_promptInstall;
}


bool
Settings::debugMode() const
{
    return m_debug;
}

bool
Settings::doChroot() const
{
    return m_doChroot;
}


}
