/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2020, Adriaan de Groot <groot@kde.org>
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

#include "Qml.h"

#include "Branding.h"
#include "ViewManager.h"
#include "utils/Logger.h"

#include <QByteArray>
#include <QObject>
#include <QQuickItem>
#include <QString>
#include <QVariant>

namespace CalamaresUtils
{

void
callQMLFunction( QQuickItem* qmlObject, const char* method )
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
                        [&]( const QString& s ) { return s.isEmpty() ? QString() : bPath.arg( brandDir, s ); } );
    }
    if ( ( method == QmlSearch::Both ) || ( method == QmlSearch::QrcOnly ) )
    {
        std::transform( names.constBegin(),
                        names.constEnd(),
                        std::back_inserter( candidates ),
                        [&]( const QString& s ) { return s.isEmpty() ? QString() : qrPath.arg( s ); } );
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
registerCalamaresModels()
{
    static bool done = false;
    if ( !done )
    {
        done = true;
        // Because branding and viewmanager have a parent (CalamaresApplication
        // and CalamaresWindow), they will not be deleted by QmlEngine.
        //   https://doc.qt.io/qt-5/qtqml-cppintegration-data.html#data-ownership
        qmlRegisterSingletonType< Calamares::Branding >(
            "io.calamares.ui", 1, 0, "Branding", []( QQmlEngine*, QJSEngine* ) -> QObject* {
                return Calamares::Branding::instance();
            } );
        qmlRegisterSingletonType< Calamares::Branding >(
            "io.calamares.core", 1, 0, "ViewManager", []( QQmlEngine*, QJSEngine* ) -> QObject* {
                return Calamares::ViewManager::instance();
            } );
    }
}

}  // namespace CalamaresUtils
