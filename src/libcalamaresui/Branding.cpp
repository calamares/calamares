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

#include "Branding.h"

#include "utils/CalamaresUtils.h"
#include "utils/Logger.h"
#include "utils/YamlUtils.h"

#include <QDir>
#include <QFile>

#include <yaml-cpp/yaml.h>


namespace Calamares
{

Branding* Branding::s_instance = nullptr;

Branding*
Branding::instance()
{
    return s_instance;
}


Branding::Branding( const QString& brandingFilePath,
                    QObject* parent )
    : QObject( parent )
    , m_descriptorPath( brandingFilePath )
{
    cDebug() << "Using Calamares branding file at" << brandingFilePath;
    QFile file( brandingFilePath );
    if ( file.exists() && file.open( QFile::ReadOnly | QFile::Text ) )
    {
        QByteArray ba = file.readAll();

        try
        {
            YAML::Node doc = YAML::Load( ba.constData() );
            Q_ASSERT( doc.IsMap() );

            m_componentName = QString::fromStdString( doc[ "component-name" ]
                                                      .as< std::string >() );
            if ( m_componentName != QFileInfo( m_descriptorPath ).absoluteDir().dirName() )
            {
                cLog() << "FATAL ERROR in"
                       << m_descriptorPath
                       << "\nThe branding component name should match the name of the "
                          "component directory.";
                ::exit( EXIT_FAILURE );
            }
        }
        catch ( YAML::Exception& e )
        {
            cDebug() << "WARNING: YAML parser error " << e.what();
        }
    }
    else
    {
        cDebug() << "WARNING: Cannot read " << file.fileName();
    }

    s_instance = this;
    cDebug() << "Loaded branding component" << m_componentName;
}


QString
Branding::descriptorPath() const
{
    return m_descriptorPath;
}


QString
Branding::componentName() const
{
    return m_componentName;
}


QString
Branding::componentDirectory() const
{
    QFileInfo fi ( m_descriptorPath );
    return fi.absoluteDir().absolutePath();
}

}
