/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org> (original dummypython code)
 *   SPDX-FileCopyrightText: 2016 Kevin Kofler <kevin.kofler@chello.at>
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "DummyCppJob.h"

#include <QDateTime>
#include <QThread>

#include "CalamaresVersion.h"
#include "GlobalStorage.h"
#include "JobQueue.h"

#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"

DummyCppJob::DummyCppJob( QObject* parent )
    : Calamares::CppJob( parent )
{
}


DummyCppJob::~DummyCppJob() {}


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
    if ( variant.type() == QVariant::Map )
    {
        return variantMapToString( variant.toMap() );
    }
    else if ( variant.type() == QVariant::Hash )
    {
        return variantHashToString( variant.toHash() );
    }
    else if ( ( variant.type() == QVariant::List ) || ( variant.type() == QVariant::StringList ) )
    {
        return variantListToString( variant.toList() );
    }
    else
    {
        return variant.toString();
    }
}


static QString
variantListToString( const QVariantList& variantList )
{
    QStringList result;
    for ( const QVariant& variant : variantList )
    {
        result.append( variantToString( variant ) );
    }
    return '{' + result.join( ',' ) + '}';
}


static QString
variantMapToString( const QVariantMap& variantMap )
{
    QStringList result;
    for ( auto it = variantMap.constBegin(); it != variantMap.constEnd(); ++it )
    {
        result.append( it.key() + '=' + variantToString( it.value() ) );
    }
    return '[' + result.join( ',' ) + ']';
}


static QString
variantHashToString( const QVariantHash& variantHash )
{
    QStringList result;
    for ( auto it = variantHash.constBegin(); it != variantHash.constEnd(); ++it )
    {
        result.append( it.key() + '=' + variantToString( it.value() ) );
    }
    return '<' + result.join( ',' ) + '>';
}


Calamares::JobResult
DummyCppJob::exec()
{
    // Ported from dummypython
    CalamaresUtils::System::runCommand( CalamaresUtils::System::RunLocation::RunInHost,
                                        QStringList() << "/bin/sh"
                                                      << "-c"
                                                      << "touch ~/calamares-dummycpp" );
    QString accumulator = QDateTime::currentDateTimeUtc().toString( Qt::ISODate ) + '\n';
    accumulator += QStringLiteral( "Calamares version: " ) + CALAMARES_VERSION_SHORT + '\n';
    accumulator += QStringLiteral( "This job's name: " ) + prettyName() + '\n';
    accumulator += QStringLiteral( "Configuration map: %1\n" ).arg( variantMapToString( m_configurationMap ) );
    accumulator += QStringLiteral( "   *** globalstorage test ***\n" );
    Calamares::GlobalStorage* globalStorage = Calamares::JobQueue::instance()->globalStorage();
    accumulator += QStringLiteral( "lala: " )
        + ( globalStorage->contains( "lala" ) ? QStringLiteral( "true" ) : QStringLiteral( "false" ) ) + '\n';
    accumulator += QStringLiteral( "foo: " )
        + ( globalStorage->contains( "foo" ) ? QStringLiteral( "true" ) : QStringLiteral( "false" ) ) + '\n';
    accumulator += QStringLiteral( "count: " ) + QString::number( globalStorage->count() ) + '\n';
    globalStorage->insert( "item2", "value2" );
    globalStorage->insert( "item3", 3 );
    accumulator += QStringLiteral( "keys: %1\n" ).arg( globalStorage->keys().join( ',' ) );
    accumulator += QStringLiteral( "remove: %1\n" ).arg( QString::number( globalStorage->remove( "item2" ) ) );
    accumulator += QStringLiteral( "values: %1 %2 %3\n" )
                       .arg( globalStorage->value( "foo" ).toString(),
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

CALAMARES_PLUGIN_FACTORY_DEFINITION( DummyCppJobFactory, registerPlugin< DummyCppJob >(); )
