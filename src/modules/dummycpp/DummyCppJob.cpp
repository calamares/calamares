/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org> (original dummypython code)
 *   Copyright 2016, Kevin Kofler <kevin.kofler@chello.at>
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

#include "DummyCppJob.h"

#include <QProcess>
#include <QDateTime>
#include <QThread>

#include "CalamaresVersion.h"
#include "JobQueue.h"
#include "GlobalStorage.h"

#include "utils/Logger.h"

DummyCppJob::DummyCppJob( QObject* parent )
    : Calamares::CppJob( parent )
{
}


DummyCppJob::~DummyCppJob()
{
}


QString
DummyCppJob::prettyName() const
{
    return tr( "Dummy C++ Job" );
}


static QString variantListToString( const QVariantList& variantList );
static QString variantMapToString( const QVariantMap& variantMap );
static QString variantHashToString( const QVariantHash& variantHash );


static QString
variantToString( const QVariant& variant )
{
    switch ( variant.type() )
    {
    case QVariant::Map:
        return variantMapToString( variant.toMap() );

    case QVariant::Hash:
        return variantHashToString( variant.toHash() );

    case QVariant::List:
    case QVariant::StringList:
        return variantListToString( variant.toList() );

    default:
        return variant.toString();
    }
}


static QString
variantListToString( const QVariantList& variantList )
{
    QStringList result;
    for ( const QVariant& variant : variantList )
        result.append( variantToString( variant ) );
    return '{' + result.join(',') + '}';
}


static QString
variantMapToString( const QVariantMap& variantMap )
{
    QStringList result;
    for ( auto it = variantMap.constBegin(); it != variantMap.constEnd(); ++it )
        result.append( it.key() + '=' + variantToString( it.value() ) );
    return '[' + result.join(',') + ']';
}


static QString
variantHashToString( const QVariantHash& variantHash )
{
    QStringList result;
    for ( auto it = variantHash.constBegin(); it != variantHash.constEnd(); ++it )
        result.append( it.key() + '=' + variantToString( it.value() ) );
    return '<' + result.join(',') + '>';
}


Calamares::JobResult
DummyCppJob::exec()
{
    // Ported from dummypython
    QProcess::execute( "/bin/sh", QStringList() << "-c" << "touch ~/calamares-dummycpp" );
    QString accumulator = QDateTime::currentDateTimeUtc().toString( Qt::ISODate ) + '\n';
    accumulator += QStringLiteral( "Calamares version: " ) + CALAMARES_VERSION_SHORT + '\n';
    accumulator += QStringLiteral( "This job's name: " ) + prettyName() + '\n';
    accumulator += QStringLiteral( "Configuration map: %1\n" ).arg( variantMapToString( m_configurationMap ) );
    accumulator += QStringLiteral( "   *** globalstorage test ***\n" );
    Calamares::GlobalStorage *globalStorage = Calamares::JobQueue::instance()->globalStorage();
    accumulator += QStringLiteral( "lala: " ) + (globalStorage->contains( "lala" ) ? QStringLiteral( "true" ) : QStringLiteral( "false" )) + '\n';
    accumulator += QStringLiteral( "foo: " ) + (globalStorage->contains( "foo" ) ? QStringLiteral( "true" ) : QStringLiteral( "false" )) + '\n';
    accumulator += QStringLiteral( "count: " ) + QString::number( globalStorage->count() ) + '\n';
    globalStorage->insert( "item2", "value2" );
    globalStorage->insert( "item3", 3 );
    accumulator += QStringLiteral( "keys: %1\n" ).arg( globalStorage->keys().join( ',' ) );
    accumulator += QStringLiteral( "remove: %1\n" ).arg( QString::number( globalStorage->remove( "item2" ) ) );
    accumulator += QStringLiteral( "values: %1 %2 %3\n" ).arg(
        globalStorage->value( "foo" ).toString(),
        globalStorage->value( "item2" ).toString(),
        globalStorage->value( "item3" ).toString() );

    emit progress( 0.1 );
    cDebug() << "[DUMMYCPP]: " << accumulator;

    globalStorage->debugDump();
    emit progress( 0.5 );

    QThread::sleep( 3 );

    return Calamares::JobResult::ok();
}


void
DummyCppJob::setConfigurationMap( const QVariantMap& configurationMap )
{
    m_configurationMap = configurationMap;
}

CALAMARES_PLUGIN_FACTORY_DEFINITION( DummyCppJobFactory, registerPlugin<DummyCppJob>(); )
