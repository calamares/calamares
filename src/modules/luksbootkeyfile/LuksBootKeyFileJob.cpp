/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include "LuksBootKeyFileJob.h"

#include "utils/CalamaresUtilsSystem.h"
#include "utils/Entropy.h"
#include "utils/Logger.h"
#include "utils/NamedEnum.h"
#include "utils/UMask.h"
#include "utils/Variant.h"

#include "GlobalStorage.h"
#include "JobQueue.h"

LuksBootKeyFileJob::LuksBootKeyFileJob( QObject* parent )
    : Calamares::CppJob( parent )
{
}

LuksBootKeyFileJob::~LuksBootKeyFileJob() {}

QString
LuksBootKeyFileJob::prettyName() const
{
    return tr( "Configuring LUKS key file." );
}

struct LuksDevice
{
    LuksDevice( const QMap< QString, QVariant >& pinfo )
        : isValid( false )
        , isRoot( false )
    {
        if ( pinfo.contains( "luksMapperName" ) )
        {
            QString fs = pinfo[ "fs" ].toString();
            QString mountPoint = pinfo[ "mountPoint" ].toString();

            if ( !mountPoint.isEmpty() || fs == QStringLiteral( "linuxswap" ) )
            {
                isValid = true;
                isRoot = mountPoint == '/';
                device = pinfo[ "device" ].toString();
                passphrase = pinfo[ "luksPassphrase" ].toString();
            }
        }
    }

    bool isValid;
    bool isRoot;
    QString device;
    QString passphrase;
};

/** @brief Extract the luks passphrases setup.
 *
 * Given a list of partitions (as set up by the partitioning module,
 * so there's maps with keys inside), returns just the list of
 * luks passphrases for each device.
 */
static QList< LuksDevice >
getLuksDevices( const QVariantList& list )
{
    QList< LuksDevice > luksItems;

    for ( const auto& p : list )
    {
        if ( p.canConvert< QVariantMap >() )
        {
            LuksDevice d( p.toMap() );
            if ( d.isValid )
            {
                luksItems.append( d );
            }
        }
    }
    return luksItems;
}

struct LuksDeviceList
{
    LuksDeviceList( const QVariant& partitions )
        : valid( false )
    {
        if ( partitions.canConvert< QVariantList >() )
        {
            devices = getLuksDevices( partitions.toList() );
            valid = true;
        }
    }

    QList< LuksDevice > devices;
    bool valid;
};

static const char keyfile[] = "/crypto_keyfile.bin";

static bool
generateTargetKeyfile()
{
    CalamaresUtils::UMask m( CalamaresUtils::UMask::Safe );

    // Get the data
    QByteArray entropy;
    auto entropySource = CalamaresUtils::getEntropy( 2048, entropy );
    if ( entropySource != CalamaresUtils::EntropySource::URandom )
    {
        cWarning() << "Could not get entropy from /dev/urandom for LUKS.";
        return false;
    }

    auto fileResult = CalamaresUtils::System::instance()->createTargetFile(
        keyfile, entropy, CalamaresUtils::System::WriteMode::Overwrite );
    entropy.fill( 'A' );
    if ( !fileResult )
    {
        cWarning() << "Could not create LUKS keyfile:" << smash( fileResult.code() );
        return false;
    }

    // Give ample time to check that the file was created correctly;
    // we actually expect ls to return pretty-much-instantly.
    auto r = CalamaresUtils::System::instance()->targetEnvCommand(
        { "ls", "-la", "/" }, QString(), QString(), std::chrono::seconds( 5 ) );
    cDebug() << "In target system after creating LUKS file" << r.getOutput();
    return true;
}

static bool
setupLuks( const LuksDevice& d )
{
    // Adding the key can take some times, measured around 15 seconds with
    // a HDD (spinning rust) and a slow-ish computer. Give it a minute.
    auto r = CalamaresUtils::System::instance()->targetEnvCommand(
        { "cryptsetup", "luksAddKey", d.device, keyfile }, QString(), d.passphrase, std::chrono::seconds( 60 ) );
    if ( r.getExitCode() != 0 )
    {
        cWarning() << "Could not configure LUKS keyfile on" << d.device << ':' << r.getOutput() << "(exit code"
                   << r.getExitCode() << ')';
        return false;
    }
    return true;
}

static QVariantList
partitions()
{
    Calamares::GlobalStorage* globalStorage = Calamares::JobQueue::instance()->globalStorage();
    return globalStorage->value( QStringLiteral( "partitions" ) ).toList();
}

static bool
hasUnencryptedSeparateBoot()
{
    const QVariantList partitions = ::partitions();
    for ( const QVariant& partition : partitions )
    {
        QVariantMap partitionMap = partition.toMap();
        QString mountPoint = partitionMap.value( QStringLiteral( "mountPoint" ) ).toString();
        if ( mountPoint == QStringLiteral( "/boot" ) )
        {
            return !partitionMap.contains( QStringLiteral( "luksMapperName" ) );
        }
    }
    return false;
}

Calamares::JobResult
LuksBootKeyFileJob::exec()
{
    const auto* gs = Calamares::JobQueue::instance()->globalStorage();
    if ( !gs )
    {
        return Calamares::JobResult::internalError(
            "LuksBootKeyFile", "No GlobalStorage defined.", Calamares::JobResult::InvalidConfiguration );
    }
    if ( !gs->contains( "partitions" ) )
    {
        cError() << "No GS[partitions] key.";
        return Calamares::JobResult::internalError(
            "LuksBootKeyFile", tr( "No partitions are defined." ), Calamares::JobResult::InvalidConfiguration );
    }

    LuksDeviceList s( gs->value( "partitions" ) );
    if ( !s.valid )
    {
        cError() << "GS[partitions] is invalid";
        return Calamares::JobResult::internalError(
            "LuksBootKeyFile", tr( "No partitions are defined." ), Calamares::JobResult::InvalidConfiguration );
    }

    cDebug() << "There are" << s.devices.count() << "LUKS partitions";
    if ( s.devices.count() < 1 )
    {
        cDebug() << Logger::SubEntry << "Nothing to do for LUKS.";
        return Calamares::JobResult::ok();
    }

    auto it = std::partition( s.devices.begin(), s.devices.end(), []( const LuksDevice& d ) { return d.isRoot; } );
    for ( const auto& d : s.devices )
    {
        cDebug() << Logger::SubEntry << ( d.isRoot ? "root" : "dev." ) << d.device << "passphrase?"
                 << !d.passphrase.isEmpty();
    }

    if ( it == s.devices.begin() )
    {
        // Then there was no root partition
        cDebug() << Logger::SubEntry << "No root partition.";
        return Calamares::JobResult::ok();
    }

    // /boot partition is not encrypted, keyfile must not be used
    if ( hasUnencryptedSeparateBoot() )
    {
        cDebug() << Logger::SubEntry << "/boot partition is not encrypted, skipping keyfile creation.";
        return Calamares::JobResult::ok();
    }

    if ( s.devices.first().passphrase.isEmpty() )
    {
        cDebug() << Logger::SubEntry << "No root passphrase.";
        return Calamares::JobResult::error(
            tr( "Encrypted rootfs setup error" ),
            tr( "Root partition %1 is LUKS but no passphrase has been set." ).arg( s.devices.first().device ) );
    }

    if ( !generateTargetKeyfile() )
    {
        return Calamares::JobResult::error(
            tr( "Encrypted rootfs setup error" ),
            tr( "Could not create LUKS key file for root partition %1." ).arg( s.devices.first().device ) );
    }

    for ( const auto& d : s.devices )
    {
        if ( !setupLuks( d ) )
            return Calamares::JobResult::error(
                tr( "Encrypted rootfs setup error" ),
                tr( "Could not configure LUKS key file on partition %1." ).arg( d.device ) );
    }

    return Calamares::JobResult::ok();
}

CALAMARES_PLUGIN_FACTORY_DEFINITION( LuksBootKeyFileJobFactory, registerPlugin< LuksBootKeyFileJob >(); )
