/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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

#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

namespace Calamares
{

Settings* Settings::s_instance = 0;

Settings*
Settings::instance()
{
    return s_instance;
}


Settings::Settings( QObject* parent )
    : QObject( parent )
{
    QFile file( CalamaresUtils::appDataDir().absoluteFilePath( "settings.json" ) );
    if ( file.exists() && file.canReadLine() )
    {
        QByteArray ba = file.readAll();
        QJsonParseError* err = 0;
        QJsonDocument document = QJsonDocument::fromJson( ba, err );
        if ( !err && !document.isNull() && !document.isEmpty() )
        {
            QJsonObject json = document.object();

            foreach ( const QJsonValue& val, json[ "modules-search" ].toArray() )
            {
                if ( !val.isString() || val.toString().isEmpty() )
                    continue;

                QString entry = val.toString();

                if ( entry == "local" )
                {
                    m_modulesSearchPaths.append( CalamaresUtils::appDataDir().absolutePath() + QDir::separator() + "modules" );
                }
                else
                {
                    QDir path( entry );
                    if ( path.exists() && path.isReadable() )
                        m_modulesSearchPaths.append( path.absolutePath() );
                }
            }

            foreach ( const QJsonValue& val, json[ "modules-prepare" ].toArray() )
            {
                if ( !val.isString() || val.toString().isEmpty() )
                    continue;

                m_viewModulesPrepareList.append( val.toString() );
            }

            foreach ( const QJsonValue& val, json[ "modules-postinstall" ].toArray() )
            {
                if ( !val.isString() || val.toString().isEmpty() )
                    continue;

                m_viewModulesPostInstallList.append( val.toString() );
            }
        }
        else
        {
            cDebug() << "WARNING: Invalid document " << file.fileName()
                     << " error: " << err->errorString();
        }
    }
    else
    {
        cDebug() << "WARNING: Cannot read " << file.fileName();
    }

    s_instance = this;
}


QStringList
Settings::modulesSearchPaths()
{
    return m_modulesSearchPaths;
}


QStringList
Settings::viewModulesPrepare()
{
    return m_viewModulesPrepareList;
}


QStringList
Settings::viewModulesPostInstall()
{
    return m_viewModulesPostInstallList;
}


}
