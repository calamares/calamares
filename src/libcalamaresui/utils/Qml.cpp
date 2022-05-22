/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "Qml.h"

#include "Branding.h"
#include "GlobalStorage.h"
#include "JobQueue.h"
#include "Settings.h"
#include "ViewManager.h"
#include "network/Manager.h"
#include "utils/Dirs.h"
#include "utils/Logger.h"

#include <QByteArray>
#include <QObject>
#include <QQuickItem>
#include <QString>
#include <QVariant>

static QDir s_qmlModulesDir( QString( CMAKE_INSTALL_FULL_DATADIR ) + "/qml" );

namespace CalamaresUtils
{
QDir
qmlModulesDir()
{
    return s_qmlModulesDir;
}

void
setQmlModulesDir( const QDir& dir )
{
    s_qmlModulesDir = dir;
}

static QStringList
qmlDirCandidates( bool assumeBuilddir )
{
    static const char QML[] = "qml";

    QStringList qmlDirs;
    if ( CalamaresUtils::isAppDataDirOverridden() )
    {
        qmlDirs << CalamaresUtils::appDataDir().absoluteFilePath( QML );
    }
    else
    {
        if ( assumeBuilddir )
        {
            qmlDirs << QDir::current().absoluteFilePath( "src/qml" );  // In build-dir
        }
        if ( CalamaresUtils::haveExtraDirs() )
            for ( auto s : CalamaresUtils::extraDataDirs() )
            {
                qmlDirs << ( s + QML );
            }
        qmlDirs << CalamaresUtils::appDataDir().absoluteFilePath( QML );
    }

    return qmlDirs;
}

bool
initQmlModulesDir()
{
    QStringList qmlDirCandidatesByPriority
        = qmlDirCandidates( Calamares::Settings::instance() && Calamares::Settings::instance()->debugMode() );

    for ( const QString& path : qmlDirCandidatesByPriority )
    {
        QDir dir( path );
        if ( dir.exists() && dir.isReadable() )
        {
            cDebug() << "Using Calamares QML directory" << dir.absolutePath();
            CalamaresUtils::setQmlModulesDir( dir );
            return true;
        }
    }

    cError() << "Cowardly refusing to continue startup without a QML directory."
             << Logger::DebugList( qmlDirCandidatesByPriority );
    if ( CalamaresUtils::isAppDataDirOverridden() )
    {
        cError() << "FATAL: explicitly configured application data directory is missing qml/";
    }
    else
    {
        cError() << "FATAL: none of the expected QML paths exist.";
    }
    return false;
}

void
callQmlFunction( QQuickItem* qmlObject, const char* method )
{
    QByteArray methodSignature( method );
    methodSignature.append( "()" );

    if ( qmlObject && qmlObject->metaObject()->indexOfMethod( methodSignature ) >= 0 )
    {
        QVariant returnValue;
        QMetaObject::invokeMethod( qmlObject, method, Q_RETURN_ARG( QVariant, returnValue ) );
        if ( !returnValue.isNull() )
        {
            cDebug() << "QML" << methodSignature << "returned" << returnValue;
        }
    }
    else if ( qmlObject )
    {
        cDebug() << "QML" << methodSignature << "is missing.";
    }
}

/** @brief Appends to @p candidates suitable expansions of @p names
 *
 * Depending on @p method, adds search expansions for branding, or QRC,
 * or both (with branding having precedence).
 */
static void
addExpansions( QmlSearch method, QStringList& candidates, const QStringList& names )
{
    QString bPath( QStringLiteral( "%1/%2.qml" ) );
    QString qrPath( QStringLiteral( ":/%1.qml" ) );

    if ( ( method == QmlSearch::Both ) || ( method == QmlSearch::BrandingOnly ) )
    {
        QString brandDir = Calamares::Branding::instance()->componentDirectory();
        std::transform( names.constBegin(),
                        names.constEnd(),
                        std::back_inserter( candidates ),
                        [ & ]( const QString& s ) { return s.isEmpty() ? QString() : bPath.arg( brandDir, s ); } );
    }
    if ( ( method == QmlSearch::Both ) || ( method == QmlSearch::QrcOnly ) )
    {
        std::transform( names.constBegin(),
                        names.constEnd(),
                        std::back_inserter( candidates ),
                        [ & ]( const QString& s ) { return s.isEmpty() ? QString() : qrPath.arg( s ); } );
    }
}

/** @brief Does actual search and returns result.
 *
 * Empty items in @p candidates are ignored.
 */
static QString
searchQmlFile( QmlSearch method, const QString& configuredName, const QStringList& hints )
{
    QStringList candidates;
    if ( configuredName.startsWith( '/' ) )
    {
        candidates << configuredName;
    }
    addExpansions( method, candidates, hints );

    for ( const QString& candidate : candidates )
    {
        if ( candidate.isEmpty() )
        {
            continue;
        }
        cDebug() << Logger::SubEntry << "Looking at QML file" << candidate;
        if ( QFile::exists( candidate ) )
        {
            if ( candidate.startsWith( ':' ) )
            {
                // Inconsistency: QFile only sees the file with :,
                // but QML needs an explicit scheme (of qrc:)
                return QStringLiteral( "qrc" ) + candidate;
            }
            return candidate;
        }
    }
    cDebug() << Logger::SubEntry << "None found.";
    return QString();
}

QString
searchQmlFile( QmlSearch method, const QString& configuredName, const Calamares::ModuleSystem::InstanceKey& i )
{
    cDebug() << "Looking for QML for" << i.toString();
    return searchQmlFile( method, configuredName, { configuredName, i.toString(), i.module() } );
}

QString
searchQmlFile( QmlSearch method, const QString& configuredName )
{
    cDebug() << "Looking for QML for" << configuredName;
    return searchQmlFile( method, configuredName, { configuredName } );
}

const NamedEnumTable< QmlSearch >&
qmlSearchNames()
{
    // *INDENT-OFF*
    // clang-format off
    static NamedEnumTable< QmlSearch > names {
        { QStringLiteral( "both" ), QmlSearch::Both },
        { QStringLiteral( "qrc" ), QmlSearch::QrcOnly },
        { QStringLiteral( "branding" ), QmlSearch::BrandingOnly }
    };
    // *INDENT-ON*
    // clang-format on

    return names;
}

void
registerQmlModels()
{
    static bool done = false;
    if ( !done )
    {
        done = true;
        // Because branding and viewmanager have a parent (CalamaresApplication
        // and CalamaresWindow), they will not be deleted by QmlEngine.
        //   https://doc.qt.io/qt-5/qtqml-cppintegration-data.html#data-ownership
        qmlRegisterSingletonType< Calamares::Branding >( "io.calamares.ui",
                                                         1,
                                                         0,
                                                         "Branding",
                                                         []( QQmlEngine*, QJSEngine* ) -> QObject*
                                                         { return Calamares::Branding::instance(); } );
        qmlRegisterSingletonType< Calamares::ViewManager >( "io.calamares.ui",
                                                            1,
                                                            0,
                                                            "ViewManager",
                                                            []( QQmlEngine*, QJSEngine* ) -> QObject*
                                                            { return Calamares::ViewManager::instance(); } );
        qmlRegisterSingletonType< Calamares::GlobalStorage >(
            "io.calamares.core",
            1,
            0,
            "Global",
            []( QQmlEngine*, QJSEngine* ) -> QObject* { return Calamares::JobQueue::instance()->globalStorage(); } );
        qmlRegisterSingletonType< CalamaresUtils::Network::Manager >(
            "io.calamares.core",
            1,
            0,
            "Network",
            []( QQmlEngine*, QJSEngine* ) -> QObject* { return &CalamaresUtils::Network::Manager::instance(); } );
    }
}

}  // namespace CalamaresUtils
