/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017-2020, 2023-2024 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */
#include "Api.h"

#include "Variant.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "locale/Global.h"
#include "partition/Mount.h"
#include "utils/Logger.h"
#include "utils/RAII.h"
#include "utils/String.h"
#include "utils/Yaml.h"

#include <QCoreApplication>
#include <QDir>
#include <QStandardPaths>

namespace
{

///@brief Prefix added to Python log-messages
constexpr char output_prefix[] = "[PYTHON JOB]:";

///@brief Helper function to log a message (adds prefix, wrangles types)
inline void
log_action( unsigned int level, const std::string& s )
{
    Logger::CDebug( level ) << output_prefix << QString::fromStdString( s );
}

Calamares::GlobalStorage*
own_global_storage()
{
    static Calamares::GlobalStorage* p = new Calamares::GlobalStorage;
    return p;
}

QStringList
languages_from_global_storage()
{
    QStringList languages;

    // There are two ways that Python jobs can be initialised:
    //  - through JobQueue, in which case that has an instance which holds
    //    a GlobalStorage object, or
    //  - through the Python test-script, which initialises its
    //    own GlobalStorageProxy, which then holds a
    //    GlobalStorage object for all of Python.
    Calamares::JobQueue* jq = Calamares::JobQueue::instance();
    Calamares::GlobalStorage* gs = jq ? jq->globalStorage() : own_global_storage();

    QString lang = Calamares::Locale::readGS( *gs, QStringLiteral( "LANG" ) );
    if ( !lang.isEmpty() )
    {
        languages.append( lang );
        if ( lang.indexOf( '.' ) > 0 )
        {
            lang.truncate( lang.indexOf( '.' ) );
            languages.append( lang );
        }
        if ( lang.indexOf( '_' ) > 0 )
        {
            lang.truncate( lang.indexOf( '_' ) );
            languages.append( lang );
        }
    }
    return languages;
}

void
append_language_directory( QStringList& pathList, const QString& candidate )
{
    if ( !candidate.isEmpty() && !pathList.contains( candidate ) )
    {
        pathList.prepend( candidate );
        if ( QDir( candidate ).cd( "lang" ) )
        {
            pathList.prepend( candidate + "/lang" );
        }
    }
}

}

namespace Calamares
{
namespace Python
{

std::string
obscure( const std::string& string )
{
    return Calamares::String::obscure( QString::fromStdString( string ) ).toStdString();
}

void
debug( const std::string& s )
{
    log_action( Logger::LOGDEBUG, s );
}

void
warning( const std::string& s )
{
    log_action( Logger::LOGWARNING, s );
}

void
error( const std::string& s )
{
    log_action( Logger::LOGERROR, s );
}

Dictionary
load_yaml( const std::string& path )
{
    const QString filePath = QString::fromUtf8( path.c_str() );
    bool ok = false;
    auto map = Calamares::YAML::load( filePath, &ok );
    if ( !ok )
    {
        cWarning() << "Loading YAML from" << filePath << "failed.";
    }

    return Calamares::Python::variantMapToPyDict( map );
}

Python::List
gettext_languages()
{
    Python::List pyList;
    for ( const auto & lang : languages_from_global_storage()  )
    {
        pyList.append( lang.toStdString() );
    }
    return pyList;
}

Python::Object
gettext_path()
{
    // Going to log informatively just once
    static bool first_time = true;
    cScopedAssignment( &first_time, false );

    // TODO: distinguish between -d runs and normal runs
    // TODO: can we detect DESTDIR-installs?
    QStringList candidatePaths
        = QStandardPaths::locateAll( QStandardPaths::GenericDataLocation, "locale", QStandardPaths::LocateDirectory );
    QString extra = QCoreApplication::applicationDirPath();
    append_language_directory( candidatePaths, extra );  // Often /usr/local/bin
    if ( !extra.isEmpty() )
    {
        QDir d( extra );
        if ( d.cd( "../share/locale" ) )  // Often /usr/local/bin/../share/locale -> /usr/local/share/locale
        {
            append_language_directory( candidatePaths, d.canonicalPath() );
        }
    }
    append_language_directory( candidatePaths, QDir().canonicalPath() ); // Current directory, e.g. "."

    if ( first_time )
    {
        cDebug() << "Determining gettext path from" << candidatePaths;
    }

    QStringList candidateLanguages = languages_from_global_storage();
    for ( const auto& lang : candidateLanguages )
    {
        for ( const auto & localedir : candidatePaths )
        {
            QDir ldir( localedir );
            if ( ldir.cd( lang ) )
            {
                Logger::CDebug( Logger::LOGDEBUG )
                    << output_prefix << "Found gettext" << lang << "in" << ldir.canonicalPath();
                return String( localedir.toStdString() );
            }
        }
    }
    cWarning() << "No translation found for languages" << candidateLanguages;
    return Python::None();
}

int
mount( const std::string& device_path,
       const std::string& mount_point,
       const std::string& filesystem_name,
       const std::string& options )
{
    return Calamares::Partition::mount( QString::fromStdString( device_path ),
                                        QString::fromStdString( mount_point ),
                                        QString::fromStdString( filesystem_name ),
                                        QString::fromStdString( options ) );
}

}
}
